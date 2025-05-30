include ../../.config

HYPVSR_LINK = \
uefifs.c

BUILD_DIR = ../../build/uefifs

all:
ifeq ($(CONFIG_UEFIFS), y)
	mkdir -p $(BUILD_DIR)

	for src in $(HYPVSR_LINK) ; do \
	    $(CC_CORE) -c $(CFLAGS_CORE) -Wno-macro-redefined $$src -o $(BUILD_DIR)/$$src.o; \
	done
endif
