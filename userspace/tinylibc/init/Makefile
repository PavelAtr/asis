PREFIX?=/tinysys
CFLAGS?= -g -fPIC -fomit-frame-pointer --sysroot=$(PREFIX)

all: 
	$(CC) $(CFLAGS) -g -fPIC -c crt.c
	$(CC) $(CFLAGS) -g -fPIC -c tls.c
	ar rcs tls.a tls.o
	
clean:
	rm -f *.o *.a

