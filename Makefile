
.PHONY: all
#.SECONDARY:

ifneq ($(KERNELRELEASE),)

  obj-m := helloWorld.o
  obj-m +=  helloWorldParam.o
  obj-m +=  helloWorldHideProc.o
  obj-m +=  helloWorldHideProcSyscall.o
  # nom du module (pas le .ko mais l'intermédiaire)

  # Si plusieurs sources, on liste les fichiers objets :
  #$(name)-objs := file1.o file2.o

else

  KERNELDIR ?= /lib/modules/$(shell uname -r)/build
  PWD := $(shell pwd)

all :
	make -C $(KERNELDIR) M=$(PWD) modules

clean:
	make -C $(KERNELDIR) M=$(PWD) clean
endif
