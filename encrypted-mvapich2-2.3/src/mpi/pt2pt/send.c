/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

/* Copyright (c) 2001-2018, The Ohio State University. All rights
 * reserved.
 *
 * This file is part of the MVAPICH2 software package developed by the
 * team members of The Ohio State University's Network-Based Computing
 * Laboratory (NBCL), headed by Professor Dhabaleswar K. (DK) Panda.
 *
 * For detailed copyright and licensing information, please refer to the
 * copyright file COPYRIGHT in the top level MVAPICH2 directory.
 *
 */

#include "mpiimpl.h"

#if BORINGSSL_LIB
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/err.h>
#include <openssl/aead.h>
unsigned char ciphertext[4194304+18];
EVP_AEAD_CTX *ctx = NULL;
unsigned char key [32] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f'};
unsigned char nonce[12] = {'1','2','3','4','5','6','7','8','9','0','1','2'};  
int nonceCounter; 

#elif OPENSSL_LIB
unsigned int outlen_enc;
EVP_CIPHER_CTX *ctx_enc;
int nonceCounter=0,amount,sct_sz,pre_next;
const unsigned char gcm_key[32] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f'};
unsigned char send_ciphertext[4194304+400];
#elif LIBSODIUM_LIB
CRYPTO_ALIGN(16) crypto_aead_aes256gcm_state ctx;
unsigned char key [32] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f'};
unsigned char send_ciphertext[4194304+18];
int nonceCounter;
#elif CRYPTOPP_LIB
int nonceCounter=0;
unsigned long key_size=32;
unsigned char send_ciphertext[4194304+18];
unsigned char gcm_key[32] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f'};
#endif



/* -- Begin Profiling Symbol Block for routine MPI_Send */
#if defined(HAVE_PRAGMA_WEAK)
#pragma weak MPI_Send = PMPI_Send
#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#pragma _HP_SECONDARY_DEF PMPI_Send  MPI_Send
#elif defined(HAVE_PRAGMA_CRI_DUP)
#pragma _CRI duplicate MPI_Send as PMPI_Send
#elif defined(HAVE_WEAK_ATTRIBUTE)
int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag,
             MPI_Comm comm) __attribute__((weak,alias("PMPI_Send")));
#endif
/* -- End Profiling Symbol Block */

/* Define MPICH_MPI_FROM_PMPI if weak symbols are not supported to build
   the MPI routines */
#ifndef MPICH_MPI_FROM_PMPI
#undef MPI_Send
#define MPI_Send PMPI_Send

#endif

#undef FUNCNAME
#define FUNCNAME MPI_Send

/*@
    MPI_Send - Performs a blocking send

Input Parameters:
+ buf - initial address of send buffer (choice) 
. count - number of elements in send buffer (nonnegative integer) 
. datatype - datatype of each send buffer element (handle) 
. dest - rank of destination (integer) 
. tag - message tag (integer) 
- comm - communicator (handle) 

Notes:
This routine may block until the message is received by the destination 
process.

.N ThreadSafe

.N Fortran

.N Errors
.N MPI_SUCCESS
.N MPI_ERR_COMM
.N MPI_ERR_COUNT
.N MPI_ERR_TYPE
.N MPI_ERR_TAG
.N MPI_ERR_RANK

.seealso: MPI_Isend, MPI_Bsend
@*/
int MPI_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag,
	     MPI_Comm comm)
{
    static const char FCNAME[] = "MPI_Send";
    int mpi_errno = MPI_SUCCESS;
    MPID_Comm *comm_ptr = NULL;
    MPID_Request * request_ptr = NULL;
    MPID_MPI_STATE_DECL(MPID_STATE_MPI_SEND);

    MPIR_ERRTEST_INITIALIZED_ORDIE();
    
    MPID_THREAD_CS_ENTER(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    MPID_MPI_PT2PT_FUNC_ENTER_FRONT(MPID_STATE_MPI_SEND);
    
    /* Validate handle parameters needing to be converted */
#   ifdef HAVE_ERROR_CHECKING
    {
        MPID_BEGIN_ERROR_CHECKS;
        {
	    MPIR_ERRTEST_COMM(comm, mpi_errno);
	}
        MPID_END_ERROR_CHECKS;
    }
#   endif /* HAVE_ERROR_CHECKING */
    
    /* Convert MPI object handles to object pointers */
    MPID_Comm_get_ptr( comm, comm_ptr );

    /* Validate parameters if error checking is enabled */
#   ifdef HAVE_ERROR_CHECKING
    {
        MPID_BEGIN_ERROR_CHECKS;
        {
            MPID_Comm_valid_ptr( comm_ptr, mpi_errno, FALSE );
            if (mpi_errno) goto fn_fail;
	    
	    MPIR_ERRTEST_COUNT(count, mpi_errno);
	    MPIR_ERRTEST_SEND_RANK(comm_ptr, dest, mpi_errno);
	    MPIR_ERRTEST_SEND_TAG(tag, mpi_errno);
	    
	    /* Validate datatype handle */
	    MPIR_ERRTEST_DATATYPE(datatype, "datatype", mpi_errno);
	    
	    /* Validate datatype object */
	    if (HANDLE_GET_KIND(datatype) != HANDLE_KIND_BUILTIN)
	    {
		MPID_Datatype *datatype_ptr = NULL;

		MPID_Datatype_get_ptr(datatype, datatype_ptr);
		MPID_Datatype_valid_ptr(datatype_ptr, mpi_errno);
		if (mpi_errno) goto fn_fail;
		MPID_Datatype_committed_ptr(datatype_ptr, mpi_errno);
		if (mpi_errno) goto fn_fail;
	    }
	    
	    /* Validate buffer */
	    MPIR_ERRTEST_USERBUFFER(buf,count,datatype,mpi_errno);
        }
        MPID_END_ERROR_CHECKS;
    }
#   endif /* HAVE_ERROR_CHECKING */

    /* ... body of routine ...  */
    
    mpi_errno = MPID_Send(buf, count, datatype, dest, tag, comm_ptr, 
			  MPID_CONTEXT_INTRA_PT2PT, &request_ptr);
    if (mpi_errno != MPI_SUCCESS) goto fn_fail;

    if (request_ptr == NULL)
    {
#if defined(CHANNEL_MRAIL)
        mpi_errno = MPID_Progress_test();
        if (mpi_errno != MPI_SUCCESS)
        {
            goto fn_fail;
        }
#endif /* defined(CHANNEL_MRAIL) */
	goto fn_exit;
    }

    /* If a request was returned, then we need to block until the request 
       is complete */
    if (!MPID_Request_is_complete(request_ptr))
    {
	MPID_Progress_state progress_state;
	    
	MPID_Progress_start(&progress_state);
        while (!MPID_Request_is_complete(request_ptr))
	{
	    mpi_errno = MPID_Progress_wait(&progress_state);
	    if (mpi_errno != MPI_SUCCESS)
	    {
		/* --BEGIN ERROR HANDLING-- */
		MPID_Progress_end(&progress_state);
		goto fn_fail;
		/* --END ERROR HANDLING-- */
	    }
	}
	MPID_Progress_end(&progress_state);
    }

    mpi_errno = request_ptr->status.MPI_ERROR;
    MPID_Request_release(request_ptr);
    
    if (mpi_errno != MPI_SUCCESS) goto fn_fail;

    /* ... end of body of routine ... */
    
  fn_exit:
    MPID_MPI_PT2PT_FUNC_EXIT(MPID_STATE_MPI_SEND);
    MPID_THREAD_CS_EXIT(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    return mpi_errno;

  fn_fail:
    /* --BEGIN ERROR HANDLING-- */
#   ifdef HAVE_ERROR_CHECKING
    {
	mpi_errno = MPIR_Err_create_code(
	    mpi_errno, MPIR_ERR_RECOVERABLE, FCNAME, __LINE__, MPI_ERR_OTHER, "**mpi_send", 
	    "**mpi_send %p %d %D %i %t %C", buf, count, datatype, dest, tag, comm);
    }
#   endif
    mpi_errno = MPIR_Err_return_comm( comm_ptr, FCNAME, mpi_errno );
    goto fn_exit;
    /* --END ERROR HANDLING-- */
}


#if BORINGSSL_LIB
/* variable nonce implementation */
int MPI_SEC_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag,
	     MPI_Comm comm)
{
    int mpi_errno = MPI_SUCCESS;
    unsigned long ciphertext_len=0;
    int  sendtype_sz;           
    
    MPI_Type_size(datatype, &sendtype_sz);         
    unsigned long   max_out_len = (unsigned long) (16 + (sendtype_sz*count));
    
    /* Set the nonce in send_ciphertext */
	RAND_bytes(ciphertext, 12); // 12 bytes of nonce
    /* nonceCounter++;
    memset(ciphertext, 0, 8);
    ciphertext[8] = (nonceCounter >> 24) & 0xFF;
    ciphertext[9] = (nonceCounter >> 16) & 0xFF;
    ciphertext[10] = (nonceCounter >> 8) & 0xFF;
    ciphertext[11] = nonceCounter & 0xFF; */

    /* ciphertext's first 12 byte is now nonce. so cipher will start from */
    /* ciphertext+12. And nonce is from ciphertext                   */    
    if(!EVP_AEAD_CTX_seal(ctx, ciphertext+12,
                         &ciphertext_len, max_out_len,
                         ciphertext, 12,
                         buf,  (unsigned long)(count*sendtype_sz),
                        NULL, 0)){
              printf("error in encryption\n");
              fflush(stdout);
        }
    
    /* Sending additional 12 bytes for nonce */  
	mpi_errno = MPI_Send(ciphertext, ciphertext_len+12, MPI_CHAR, dest, tag, comm);

    return mpi_errno;
}
#elif OPENSSL_LIB
void openssl_enc_core(unsigned char *send_ciphertext , unsigned long long src,const void *sendbuf,
                      unsigned long long dest, unsigned long long blocktype_send){  
    

	RAND_bytes(send_ciphertext+src, 12);
    EVP_EncryptInit_ex(ctx_enc, NULL, NULL, NULL, send_ciphertext+src);
    EVP_EncryptUpdate(ctx_enc, send_ciphertext+src+12, &outlen_enc, sendbuf+dest, blocktype_send);
    EVP_EncryptFinal_ex(ctx_enc, send_ciphertext+12+src+outlen_enc, &outlen_enc);
    EVP_CIPHER_CTX_ctrl(ctx_enc, EVP_CTRL_GCM_GET_TAG, 16, send_ciphertext+12+src+blocktype_send);

}

int MPI_SEC_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
    int mpi_errno = MPI_SUCCESS;
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int i=0;
			
	char * ciphertext;
	int sendtype_sz;
	unsigned long long next, src;
	MPI_Type_size(datatype, &sendtype_sz);
    	
	unsigned long long blocktype_send= (unsigned long long) sendtype_sz*count;
	
	
	openssl_enc_core(send_ciphertext,0,buf,0,blocktype_send);
		
    // BIO_dump_fp(stdout, ciphertext, count+16);
	
	//with IV size 12, tag size 16
	mpi_errno=MPI_Send(send_ciphertext,blocktype_send+16+12, MPI_CHAR, dest, tag, comm);

	return mpi_errno;
}
#elif LIBSODIUM_LIB
/* This implementation will use unique nonce for each message */
int MPI_SEC_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{

int mpi_errno = MPI_SUCCESS;
int i;
int var;
unsigned long long ciphertext_len=0;
int * val;
unsigned char * c;


int  sendtype_sz=0;           
MPI_Type_size(datatype, &sendtype_sz);

 MPID_Comm *comm_ptr = NULL;
    MPID_Comm_get_ptr( comm, comm_ptr );
    int rank;
    rank = comm_ptr->rank; 

int total = sendtype_sz * count;

/* Set the nonce in send_ciphertext */
randombytes_buf(send_ciphertext, 12);
/*nonceCounter++;
memset(send_ciphertext, 0, 8);
send_ciphertext[8] = (nonceCounter >> 24) & 0xFF;
send_ciphertext[9] = (nonceCounter >> 16) & 0xFF;
send_ciphertext[10] = (nonceCounter >> 8) & 0xFF;
send_ciphertext[11] = nonceCounter & 0xFF;*/

/* send_ciphertext's first 12 byte is now nonce. so cipher will start from */
/* send_ciphertext+12. And nonce is from send_ciphertext                   */
var = crypto_aead_aes256gcm_encrypt_afternm(send_ciphertext+12,&ciphertext_len,
            buf, total,
            NULL, 0,
            NULL, send_ciphertext, (const crypto_aead_aes256gcm_state *) &ctx); 
 if(var != 0){
        printf("Encryption failed\n");
        fflush(stdout);
    }

/* Sending additional 12 bytes for nonce */  
mpi_errno=MPI_Send(send_ciphertext, ciphertext_len+12, MPI_CHAR, dest, tag, comm);

return mpi_errno;

}


#elif CRYPTOPP_LIB
int MPI_SEC_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm)
{
	int mpi_errno = MPI_SUCCESS;

	int ciphertext_len = 0;

	//unsigned char * ciphertext;
    int  sendtype_sz;        

	//unsigned char gcm_key[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	//wrapper_nonce(unsigned char * nonce, unsigned long nonce_len)
	wrapper_nonce(send_ciphertext, 12);
	//memset(&send_ciphertext, 0, 12);
	    
	/* nonceCounter++;
	memset(&send_ciphertext, 0, 8);
	send_ciphertext[8] = (nonceCounter >> 24) & 0xFF;
	send_ciphertext[9] = (nonceCounter >> 16) & 0xFF;
	send_ciphertext[10] = (nonceCounter >> 8) & 0xFF;
	send_ciphertext[11] = nonceCounter & 0xFF; */
    
    MPI_Type_size(datatype, &sendtype_sz);

	//wrapper_encrypt( char *sendbuf ,  char *ciphertext , int datacount, unsigned long key_size, unsigned char *key, unsigned char *nonce)
	wrapper_encrypt( buf ,  send_ciphertext+12 , sendtype_sz*count, key_size, gcm_key, send_ciphertext);
	
    ciphertext_len= count* sendtype_sz+12+12;
	mpi_errno=MPI_Send(send_ciphertext, ciphertext_len, MPI_CHAR, dest, tag, comm);

	return mpi_errno;

}
#endif

/* Fixed nonce implementation */
#if 0
int MPI_SEC_Send(const void *buf, int count, MPI_Datatype datatype, int dest, int tag,
	     MPI_Comm comm)
{
    int mpi_errno = MPI_SUCCESS;
    unsigned long ciphertext_len=0;
    int  sendtype_sz;           
    
    MPI_Type_size(datatype, &sendtype_sz);         
    unsigned long   max_out_len = (unsigned long) (16 + (sendtype_sz*count));
    
    if(!EVP_AEAD_CTX_seal(ctx, ciphertext,
                         &ciphertext_len, max_out_len,
                         nonce, 12,
                         buf,  (unsigned long)(count*sendtype_sz),
                        NULL, 0)){
              printf("error in encryption\n");
              fflush(stdout);
        }
    
	mpi_errno = MPI_Send(ciphertext, ciphertext_len, MPI_CHAR, dest, tag, comm);

    return mpi_errno;
}
#endif


#if BORINGSSL_LIB
void init_crypto(){
    nonceCounter=0;
    ctx = EVP_AEAD_CTX_new(EVP_aead_aes_256_gcm_siv(),
                            key,
                            32, 0);
    return;                        
}


void init_boringssl_256_siv(){
   
    nonceCounter=0;
    ctx = EVP_AEAD_CTX_new(EVP_aead_aes_256_gcm_siv(),
                            key,
                            32, 0);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    return;                        
}

void init_boringssl_128_siv(){
   
    nonceCounter=0;
	
    ctx = EVP_AEAD_CTX_new(EVP_aead_aes_128_gcm_siv(),
                            key,
                            16, 0);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
    return;                        
}

void init_boringssl_128(){
  
    nonceCounter=0;
    ctx = EVP_AEAD_CTX_new(EVP_aead_aes_128_gcm(),
                            key,
                            16, 0);
    int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	return;                        
}

void init_boringssl_256(){
   
    nonceCounter=0;
    ctx = EVP_AEAD_CTX_new(EVP_aead_aes_256_gcm(),
                            key,
                            32, 0);
    int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	return;                        
}
#elif OPENSSL_LIB
void init_openssl_128(){
   // printf("set the key now\n");fflush(stdout);

    ctx_enc = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx_enc, EVP_aes_128_gcm(), NULL, gcm_key, NULL);
    EVP_CIPHER_CTX_ctrl(ctx_enc, EVP_CTRL_GCM_SET_IVLEN, (int)12, NULL);


    ctx_dec = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx_dec, EVP_aes_128_gcm(), NULL, gcm_key, NULL);
    EVP_CIPHER_CTX_ctrl(ctx_dec, EVP_CTRL_GCM_SET_IVLEN, (int)12, NULL);
	
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	//if (world_rank == 0) printf("\n\t\t****** Secure MPI with OpenSSL  128  GCM ********\n");
    return;                        
}

//void init_openssl_256(){
    void init_crypto(){	
    //printf("set the key now\n");fflush(stdout);

    ctx_enc = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx_enc, EVP_aes_256_gcm(), NULL, gcm_key, NULL);
    EVP_CIPHER_CTX_ctrl(ctx_enc, EVP_CTRL_GCM_SET_IVLEN, (int)12, NULL);


    ctx_dec = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx_dec, EVP_aes_256_gcm(), NULL, gcm_key, NULL);
    EVP_CIPHER_CTX_ctrl(ctx_dec, EVP_CTRL_GCM_SET_IVLEN, (int)12, NULL);
	
	//int world_rank;
	//MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	//if (world_rank == 0) printf("\n\t\t****** Secure MPI with OpenSSL  256  GCM ********\n");
    return;                        
}

#elif LIBSODIUM_LIB
/* Initializaiton of lib sodium */
void init_crypto(){
    int var= sodium_init();
    nonceCounter = 0;
    var = crypto_aead_aes256gcm_beforenm(&ctx, key);
    return;
}
#elif CRYPTOPP_LIB
// void cryptopp_init(unsigned long user_key_size){
void init_crypto(){	
	key_size=32;
    unsigned char iv[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	/* int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	if (world_rank == 0){
		if (user_key_size==16) printf("\n\t\t****** Secure MPI with CryptoPP 128  GCM ********\n");
		else if (user_key_size==32) printf("\n\t\t****** Secure MPI with CryptoPP 256  GCM ********\n");
    }*/
    wrapper_init_cryptopp( key_size,  gcm_key,   iv); 
}
#endif

/*End of adding */
