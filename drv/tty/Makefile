include ../../.config

HYPVSR_LINK = \
tty.c

BUILD_DIR = ../../build/tty

ifeq ($(CONFIG_TTY), y)
all:
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC) -c $(CFLAGS) $$src -o $(BUILD_DIR)/$$src.o; \
	done
else
all:
endif
