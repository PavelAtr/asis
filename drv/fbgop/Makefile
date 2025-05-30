include ../../.config

HYPVSR_LINK = \
fbgop.c

BUILD_DIR = ../../build/fbgop

all:
ifeq ($(CONFIG_FBGOP), y)
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC_CORE) -c $(CFLAGS_CORE) $$src -o $(BUILD_DIR)/$$src.o; \
	done
endif
