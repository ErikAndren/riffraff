//#include <ppu-types.h>
#include <stdint.h>

int ecdsa_set_curve(uint32_t type);
void ecdsa_set_pub(uint8_t *Q);
void ecdsa_set_priv(uint8_t *k);
void ecdsa_sign(uint8_t *hash, uint8_t *R, uint8_t *S);

void get_rand(uint8_t *dst, uint32_t len);
