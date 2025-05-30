include ../../.config

HYPVSR_LINK = \
hostfs.c

BUILD_DIR = ../../build/hostfs

all:
ifeq ($(CONFIG_HOSTFS), y)
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC_CORE) -c $(CFLAGS_CORE) $$src -o $(BUILD_DIR)/$$src.o; \
	done
endif
