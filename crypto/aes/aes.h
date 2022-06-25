//
//  aes.h
//  genpass
//
//  Created by Sylvan Martin on 8/6/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

#ifndef aes_h
#define aes_h

#include <stdio.h>

#include "crypto.h"

// MARK: - Intel Low Level AES Routines

/*
 * All Intel Low Level AES Routines written by Intel, not me.
 */

inline void KEY_256_ASSIST_1(__m128i *temp1, __m128i *temp2);

inline void KEY_256_ASSIST_2(__m128i *temp1, __m128i *temp3);

void AES_256_Key_Expansion (const uint64_t *userkey, __m128i *key);

// MARK: - High Level AES Routines

/**
 * Encrypts a single 128-bit block using AES with a 256 bit key
 *
 * @param plain_block An array of two 64 bit words to make one 128 bit block to be encrypted
 * @param key An array of 4 64 bit words to make one 256 bit key
 * @param cipher_block array to store the result of the encryption
 */
int aesenc_block_256(uint64_t plain_block[BLOCK_LENGTH_WORDS],
                     const uint64_t key[KEY_LENGTH_WORDS],
                     uint64_t cipher_block[KEY_LENGTH_WORDS]);

/**
 * @pre The plaintext is propperly padded, the first block is the IV.
 *
 * @param plaintext the data to encrypt. The first block of this data should be a random initialization vector
 * @param key The key for encryption
 * @param ciphertext where to store the result of the encryption
 * @param len the length of the plaintext and ciphertext in 128-bit blocks
 */
int aesenc_256(uint64_t *plaintext,
               const uint64_t key[KEY_LENGTH_WORDS],
               uint64_t *ciphertext,
               size_t len);

#endif /* aes_h */
