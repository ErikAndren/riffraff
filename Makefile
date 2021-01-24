CC=gcc

CFLAGS=-I/usr/local/Cellar/mbedtls/2.25.0/include/ -llibmbedtls

rif2rap:
	$(CC) -o rif2rap $(CFLAGS) ecdsa.c rifrap.c

clean:
