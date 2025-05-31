include ../../.config
include ../../make.conf

HYPVSR_LINK = \
dummyblk.c

BUILD_DIR = ../../build/dummyblk

all:
ifeq ($(CONFIG_DUMMYBLK), y)
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC_CORE) -c $(CFLAGS_CORE) $$src -o $(BUILD_DIR)/$$src.o; \
	done
endif