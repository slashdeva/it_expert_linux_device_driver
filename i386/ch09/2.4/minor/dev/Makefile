KERNELDIR = /lib/modules/$(shell uname -r)/build
CFLAGS = -D__KERNEL__ -DMODULE -I$(KERNELDIR)/include -O

all: minor_dev.o

clean:
	rm -rf *.o
