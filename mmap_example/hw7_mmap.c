#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <termios.h>

// rpi4 target board register address, size
#define BCM2711_PERI_BASE 0xFE000000
#define BLOCK_SIZE (4*1024)
#define PAGE_SIZE (4*1024)
#define GPIO_BASE (BCM2711_PERI_BASE + 0x200000)

// offset setting
#define GPFSEL0 0x00    // gpio function select 0
#define GPSET0 0x1c     // gpio pin ouput set 0
#define GPCLR0 0x28     // gpio pin output clear 0
#define GPLEV0 0x34     // gpio pin level 1

// termios : terminal return control struct
/* init_setting : 초기 터미널 설정 저장
 * new_setting : 새로운 터미널 설정 저장 */
static struct termios init_setting, new_setting;

// keyboard reset
void init_keyboard()
{
	tcgetattr(STDIN_FILENO, &init_setting);
	new_setting = init_setting;
	new_setting.c_lflag &= ~ICANON;
	new_setting.c_lflag &= ~ECHO;
	new_setting.c_cc[VMIN] = 0;
	new_setting.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_setting);
}

// close keyboard : terminal setting = init_setting 으로 복원
void close_keyboard()
{
	tcsetattr(0, TCSANOW, &init_setting);
}

// read input key > return char type 
char get_key()
{
	char ch = -1;

	if(read(STDIN_FILENO, &ch, 1) != 1)
		ch = -1;
	return ch;
}

// print menu
void print_menu()
{
	printf("\n\n-------------------------\n");
	printf("press the button !\n");
	printf("[q] ; Exit program\n");
	printf("----------------------------\n");
}


/*
 * 1. 프로그램 이름 외의 argument는 없다.
 * 2. 첫 실행시 LED가 꺼져있다.
 * 3. 버튼을 누르면 LED가 켜지고, 다시 누르면 꺼진다.(토글방식) 
 * 4. 키보드[q]를 눌러 프로그램을 종료한다.
 */

int main(int argc, char **argv)
{
	// variable setting
	int data;
	int memfd;
	char *addr_gpio;
	volatile unsigned int *gpio;
	char ch;
    int tmp;
    int prev;
    int led_flag;

	// target board all system mem open
	/* O_RDWR: read/write mode
	 * O_SYNC: data 가 cache 를 거쳐 전송되었는지 확인하는 option */
	memfd = open("/dev/mem", O_RDWR | O_SYNC);
	if(memfd<0){
		printf("mem open fail\n");
		return -1;
	}

	// *char pointer addr_gpio 에 mmap로 mem address mapping
	/* void *mmap(void *start, size_t length, int prot, int flags, int fd, off_toffset); */
	addr_gpio = (char*)mmap(NULL, BLOCK_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, memfd, GPIO_BASE);
	if(addr_gpio == MAP_FAILED){
		printf("mmap fail\n");
		return -1;
	}

	// addr_gpio 를 rasp4 control format 맞춰서 int type 으로 재선언
	gpio = (volatile unsigned int*)addr_gpio;

	// GPIO4 를 output pin으로 설정 (led on/off)
	gpio[GPFSEL0/4] |= (1<<12);

	// read keyboard input, print menu
	init_keyboard();
	print_menu();

    led_flag =0;

	while(1){
		ch = get_key();
        prev = tmp;
		tmp = gpio[GPLEV0/4] & (1<<17);     // monitoring GPIO17(switch)

        // interrupt    
		if(ch == 'q'){                      // if keyboard interrupt > shut down
			gpio[GPCLR0/4] |= (1<<4);
			printf("shut down program\n");
			break;
		}
        else if(tmp != prev){               // if switch interrupt (off>on or on>off)
			if(tmp & (1<<17)){              // off>on
                led_flag = 1-led_flag;      // flag change
			}
		}

        // led on/off
        if(led_flag==1){                    // if flag ==1 : led is on
            gpio[GPSET0/4] |= (1<<4);
        }
        else{
            gpio[GPCLR0/4] |= (1<<4);       // if flag ==0 : led is off
        }
	}
	
	// munmap : mmap(addr_gpio) free
	munmap(addr_gpio, BLOCK_SIZE);
	close_keyboard();
	close(memfd);

	return 0;
}

