CC=gcc
CFLAGS=-W -Wall -Wextra -O2 -fstack-protector-all
DFLAGS=-D_FORTIFY_SOURCE=2
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS=-Wl
else
	LDFLAGS=-Wl,-z,relro,-z,now 
endif

0d1n: payloadmask.c 
	$(CC) $(CFLAGS) $(DFLAGS) -c *.c
	$(CC) -o payloadmask *.o $(LDFLAGS)

clean:
	rm -f *.o payloadmask
