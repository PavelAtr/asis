include ../.config
include ../make.conf

all:
ifeq ($(CONFIG_ALIBC), y)
	make -C alibc
	make -C alibc install
endif
ifeq ($(CONFIG_LIBDL), y)
	make -C libdl
	make -C libdl install
endif
ifeq ($(CONFIG_LIBPWD), y)
	make -C libpwd
	make -C libpwd install
endif
ifeq ($(CONFIG_TESTAPP), y)
	make -C testapp
	make -C testapp install
endif
ifeq ($(CONFIG_DASH), y)
	cd scripts; ./dash.sh
endif
ifeq ($(CONFIG_COREUTILS), y)
	cd scripts; ./coreutils.sh
endif




clean:
	make -C alibc clean
	make -C libdl clean
	make -C libpwd clean
	make -C testapp clean

install_headers:
	make -C alibc install_headers
	make -C libdl install_headers
	make -C libpwd install_headers
