include ../../.config
include ../../make.conf

HYPVSR_LINK = \
uefikeyboard.c

BUILD_DIR = ../../build/uefikeyboard

all:
ifeq ($(CONFIG_UEFIKEYBOARD), y)
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC_CORE) -c $(CFLAGS_CORE) -Wno-macro-redefined $$src -o $(BUILD_DIR)/$$src.o; \
	done
endif
