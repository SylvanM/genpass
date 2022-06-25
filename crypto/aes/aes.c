//
//  aes.c
//  genpass
//
//  Created by Sylvan Martin on 8/6/20.
//  Copyright © 2020 Sylvan Martin. All rights reserved.
//

#include "aes.h"

// MARK: - Intel Code

inline void KEY_256_ASSIST_1(__m128i *temp1, __m128i *temp2) {
    
    __m128i temp4;
    *temp2 = _mm_shuffle_epi32 (*temp2, 0xff);
    temp4 = _mm_slli_si128 (*temp1, 0x4);
    *temp1 = _mm_xor_si128 (*temp1, temp4);
    temp4 = _mm_slli_si128 (temp4, 0x4);
    *temp1 = _mm_xor_si128 (*temp1, temp4);
    temp4 = _mm_slli_si128 (temp4, 0x4);
    *temp1 = _mm_xor_si128 (*temp1, temp4);
    *temp1 = _mm_xor_si128 (*temp1, *temp2);
    
}

inline void KEY_256_ASSIST_2(__m128i *temp1, __m128i *temp3) {
    
    __m128i temp2, temp4;
    temp4 = _mm_aeskeygenassist_si128(*temp1, 0x0);
    temp2 = _mm_shuffle_epi32(temp4, 0xaa);
    temp4 = _mm_slli_si128 (*temp3, 0x4);
    *temp3 = _mm_xor_si128 (*temp3, temp4);
    temp4 = _mm_slli_si128 (temp4, 0x4);
    *temp3 = _mm_xor_si128 (*temp3, temp4);
    temp4 = _mm_slli_si128 (temp4, 0x4);
    *temp3 = _mm_xor_si128 (*temp3, temp4);
    *temp3 = _mm_xor_si128 (*temp3, temp2);
    
}

void AES_256_Key_Expansion (const uint64_t *userkey, __m128i *key) {
    
    __m128i temp1, temp2, temp3;
    
    temp1 = _mm_loadu_si128( (__m128i *) userkey);
    temp3 = _mm_loadu_si128( (__m128i *) userkey + 16);
    
    key[0] = temp1;
    key[1] = temp3;
    
    // Intel has some built in AES instructions and also some instrinsic functions that I'm trying to use here.
    
    // this code gives me the following error:
    // "'__builtin_ia32_aeskeygenassist128' needs target feature aes"
    // I'm using Xcode to make this, so I'm assuming I need to mess around in the build settings?
    
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x01);
    KEY_256_ASSIST_1(&temp1, &temp2);
    key[2] = temp1;
    KEY_256_ASSIST_2(&temp1, &temp3);
    key[3] = temp3;
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x02);
    KEY_256_ASSIST_1(&temp1, &temp2);
    key[4] = temp1;
    KEY_256_ASSIST_2(&temp1, &temp3);
    key[5] = temp3;
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x04);
    KEY_256_ASSIST_1(&temp1, &temp2);
    key[6] = temp1;
    KEY_256_ASSIST_2(&temp1, &temp3);
    key[7] = temp3;
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x08);
    KEY_256_ASSIST_1(&temp1, &temp2);
    key[8] = temp1;
    KEY_256_ASSIST_2(&temp1, &temp3);
    key[9] = temp3;
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x010);
    KEY_256_ASSIST_1(&temp1, &temp2);
    key[10] = temp1;
    KEY_256_ASSIST_2(&temp1, &temp3);
    key[11] = temp3;
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x20);
    KEY_256_ASSIST_1(&temp1, &temp2);
    key[12] = temp1;
    KEY_256_ASSIST_2(&temp1, &temp3);
    key[13] = temp3;
    temp2 = _mm_aeskeygenassist_si128(temp3, 0x40);
    KEY_256_ASSIST_1(&temp1, &temp2);
    key[14] = temp1;
    
}

// MARK: - My Code

int aesenc_block_256(uint64_t plain_block[BLOCK_LENGTH_WORDS], const uint64_t key[KEY_LENGTH_WORDS], uint64_t cipher_block[BLOCK_LENGTH_WORDS]) {
    
    __m128i key_schedule[KEY_LENGTH_WORDS * 15];
    __m128i *feedback;
    
    AES_256_Key_Expansion(key, key_schedule);
    
    // unfinished
    
    return 0;
}

// this uses CBC, because I don't understand GCM.
int aesenc_256(uint64_t *plaintext, const uint64_t key[KEY_LENGTH_WORDS], uint64_t *ciphertext, size_t len) {
    
    // initialize this to 0 so that the first block doesn't get wrongfully XOR'd with some junk data.
    // The first block should be an IV anyway.
    uint64_t previous[BLOCK_LENGTH_WORDS] = { 0, 0 };
    
    while (len--) {
        plaintext[0] ^= previous[0];
        plaintext[1] ^= previous[1];
        
        aesenc_block_256(plaintext, key, ciphertext);
        
        previous[0] = ciphertext[0];
        previous[1] = ciphertext[1];
        
        plaintext += 2;
        ciphertext += 2;
    }
    
    return 0;
}
