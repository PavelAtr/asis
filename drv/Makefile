ARCH?=x86_64

ifeq ($(CONFIG_LINUX), y)
    CFLAGS?= -fPIC -g -fomit-frame-pointer -D__ASIS__
endif

PREFIX?=/asis

SYSTEM_LINK = \
tty/*.c \
blk/*.c \
loop/*.c \
hosttrap/*.c 

BUILD_DIRS = \
../build/tty \
../build/blk/ \
../build/loop/ \
../build/hosttrap/ \

all:
	mkdir -p $(BUILD_DIRS)

	make -C hostfs
	make -C tty
	make -C loop
