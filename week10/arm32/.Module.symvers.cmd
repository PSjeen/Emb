cmd_/home/sangjin/working/week10/arm32/Module.symvers :=  sed 's/ko$$/o/'  /home/sangjin/working/week10/arm32/modules.order | scripts/mod/modpost -m -a    -o /home/sangjin/working/week10/arm32/Module.symvers -e -i Module.symvers -T - 