obj-m += ldd.o

all: ldd.c
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean

test.text: test.c
	cat test.c
	cat test.c > test.text
	cat test.text