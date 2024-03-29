#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "aes.h"


static void phex(uint8_t* str);
static int test_encrypt_ecb(void);
static int test_decrypt_ecb(void);
static void test_encrypt_ecb_verbose(void);
static int test_encrypt_hello_ecb(void);

int main(void)
{
	int exit;

	exit = test_encrypt_ecb() + test_decrypt_ecb();
	test_encrypt_ecb_verbose();

	return exit;
}


// prints string as hex
static void phex(uint8_t* str)
{
	uint8_t len = 16;

	unsigned char i;
	for (i = 0; i < len; ++i)
		printf("%.2x", str[i]);
	printf("\n");
}

static void test_encrypt_ecb_verbose(void)
{
	// Example of more verbose verification

	uint8_t i;

	// 128bit key
	uint8_t key[16] =        { (uint8_t) 0x2b, (uint8_t) 0x7e, (uint8_t) 0x15, (uint8_t) 0x16, (uint8_t) 0x28, (uint8_t) 0xae, (uint8_t) 0xd2, (uint8_t) 0xa6, (uint8_t) 0xab, (uint8_t) 0xf7, (uint8_t) 0x15, (uint8_t) 0x88, (uint8_t) 0x09, (uint8_t) 0xcf, (uint8_t) 0x4f, (uint8_t) 0x3c };
	// 512bit text
	uint8_t plain_text[64] = { (uint8_t) 0x6b, (uint8_t) 0xc1, (uint8_t) 0xbe, (uint8_t) 0xe2, (uint8_t) 0x2e, (uint8_t) 0x40, (uint8_t) 0x9f, (uint8_t) 0x96, (uint8_t) 0xe9, (uint8_t) 0x3d, (uint8_t) 0x7e, (uint8_t) 0x11, (uint8_t) 0x73, (uint8_t) 0x93, (uint8_t) 0x17, (uint8_t) 0x2a,
							   (uint8_t) 0xae, (uint8_t) 0x2d, (uint8_t) 0x8a, (uint8_t) 0x57, (uint8_t) 0x1e, (uint8_t) 0x03, (uint8_t) 0xac, (uint8_t) 0x9c, (uint8_t) 0x9e, (uint8_t) 0xb7, (uint8_t) 0x6f, (uint8_t) 0xac, (uint8_t) 0x45, (uint8_t) 0xaf, (uint8_t) 0x8e, (uint8_t) 0x51,
							   (uint8_t) 0x30, (uint8_t) 0xc8, (uint8_t) 0x1c, (uint8_t) 0x46, (uint8_t) 0xa3, (uint8_t) 0x5c, (uint8_t) 0xe4, (uint8_t) 0x11, (uint8_t) 0xe5, (uint8_t) 0xfb, (uint8_t) 0xc1, (uint8_t) 0x19, (uint8_t) 0x1a, (uint8_t) 0x0a, (uint8_t) 0x52, (uint8_t) 0xef,
							   (uint8_t) 0xf6, (uint8_t) 0x9f, (uint8_t) 0x24, (uint8_t) 0x45, (uint8_t) 0xdf, (uint8_t) 0x4f, (uint8_t) 0x9b, (uint8_t) 0x17, (uint8_t) 0xad, (uint8_t) 0x2b, (uint8_t) 0x41, (uint8_t) 0x7b, (uint8_t) 0xe6, (uint8_t) 0x6c, (uint8_t) 0x37, (uint8_t) 0x10 };

	// print text to encrypt, key and IV
	printf("ECB encrypt verbose:\n\n");
	printf("plain text:\n");
	for (i = (uint8_t) 0; i < (uint8_t) 4; ++i)
	{
		phex(plain_text + i * (uint8_t) 16);
	}
	printf("\n");

	printf("key:\n");
	phex(key);
	printf("\n");

	// print the resulting cipher as 4 x 16 byte strings
	printf("ciphertext:\n");

	for (i = 0; i < 4; ++i)
	{
		encrypt(key, plain_text, 16);
		phex(plain_text + (i * 16));
	}
	printf("\n");
}


static int test_encrypt_ecb(void)
{
	uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
    uint8_t out[] = { 0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97 };

	uint8_t in[]  = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
	encrypt(key, in, 16);

	printf("ECB encrypt: ");

	if (0 == memcmp((char*) out, (char*) in, 16)) {
		printf("SUCCESS!\n");
		return(0);
	} else {
		printf("FAILURE!\n");
		return(1);
	}
}

static int test_decrypt_ecb(void)
{
	uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
	uint8_t in[]  = { 0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97 };

	uint8_t out[]   = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };

	decrypt(key, in, 16);

	printf("ECB decrypt: ");

	if (0 == memcmp((char*) out, (char*) in, 16)) {
		printf("SUCCESS!\n");
		return(0);
	} else {
		printf("FAILURE!\n");
		return(1);
	}
}


static int test_encrypt_hello_ecb(void)
{
	char key[16] = "aaaabbbbccccdddd";
	uint8_t out[] = { 0x00, 0x23, 0xA3, 0x49, 0x04, 0x3D, 0x91, 0xF1, 0x08, 0xF3, 0xE0, 0xD2, 0xD3, 0xFA, 0xBA, 0xDE };

	char in[16]  = "Hello worldddd!\0";
	encrypt(key, in, 16);

	printf("ECB encrypt: ");

	if (0 == memcmp((char*) out, (char*) in, 16)) {
		printf("SUCCESS!\n");
		return(0);
	} else {
		printf("FAILURE!\n");
		return(1);
	}
}

static int test_decrypt_hello_ecb(void)
{
	uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };
	uint8_t in[]  = { 0x3a, 0xd7, 0x7b, 0xb4, 0x0d, 0x7a, 0x36, 0x60, 0xa8, 0x9e, 0xca, 0xf3, 0x24, 0x66, 0xef, 0x97 };

	uint8_t out[]   = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };

	decrypt(key, in, 16);

	printf("ECB decrypt: ");

	if (0 == memcmp((char*) out, (char*) in, 16)) {
		printf("SUCCESS!\n");
		return(0);
	} else {
		printf("FAILURE!\n");
		return(1);
	}
}