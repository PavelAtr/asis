include ../../.config

HYPVSR_LINK = \
lintrap.c

BUILD_DIR = ../../build/lintrap

all:
ifeq ($(CONFIG_LINTRAP), y)
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC) -c $(CFLAGS) $$src -o $(BUILD_DIR)/$$src.o; \
	done
endif
