include .config

export PREFIX=/asis
ifeq ($(CONFIG_X86_64), y)
    export ARCH=x86_64
endif
ifeq ($(CONFIG_LINUX), y)
    export CFLAGS= -fPIC -g -fomit-frame-pointer
    export SYSROOT=--sysroot=$(PREFIX)
endif


all: headers
	make -C core
	make -C userspace

headers:
	make -C core install_headers
	make -C userspace install_headers

menuconfig:
	kconfig-mconf KConfig
	cat .config | grep -v "#" | tr '=' ' ' | tr '=' ' ' | tr -s '\n' | sed 's/\(,*\)/#define \1/' > config.h

clean:
	make -C core clean
	make -C userspace clean
    