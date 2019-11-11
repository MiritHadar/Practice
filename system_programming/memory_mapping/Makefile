CC=/usr/bin/gcc
CFLAGS=-g
RM=/bin/rm -f
AR=/usr/bin/ar
ARFLAGS=rvs
SOFLAGS=-fPIC -shared
LIBS=-ldl


TARGETS=main archive runtimeso sowitharchive
OBJS=$(TARGETS:%=%.o)

all: $(TARGETS)
	$(AR) $(ARFLAGS) libarchive.a archive.o
	$(CC) $(CFLAGS) $(SOFLAGS) runtimeso.c -o libruntimeso.so 
	$(CC) $(CFLAGS) $(SOFLAGS) libarchive.a sowitharchive.o -o libsowitharchive.so
	$(CC) $(CFLAGS) main.o -o main.out $(LIBS) libarchive.a libsowitharchive.so 

% : %.c
	$(CC) -c $(CFLAGS) $(SOFLAGS) $*.c

clean:
	$(RM) *~ *.o *.bak core *.out *.so *.a
