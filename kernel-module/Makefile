obj-m := hello-1.o hello-2.o hello-3.o hello-4.o hello-5.o chardev.o print_string.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

# You may need to be root to compile the module.
#
# You must be root to insert it into a running kernel
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
