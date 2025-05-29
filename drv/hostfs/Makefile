include ../../.config

HYPVSR_LINK = \
hostfs.c

BUILD_DIR = ../../build/hostfs

ifeq ($(CONFIG_HOSTFS), y)
all:
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC) -c $(CFLAGS) -DELF64 $$src -o $(BUILD_DIR)/$$src.o; \
	done
else
all:
endif
