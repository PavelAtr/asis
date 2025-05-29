include ../../.config

HYPVSR_LINK = \
tty.c

BUILD_DIR = ../../build/tty

all:
ifeq ($(CONFIG_TTY), y)
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC) -c $(CFLAGS_CORE) -Wno-macro-redefined $$src -o $(BUILD_DIR)/$$src.o; \
	done
endif
