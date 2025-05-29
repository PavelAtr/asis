include ../../.config

HYPVSR_LINK = \
lintrap.c

BUILD_DIR = ../../build/lintrap

ifeq ($(CONFIG_HOSTFS), y)
all:
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC) -c $(CFLAGS) $$src -o $(BUILD_DIR)/$$src.o; \
	done
endif
