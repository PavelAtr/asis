include ../.config
include ../make.conf

PREFIX?=/asis

HYPERV_LINK = \
syscalls/sys_memory.c \
main.c \
sys_printf.c

ASIS_LINK = \
sys_dev.c \
sys_sched.c \
syscalls/sys_run.c \
sys_proc.c \
sys_security.c \
sys_syscall.c \
syscalls/sys_fs.c \
syscalls/sys_mount.c \
syscalls/sys_usleep.c \
syscalls/sys_rlimit.c \
sys_dl.c \
sys_trap.c \
sys_tls.c \
sys_shared.c \
sys_socket.c


EXTLIBS = \
userspace/alibdl/libdl.c \
userspace/alibdl/tinyelf.c \
userspace/alibdl/$(ARCH)/relocate.c \
userspace/alibdl/list.c \
userspace/alibdl/modid.c \
userspace/alibc/src/stdio.c

BUILD_DIRS = \
../build/syscalls \
../build/userspace/alibc/src \
../build/userspace/alibdl/$(ARCH)

all: install_headers objs

	$(LD_CORE) $(LDFLAGS_CORE) $(shell find ../build -name '*.o')

objs: clean
	mkdir -p $(BUILD_DIRS)

	make -C ../drv -f Makefile

	for src in $(HYPERV_LINK) ; do \
	    $(CC_CORE) -c $(CFLAGS_CORE) -DUSE_SYMBOLFILE  $$src -o ../build/$$src.o; \
	done

	for src in $(ASIS_LINK) ; do \
	    $(CC_CORE) -c $(CFLAGS_CORE) -Wno-macro-redefined -Wno-pointer-to-int-cast -Wno-int-to-pointer-cast $(SYSROOT) -D__ASIS__ -DUSE_SYMBOLFILE $$src -o ../build/$$src.o; \
	done

	for src in $(EXTLIBS) ; do \
	    $(CC_CORE) -c $(CFLAGS_CORE) -Wno-sign-compare $(SYSROOT) -D__ASIS__ -DUSE_SYMBOLFILE $$src -o ../build/$$src.o; \
	done
clean:
	rm -rf ../build/*

install_headers:
	mkdir -p $(DESTDIR)$(PREFIX)/usr/
	cp -r include $(DESTDIR)$(PREFIX)/usr/

