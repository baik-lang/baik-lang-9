// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2015
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia


#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>

void encrypt_des(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len, out_len=0;
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&result, '\0', sizeof(result));
     memset(&ctx, '\0', sizeof(ctx));
     out_len=0;
     in_len = strlen(plaintext);
     // printf("Orig plain: %s\n", plaintext);

     EVP_EncryptInit(&ctx, EVP_des_cbc(), mykey, iv);
     EVP_EncryptUpdate(&ctx, ciphertext, &out_len, plaintext, in_len);
     EVP_EncryptFinal(&ctx, &ciphertext[out_len], &out_len);
     // printf("3DES Encrypted : %s\n", ciphertext);
}

void decrypt_des(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len=0, n=0,
		 out_len=MAX_STRING_LEN; // max buffer for original msg
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&ctx, '\0', sizeof(ctx));
     memset(&result, '\0', sizeof(result));

     EVP_DecryptInit(&ctx, EVP_des_cbc(), mykey, iv);
     EVP_DecryptUpdate(&ctx, result, &in_len, ciphertext, out_len);
     EVP_DecryptFinal(&ctx, &result[in_len], &in_len);

     n=0;
     do {
       n++;
     } while(isalnum(result[n]) || isspace(result[n]) ||
             ispunct(result[n]) || isgraph(result[n]));
     result[n] = '\0';

	 strcpy(plaintext, result);
     // printf("3DES Decrypted : %s\n", result);
     memset(&result, '\0', sizeof(result));
}

// -----------------------------------------------------------------

void encrypt_3des(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len, out_len=0;
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&result, '\0', sizeof(result));
     memset(&ctx, '\0', sizeof(ctx));
     out_len=0;
     in_len = strlen(plaintext);
     // printf("Orig plain: %s\n", plaintext);

     EVP_EncryptInit(&ctx, EVP_des_ede3_cbc(), mykey, iv);
     EVP_EncryptUpdate(&ctx, ciphertext, &out_len, plaintext, in_len);
     EVP_EncryptFinal(&ctx, &ciphertext[out_len], &out_len);
     // printf("3DES Encrypted : %s\n", ciphertext);
}

void decrypt_3des(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len=0, n=0,
		 out_len=MAX_STRING_LEN; // max buffer for original msg
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&ctx, '\0', sizeof(ctx));
     memset(&result, '\0', sizeof(result));

     EVP_DecryptInit(&ctx, EVP_des_ede3_cbc(), mykey, iv);
     EVP_DecryptUpdate(&ctx, result, &in_len, ciphertext, out_len);
     EVP_DecryptFinal(&ctx, &result[in_len], &in_len);

     n=0;
     do {
       n++;
     } while(isalnum(result[n]) || isspace(result[n]) ||
             ispunct(result[n]) || isgraph(result[n]));
     result[n] = '\0';

	 strcpy(plaintext, result);
     // printf("3DES Decrypted : %s\n", result);
     memset(&result, '\0', sizeof(result));
}

// -----------------------------------------------------------------

void encrypt_rc4(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len, out_len=0;
     int n=0, in_len2=0;
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&result, '\0', sizeof(result));
     memset(&ctx, '\0', sizeof(ctx));
     out_len=0;
     in_len = strlen(plaintext);
     // printf("Orig plain: %s\n", plaintext);

     EVP_EncryptInit(&ctx, EVP_rc4(), mykey, iv);
     EVP_EncryptUpdate(&ctx, ciphertext, &out_len, plaintext, in_len);
     EVP_EncryptFinal(&ctx, &ciphertext[out_len], &out_len);
     printf("rc4 Encrypted : %s\n", ciphertext);

     EVP_DecryptInit(&ctx, EVP_rc4(), mykey, iv);
     EVP_DecryptUpdate(&ctx, result, &in_len2, ciphertext, 100);
     EVP_DecryptFinal(&ctx, &result[in_len2], &in_len2);

     printf("RC4 Decrypted 0 : %s\n", result);

	  n=0;
     do {
       n++;
     } while(isalnum(result[n]) || isspace(result[n]) ||
             ispunct(result[n]) || isgraph(result[n]));
     result[n] = '\0';

     printf("rc4 Decrypted 1 : %s\n", result);
}

void decrypt_rc4(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len=0, n=0,
		 out_len=MAX_STRING_LEN; // max buffer for original msg
     int in_len2=0;
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&ctx, '\0', sizeof(ctx));
     memset(&result, '\0', sizeof(result));

	 printf("rc4 orig : %s\n", ciphertext);

     EVP_DecryptInit(&ctx, EVP_rc4(), mykey, iv);
     EVP_DecryptUpdate(&ctx, result, &in_len2, ciphertext, 100);
     EVP_DecryptFinal(&ctx, &result[in_len2], &in_len2);
     printf("rc4 orig Decrypted : %s\n", result);

     n=0;
     do {
       n++;
     } while(isalnum(result[n]) || isspace(result[n]) ||
             ispunct(result[n]) || isgraph(result[n]));
     result[n] = '\0';

	 strcpy(plaintext, result);
     printf("rc4 Decrypted : %s\n", result);
     memset(&result, '\0', sizeof(result));
}

// -----------------------------------------------------------------

void encrypt_aes128ecb(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len, out_len=0;
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&result, '\0', sizeof(result));
     memset(&ctx, '\0', sizeof(ctx));
     out_len=0;
     in_len = strlen(plaintext);
     // printf("Orig plain: %s\n", plaintext);

     EVP_EncryptInit(&ctx, EVP_aes_128_ecb(), mykey, iv);
     EVP_EncryptUpdate(&ctx, ciphertext, &out_len, plaintext, in_len);
     EVP_EncryptFinal(&ctx, &ciphertext[out_len], &out_len);
     // printf("AES128ECB Encrypted : %s\n", ciphertext);
}

void decrypt_aes128ecb(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len=0, n=0,
		 out_len=MAX_STRING_LEN; // max buffer for original msg
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&ctx, '\0', sizeof(ctx));
     memset(&result, '\0', sizeof(result));

     EVP_DecryptInit(&ctx, EVP_aes_128_ecb(), mykey, iv);
     EVP_DecryptUpdate(&ctx, result, &in_len, ciphertext, out_len);
     EVP_DecryptFinal(&ctx, &result[in_len], &in_len);

     n=0;
     do {
       n++;
     } while(isalnum(result[n]) || isspace(result[n]) ||
             ispunct(result[n]) || isgraph(result[n]));
     result[n] = '\0';

	 strcpy(plaintext, result);
     // printf("AES128ECB Decrypted : %s\n", result);
     memset(&result, '\0', sizeof(result));
}

// -----------------------------------------------------------------

void encrypt_aes128cbc(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len, out_len=0;
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&result, '\0', sizeof(result));
     memset(&ctx, '\0', sizeof(ctx));
     out_len=0;
     in_len = strlen(plaintext);
     // printf("Orig plain: %s\n", plaintext);

     EVP_EncryptInit(&ctx, EVP_aes_128_cbc(), mykey, iv);
     EVP_EncryptUpdate(&ctx, ciphertext, &out_len, plaintext, in_len);
     EVP_EncryptFinal(&ctx, &ciphertext[out_len], &out_len);
     // printf("AES128ECB Encrypted : %s\n", ciphertext);
}

void decrypt_aes128cbc(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len=0, n=0,
		 out_len=MAX_STRING_LEN; // max buffer for original msg
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&ctx, '\0', sizeof(ctx));
     memset(&result, '\0', sizeof(result));

     EVP_DecryptInit(&ctx, EVP_aes_128_cbc(), mykey, iv);
     EVP_DecryptUpdate(&ctx, result, &in_len, ciphertext, out_len);
     EVP_DecryptFinal(&ctx, &result[in_len], &in_len);

     n=0;
     do {
       n++;
     } while(isalnum(result[n]) || isspace(result[n]) ||
             ispunct(result[n]) || isgraph(result[n]));
     result[n] = '\0';

	 strcpy(plaintext, result);
     // printf("AES128ECB Decrypted : %s\n", result);
     memset(&result, '\0', sizeof(result));
}

// -----------------------------------------------------------------

void encrypt_blowfishcbc(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len, out_len=0;
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&result, '\0', sizeof(result));
     memset(&ctx, '\0', sizeof(ctx));
     out_len=0;
     in_len = strlen(plaintext);
     // printf("Orig plain: %s\n", plaintext);

     EVP_EncryptInit(&ctx, EVP_bf_cbc(), mykey, iv);
     EVP_EncryptUpdate(&ctx, ciphertext, &out_len, plaintext, in_len);
     EVP_EncryptFinal(&ctx, &ciphertext[out_len], &out_len);
     // printf("rc4 Encrypted : %s\n", ciphertext);
}

void decrypt_blowfishcbc(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len=0, n=0,
		 out_len=MAX_STRING_LEN; // max buffer for original msg
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&ctx, '\0', sizeof(ctx));
     memset(&result, '\0', sizeof(result));

     EVP_DecryptInit(&ctx, EVP_bf_cbc(), mykey, iv);
     EVP_DecryptUpdate(&ctx, result, &in_len, ciphertext, out_len);
     EVP_DecryptFinal(&ctx, &result[in_len], &in_len);

     n=0;
     do {
       n++;
     } while(isalnum(result[n]) || isspace(result[n]) ||
             ispunct(result[n]) || isgraph(result[n]));
     result[n] = '\0';

	 strcpy(plaintext, result);
     // printf("rc4 Decrypted : %s\n", result);
     memset(&result, '\0', sizeof(result));
}

// -----------------------------------------------------------------

void encrypt_blowfishcfb(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len, out_len=0;
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&result, '\0', sizeof(result));
     memset(&ctx, '\0', sizeof(ctx));
     out_len=0;
     in_len = strlen(plaintext);
     // printf("Orig plain: %s\n", plaintext);

     EVP_EncryptInit(&ctx, EVP_bf_cfb(), mykey, iv);
     EVP_EncryptUpdate(&ctx, ciphertext, &out_len, plaintext, in_len);
     EVP_EncryptFinal(&ctx, &ciphertext[out_len], &out_len);
     // printf("rc4 Encrypted : %s\n", ciphertext);
}

void decrypt_blowfishcfb(char plaintext[MAX_STRING_LEN], char ciphertext[MAX_STRING_LEN], char mykey[EVP_MAX_KEY_LENGTH]) {
     char iv[EVP_MAX_IV_LENGTH] = "my iv";
     int in_len=0, n=0,
		 out_len=MAX_STRING_LEN; // max buffer for original msg
     EVP_CIPHER_CTX ctx;
	 char result[MAX_STRING_LEN];

     memset(&ctx, '\0', sizeof(ctx));
     memset(&result, '\0', sizeof(result));

     EVP_DecryptInit(&ctx, EVP_bf_cfb(), mykey, iv);
     EVP_DecryptUpdate(&ctx, result, &in_len, ciphertext, out_len);
     EVP_DecryptFinal(&ctx, &result[in_len], &in_len);

     n=0;
     do {
       n++;
     } while(isalnum(result[n]) || isspace(result[n]) ||
             ispunct(result[n]) || isgraph(result[n]));
     result[n] = '\0';

	 strcpy(plaintext, result);
     // printf("rc4 Decrypted : %s\n", result);
     memset(&result, '\0', sizeof(result));
}

// -----------------------------------------------------------------


