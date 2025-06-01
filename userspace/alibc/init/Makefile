PREFIX?=/asis
CFLAGS?= -g -fPIC --sysroot=$(PREFIX)

all: 
	$(CC) $(CFLAGS) -c crt.c
	$(CC) $(CFLAGS) -c crtstub.c
	ar rcs crtstub.a crtstub.o
	
clean:
	rm -f *.o *.a

