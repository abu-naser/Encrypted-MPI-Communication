/***************************
 C wrapper file for cryptopp
 an16e@my.fsu.edu
****************************/

#ifndef __GCM3HEADER_H
#define __GCM3HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

extern void wrapper_encrypt(  char *buf,  char *ciphertext , int count, unsigned long key_size);
extern void wrapper_decrypt(  char *ciphertext,  char *buf , int count, unsigned long key_size);
//extern void wrapper_init_cryptopp(  unsigned long key_size );

#ifdef __cplusplus
}
#endif
#endif
