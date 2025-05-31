include ../../.config
include ../../make.conf

HYPVSR_LINK = \
loop.c

BUILD_DIR = ../../build/loop

all:
ifeq ($(CONFIG_LOOP), y)
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC_CORE) -c $(CFLAGS_CORE) $$src -o $(BUILD_DIR)/$$src.o; \
	done
endif
