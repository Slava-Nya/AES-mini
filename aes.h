#define _AES_H_

#include <stdint.h>
#include <stddef.h>

#define AES_BLOCKLEN 16 // Block length in bytes - AES is 128b block only
#define AES_KEYLEN 16   // Key length in bytes
#define AES_keyExpSize 176


struct AES_ctx
{
	uint8_t RoundKey[AES_keyExpSize];
	uint8_t Iv[AES_BLOCKLEN];
};

