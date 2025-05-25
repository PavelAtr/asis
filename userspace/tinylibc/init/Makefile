PREFIX?=/tinysys
CFLAGS?= -g -fPIC -fomit-frame-pointer --sysroot=$(PREFIX)

all: 
	$(CC) $(CFLAGS) -g -fPIC -c crt.c
	$(CC) $(CFLAGS) -g -fPIC -c tls.c
	$(CC) $(CFLAGS) -g -fPIC -c crtstub.c
	ar rcs tls.a tls.o
	ar rcs crtstub.a crtstub.o
	
clean:
	rm -f *.o *.a

