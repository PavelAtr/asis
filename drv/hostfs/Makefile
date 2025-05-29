include ../../.config

ARCH?=x86_64

ifeq ($(CONFIG_LINUX), y)
    CFLAGS?= -fPIC -g -fomit-frame-pointer -D__ASIS__
endif

PREFIX?=/asis

HYPVSR_LINK = \
hostfs.c

BUILD_DIR = ../../build/hostfs

ifeq ($(CONFIG_HOSTFS), y)
all:
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC) -c $(CFLAGS) -DELF64 $$src -o $(BUILD_DIR)/$$src.o; \
	done
endif
