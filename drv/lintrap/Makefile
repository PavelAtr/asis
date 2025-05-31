include ../../.config
include ../../make.conf

HYPVSR_LINK = \
lintrap.c

BUILD_DIR = ../../build/lintrap

all:
ifeq ($(CONFIG_LINTRAP), y)
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC_CORE) -c $(CFLAGS_CORE) $$src -o $(BUILD_DIR)/$$src.o; \
	done
endif
