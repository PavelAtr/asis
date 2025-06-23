include ../.config
include ../make.conf

all:
	make -C alibc install_headers
	make -C alibdl install_headers
	make -C alibpwd install_headers
	make -C athreads install_headers
	make -C amath install_headers

ifeq ($(CONFIG_ALIBC), y)
	make -C alibc
	make -C alibc install
endif
ifeq ($(CONFIG_LIBDL), y)
	make -C alibdl
	make -C alibdl install
endif
ifeq ($(CONFIG_LIBPWD), y)
	make -C alibpwd
	make -C alibpwd install
endif
ifeq ($(CONFIG_ATHREADS), y)
	make -C athreads
	make -C athreads install
endif
ifeq ($(CONFIG_AMATH), y)
	make -C amath
	make -C amath install
endif
ifeq ($(CONFIG_TESTAPP), y)
	make -C atestapp
	make -C atestapp install
endif
ifeq ($(CONFIG_DASH), y)
	cd scripts; ./dash.sh
endif
ifeq ($(CONFIG_COREUTILS), y)
	cd scripts; ./coreutils.sh
endif
ifeq ($(CONFIG_LIBFFI), y)
	cd scripts; ./libffi.sh
endif
ifeq ($(CONFIG_EXPAT), y)
	cd scripts; ./expat.sh
endif
ifeq ($(CONFIG_ZLIB), y)
	cd scripts; ./zlib.sh
endif
ifeq ($(CONFIG_XZUTILS), y)
	cd scripts; ./xz-utils.sh
endif
ifeq ($(CONFIG_LIBXML), y)
	cd scripts; ./libxml.sh
endif
ifeq ($(CONFIG_WAYLAND), y)
	cd scripts; ./wayland.sh
endif
ifeq ($(CONFIG_WAYLANDPROTOCOLS), y)
	cd scripts; ./wayland-protocols.sh
endif
ifeq ($(CONFIG_LIBGLVND), y)
	cd scripts; ./libglvnd.sh
endif
ifeq ($(CONFIG_LIBDRM), y)
	cd scripts; ./libdrm.sh
endif
	mv $(DESTDIR)$(PREFIX)/include/* $(DESTDIR)$(PREFIX)/usr/include/ || true
	rm -rf $(DESTDIR)$(PREFIX)/include/ || true
ifeq ($(CONFIG_EUDEV), y)
	cd scripts; ./eudev.sh
endif
ifeq ($(CONFIG_LIBINPUT), y)
	cd scripts; ./libinput.sh
endif
ifeq ($(CONFIG_WLROOTS), y)
	cd scripts; ./wlroots.sh
endif




clean:
	make -C alibc clean
	make -C alibdl clean
	make -C alibpwd clean
	make -C atestapp clean
	make -C athreads clean
	make -C amath clean

install_headers:
	make -C alibc install_headers
	make -C alibdl install_headers
	make -C alibpwd install_headers
	make -C athreads install_headers
	make -C amath install_headers
