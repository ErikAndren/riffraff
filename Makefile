CC=gcc

CFLAGS=-I/usr/local/Cellar/mbedtls/2.25.0/include/ -lmbedtls -lmbedcrypto

FILES = util.c ecdsa.c rifrap.c

rif2rap: $(FILES)
	$(CC) -o rif2rap $(CFLAGS) $(FILES)

clean:
