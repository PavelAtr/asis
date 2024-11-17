all:
	gcc -O2 -c -I./src -g  -DDYNAMIC_ALLOCATION src/weekfs.c src/weekfs_unix.c test/*.c
	gcc *.o  -o weekfs
