include ../../.config

HYPVSR_LINK = \
dummyblk.c

BUILD_DIR = ../../build/dummyblk

ifeq ($(CONFIG_DUMMYBLK), y)
all:
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC) -c $(CFLAGS) -DELF64 $$src -o $(BUILD_DIR)/$$src.o; \
	done
endif
