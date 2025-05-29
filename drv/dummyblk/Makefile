include ../../.config

HYPVSR_LINK = \
dummyblk.c

BUILD_DIR = ../../build/dummyblk

all:
ifeq ($(CONFIG_DUMMYBLK), y)
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC) -c $(CFLAGS) $$src -o $(BUILD_DIR)/$$src.o; \
	done
endif