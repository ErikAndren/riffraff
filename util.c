#include "util.h"
#include "types.h"

#include <mbedtls/sha1.h>

uint64_t x_to_uint64_t(const char *hex) {
	uint64_t result, t;
	uint32_t len;
	int32_t c;

	result = 0;
	t = 0;
	len = strlen(hex);

	while (len--) {
		c = *hex++;
		if (c >= '0' && c <= '9')
			t = c - '0';
		else if (c >= 'a' && c <= 'f')
			t = c - 'a' + 10;
		else if (c >= 'A' && c <= 'F')
			t = c - 'A' + 10;
		else
			t = 0;
		result |= t << (len * 4);
	}

	return result;
}

uint8_t * x_to_uint8_t_buffer(const char *hex) {
	char tmp[3] = { 0, 0, 0 };
	uint8_t *result;
	uint8_t *ptr;
	uint32_t len;

	len = strlen(hex);
	if (len % 2 != 0)
		return NULL;

	result = (uint8_t *)malloc(len);
	memset(result, 0, len);
	ptr = result;

	while (len--) {
		tmp[0] = *hex++;
		tmp[1] = *hex++;
		*ptr++ = (uint8_t)x_to_uint64_t(tmp);
	}

	return result;
}

void dump_data(const uint8_t *data, uint64_t size, FILE *fp) {
	uint64_t i;
	for (i = 0; i < size; i++)
		printf("%02X", data[i]);
	printf("\n");
}

int get_file_size(const char *file_path, uint64_t *size) {
	struct stat stat_buf;

	if (!file_path || !size)
		return -1;

	if (stat(file_path, &stat_buf) < 0)
		return -1;

	*size = stat_buf.st_size;

	return 0;
}

int read_file(const char *file_path, uint8_t *data, uint64_t size) {
	FILE *fp;
	struct stat stat_buf;

	if (!file_path || !data)
		return -1;

	fp = fopen(file_path, "rb");
	if (!fp)
		return -1;

	if (fstat(fileno(fp), &stat_buf) < 0)  {
		fclose(fp);
		return -1;
	}

	if (stat_buf.st_size < size) {
		fclose(fp);
		return -1;
	}

	memset(data, 0, size);

	if (fread(data, 1, size, fp) != size) {
		fclose(fp);
		return -1;
	}

	fclose(fp);

	return 0;
}

int write_file(const char *file_path, uint8_t *data, uint64_t size) {
	FILE *fp;

	if (!file_path || !data)
		return -1;

	fp = fopen(file_path, "wb");
	if (!fp)
		return -1;

	if (fwrite(data, 1, size, fp) != size) {
		fclose(fp);
		return -1;
	}

	fclose(fp);

	return 0;
}

int mmap_file(const char *file_path, uint8_t **data, uint64_t *size) {
	int fd;
	struct stat stat_buf;
	void *ptr;

	if (!file_path || !data || !size)
		return -1;

	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return -1;

	if (fstat(fd, &stat_buf) != 0) {
		close(fd);
		return -1;
	}

	ptr = malloc(stat_buf.st_size);
	if (!ptr) {
		close(fd);
		return -1;
	}

	close(fd);

	read_file(file_path, ptr, stat_buf.st_size);

	*data = (uint8_t *)ptr;
	*size = stat_buf.st_size;

	return 0;
}

int unmmap_file(uint8_t *data, uint64_t size) {
	if (!data || !size)
		return -1;

	free(data);
//	if (munmap(data, size) < 0)
//		return -1;

	return 0;
}

/* int calculate_hmac_hash(const uint8_t *data, uint64_t size, const uint8_t *key, uint32_t key_length, uint8_t output[20]) { */
/* 	mbedtls_sha1_context sha1; */

/* 	if (!key_length || !output) */
/* 		return -1; */

/* 	memset(&sha1, 0, sizeof(sha1_context)); */

/* 	sha1_hmac_starts(&sha1, key, key_length); */
/* 	sha1_hmac_update(&sha1, data, size); */
/* 	sha1_hmac_finish(&sha1, output); */

/* 	memset(&sha1, 0, sizeof(sha1_context)); */

/* 	return 0; */
/* } */

/* int calculate_file_hmac_hash(const char *file_path, const uint8_t *key, uint32_t key_length, uint8_t output[20]) { */
/* 	FILE *fp; */
/* 	uint8_t buf[512]; */
/* 	sha1_context sha1; */
/* 	size_t n; */

/* 	if ((fp = fopen(file_path, "rb")) == NULL) */
/* 		return -1; */

/* 	memset(&sha1, 0, sizeof(sha1_context)); */

/* 	sha1_hmac_starts(&sha1, key, key_length); */
/* 	while ((n = fread(buf, 1, sizeof(buf), fp)) > 0) */
/* 		sha1_hmac_update(&sha1, buf, n); */
/* 	sha1_hmac_finish(&sha1, output); */

/* 	memset(&sha1, 0, sizeof(sha1_context)); */

/* 	if (ferror(fp) != 0) { */
/* 		fclose(fp); */
/* 		return -1; */
/* 	} */

/* 	fclose(fp); */

/* 	return 0; */
/* } */

uint64_t align_to_pow2(uint64_t offset, uint64_t alignment) {
	return (offset + alignment - 1) & ~(alignment - 1);
}

int read_buffer(const char *file_path, uint8_t **buf, size_t *size) {
        FILE *fp;
        uint8_t *file_buf;
        size_t file_size;

        if ((fp = fopen(file_path, "rb")) == NULL)
                return -1;
        fseek(fp, 0, SEEK_END);
        file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        file_buf = (uint8_t *)malloc(file_size);
        fread(file_buf, 1, file_size, fp);
        fclose(fp);

        if (buf)
                *buf = file_buf;
        else
                free(file_buf);
        if (size)
                *size = file_size;

        return 0;
}

int write_buffer(const char *file_path, uint8_t *buf, size_t size) {
        FILE *fp;

        if ((fp = fopen(file_path, "wb")) == NULL)
                return -1;
        fwrite(buf, 1, size, fp);
        fclose(fp);

        return 0;
}
