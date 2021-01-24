#include <stdio.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
	/* FILE *fp; */
	/* int result; */
	/* uint8_t buffer[16]; */

	if (argc != 2) {
		printf("One argument: String of idps\n");
		return -1;
	}

	char *pos = argv[1];
    uint8_t val[16];
	size_t arglen = strlen(argv[1]);

	if (arglen != 32) {
		printf("IDPS must be precisely 16 bytes (32 char in hex)\n");
		return -2;
	}

	/* WARNING: no sanitization or error-checking whatsoever */
    for (size_t count = 0; count < arglen; count++) {
        sscanf(pos, "%2hhx", &val[count]);
        pos += 2;
    }

    for(size_t count = 0; count < arglen / 2; count++)
        printf("%02x", val[count]);
    printf("\n");


	/* fp = fopen("idps.hex", 'w'); */
	/* if (fp == NULL) { */
	/* 	printf("Failed to open idps.hex\n"); */
	/* 	return errno; */
	/* } */

	/* result = snprintf(buffer, 16, */
	/* //result = fwrite( */

	return 0;
}
