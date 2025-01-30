PREFIX?=/tinysys
CFLAGS?= -g -fPIC -fomit-frame-pointer --sysroot=$(PREFIX)

all: 
	$(CC) $(CFLAGS) -g -fPIC -c crt.c
	
clean:
	rm -f *.o

