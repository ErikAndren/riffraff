#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>


int main(int argc, char *argv[]) {
	int result;
	FILE *fp;
	char *pos = argv[1];
    uint8_t val[16];
	size_t arglen = strlen(argv[1]);

	if (argc != 2) {
		printf("One argument: String of idps\n");
		return -1;
	}

	if (arglen != 32) {
		printf("IDPS must be precisely 16 bytes (32 char in hex)\n");
		return -1;
	}

    for (size_t count = 0; count < arglen / 2; count++) {
        result = sscanf(pos, "%2hhx", &val[count]);
		if (result <= 0) {
			printf("Failed to convert string\n");
			return -1;
		}

        pos += 2;
    }

	/* Debug */
    /* for(size_t count = 0; count < arglen / 2; count++) */
    /*     printf("%02x", val[count]); */
    /* printf("\n"); */

	fp = fopen("idps.hex", "w");
	if (fp == NULL) {
		printf("Failed to open idps.hex\n");
		return errno;
	}

	result = fwrite(val, 1, 16, fp);
	if (result != 16) {
		printf("Failed to write idps to idps: %d\n", result);
		fclose(fp);
		return -1;
	}

	result = fclose(fp);
	if (result != 0) {
		printf("Failed to close idps.hex\n");
		return -1;
	}

	printf("Successfully wrote idps to idps.hex\n");

	return 0;
}
