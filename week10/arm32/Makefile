obj-m += seg_driver.o
KDIR = ~/working/Raspbian/kernel
RESULT1 = seg_example
RESULT2 = seg_example2
SRC1 = $(RESULT1).c
SRC2 = $(RESULT2).c
CCC = arm-linux-gnueabihf-gcc

all:
	make -C $(KDIR) M=$(PWD) modules
	$(CCC) -o $(RESULT1) $(SRC1)
	$(CCC) -o $(RESULT2) $(SRC2)

clean:
	make -C $(KDIR) M=$(PWD) clean
	rm -f $(RESULT1) $(RESULT2)
