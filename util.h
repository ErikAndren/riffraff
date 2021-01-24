#ifndef _UTIL_H_
#define _UTIL_H_

#include "types.h"

#define ALIGN(_value, _alignment) (((_value) + (_alignment) - 1) & ~((_alignment) - 1))

uint64_t x_to_uint64_t(const char *hex);
uint8_t * x_to_uint8_t_buffer(const char *hex);

void dump_data(const uint8_t *data, uint64_t size, FILE *fp);

int get_file_size(const char *file_path, uint64_t *size);
int read_file(const char *file_path, uint8_t *data, uint64_t size);
int write_file(const char *file_path, uint8_t *data, uint64_t size);
int mmap_file(const char *file_path, uint8_t **data, uint64_t *size);
int unmmap_file(uint8_t *data, uint64_t size);

int calculate_hmac_hash(const uint8_t *data, uint64_t size, const uint8_t *key, uint32_t key_length, uint8_t output[20]);
int calculate_file_hmac_hash(const char *file_path, const uint8_t *key, uint32_t key_length, uint8_t output[20]);

int wildcard_match(const char *data, const char *mask);
int wildcard_match_icase(const char *data, const char *mask);

uint64_t align_to_pow2(uint64_t offset, uint64_t alignment);

int read_buffer(const char *file_path, uint8_t **buf, size_t *size);
int write_buffer(const char *file_path, uint8_t *buf, size_t size);

#endif /* !_UTIL_H_ */
