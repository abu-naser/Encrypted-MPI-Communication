/***************************
 C wrapper file for cryptopp
 an16e@my.fsu.edu
****************************/

#ifndef __GCM3HEADER_H
#define __GCM3HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

extern void wrapper_encrypt(  unsigned char *buf,  unsigned char *ciphertext , int count, unsigned long key_size, 
                              unsigned char *key, unsigned char *nonce);
extern void wrapper_decrypt(  unsigned char *ciphertext,  unsigned char *buf , int count, unsigned long key_size,
                              unsigned char *key, unsigned char *nonce);
extern void wrapper_nonce(unsigned char * nonce, unsigned long nonce_len);
extern void wrapper_init_cryptopp(unsigned long key_size, unsigned char * key, unsigned char * iv);                            
//extern void wrapper_init_cryptopp(  unsigned long key_size );

#ifdef __cplusplus
}
#endif
#endif
