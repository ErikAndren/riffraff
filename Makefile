CC=gcc

CFLAGS=-I/usr/local/Cellar/mbedtls/2.25.0/include/ -lmbedtls -lmbedcrypto

FILES = util.c ecdsa.c rifrap.c main.c

all: riffraff str2idps

riffraff: $(FILES)
	$(CC) -o $@ $(CFLAGS) $(FILES)

str2idps: str2idps.c
	$(CC) -o $@ $(CFLAGS) str2idps.c

clean:
	@rm -f riffraff str2idps *~
