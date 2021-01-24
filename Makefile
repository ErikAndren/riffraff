CC=gcc

CFLAGS=-I/usr/local/Cellar/mbedtls/2.25.0/include/ -lmbedtls -lmbedcrypto

rif2rap:
	$(CC) -o rif2rap $(CFLAGS) util.c ecdsa.c rifrap.c

clean:
