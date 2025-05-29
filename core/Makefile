include ../.config

ifeq ($(CONFIG_X86_64), y)
    export ARCH=x86_64
endif
ifeq ($(CONFIG_LINUX), y)
    export CFLAGS?= -fPIC -g -fomit-frame-pointer -D__ASIS__
endif
export PREFIX=/asis

SYSTEM_LINK = \
syscalls/sys_memory.c \
sys_printf.c

ASIS_LINK = \
sys_dev.c \
sys_sched.c \
main.c \
syscalls/sys_run.c \
sys_proc.c \
sys_security.c \
sys_syscall.c \
syscalls/sys_fs.c \
syscalls/sys_mount.c \
syscalls/sys_usleep.c \
syscalls/sys_rlimit.c \
sys_dl.c \
sys_trap.c 


EXTLIBS = \
userspace/libdl/libdl.c \
userspace/libdl/tinyelf.c \
userspace/libdl/$(ARCH)/relocate.c \
userspace/libdl/list.c \
userspace/alibc/src/stdio.c

BUILD_DIRS = \
../build/syscalls \
../build/userspace/alibc/src \
../build/userspace/libdl/$(ARCH)

all: objs

	$(CC) $(LDFLAGS) $(shell find ../build -name '*.o') -o ../build/asis.linux

objs: clean
	mkdir -p $(BUILD_DIRS)

	make -C ../drv -f Makefile

	for src in $(SYSTEM_LINK) ; do \
	    $(CC) -c $(CFLAGS) -DELF64 $$src -o ../build/$$src.o; \
	done

	for src in $(ASIS_LINK) ; do \
	    $(CC) -c $(CFLAGS) --sysroot=$(PREFIX) -DUSE_SYMBOLFILE $$src -o ../build/$$src.o; \
	done

	for src in $(EXTLIBS) ; do \
	    $(CC) -c $(CFLAGS) --sysroot=$(PREFIX) -include include/asis.h -DELF64 -DUSE_SYMBOLFILE $$src -o ../build/$$src.o; \
	done
clean:
	rm -rf ../build/*

install_headers:
	cp -r include $(DESTDIR)$(PREFIX)/usr/

