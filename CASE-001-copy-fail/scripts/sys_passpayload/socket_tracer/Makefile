obj-m += socket_tracer.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

ccflags-y += -Wall -Wextra

# build
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

# clean
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean