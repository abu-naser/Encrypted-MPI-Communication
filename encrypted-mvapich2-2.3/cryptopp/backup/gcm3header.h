#ifndef __GCM3HEADER_H
#define __GCM3HEADER_H

#ifdef __cplusplus
extern "C" {
#endif

extern int encrypt( char *buf,  char *ciphertext , int count);

extern int decrypt( char *ciphertext,  char *buf , int count);

#ifdef __cplusplus
}
#endif
#endif

