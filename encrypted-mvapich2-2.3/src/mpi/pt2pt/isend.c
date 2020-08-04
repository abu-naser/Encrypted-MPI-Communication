/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

/*
 * Copyright (c) 2001-2018, The Ohio State University. All rights
 * reserved.
 *
 * This file is part of the MVAPICH2 software package developed by the
 * team members of The Ohio State University's Network-Based Computing
 * Laboratory (NBCL), headed by Professor Dhabaleswar K. (DK) Panda.
 *
 * For detailed copyright and licensing information, please refer to the
 * copyright file COPYRIGHT in the top level MVAPICH2 directory.
 */

#include "mpiimpl.h"

#if ( BORINGSSL_LIB)
unsigned char Iciphertext[NON_BLOCKING_SEND_RECV_SIZE][NON_BLOCKING_SEND_RECV_SIZE_2];
int isendCounter = 0;
#elif ( OPENSSL_LIB)
#elif ( LIBSODIUM_LIB)
unsigned char Iciphertext[NON_BLOCKING_SEND_RECV_SIZE][NON_BLOCKING_SEND_RECV_SIZE_2];
int isendCounter = 0;
#elif ( CRYPTOPP_LIB)
unsigned char Iciphertext[NON_BLOCKING_SEND_RECV_SIZE][NON_BLOCKING_SEND_RECV_SIZE_2];
int isendCounter = 0;
#endif

/* -- Begin Profiling Symbol Block for routine MPI_Isend */
#if defined(HAVE_PRAGMA_WEAK)
#pragma weak MPI_Isend = PMPI_Isend
#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#pragma _HP_SECONDARY_DEF PMPI_Isend  MPI_Isend
#elif defined(HAVE_PRAGMA_CRI_DUP)
#pragma _CRI duplicate MPI_Isend as PMPI_Isend
#elif defined(HAVE_WEAK_ATTRIBUTE)
int MPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag,
              MPI_Comm comm, MPI_Request *request) __attribute__((weak,alias("PMPI_Isend")));
#endif
/* -- End Profiling Symbol Block */

/* Define MPICH_MPI_FROM_PMPI if weak symbols are not supported to build
   the MPI routines */
#ifndef MPICH_MPI_FROM_PMPI
#undef MPI_Isend
#define MPI_Isend PMPI_Isend

#endif

#undef FUNCNAME
#define FUNCNAME MPI_Isend
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
/*@
    MPI_Isend - Begins a nonblocking send

Input Parameters:
+ buf - initial address of send buffer (choice) 
. count - number of elements in send buffer (integer) 
. datatype - datatype of each send buffer element (handle) 
. dest - rank of destination (integer) 
. tag - message tag (integer) 
- comm - communicator (handle) 

Output Parameters:
. request - communication request (handle) 

.N Fortran

.N Errors
.N MPI_SUCCESS
.N MPI_ERR_COMM
.N MPI_ERR_COUNT
.N MPI_ERR_TYPE
.N MPI_ERR_TAG
.N MPI_ERR_RANK
.N MPI_ERR_EXHAUSTED

@*/
int MPI_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag,
	      MPI_Comm comm, MPI_Request *request)
{
    int mpi_errno = MPI_SUCCESS;
    MPID_Comm *comm_ptr = NULL;
    MPID_Request *request_ptr = NULL;
    MPID_MPI_STATE_DECL(MPID_STATE_MPI_ISEND);

    MPIR_ERRTEST_INITIALIZED_ORDIE();
    
    MPID_THREAD_CS_ENTER(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    MPID_MPI_PT2PT_FUNC_ENTER_FRONT(MPID_STATE_MPI_ISEND);

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
	    MPIR_ERRTEST_ARGNULL(request,"request",mpi_errno);

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
    
    mpi_errno = MPID_Isend(buf, count, datatype, dest, tag, comm_ptr,
			   MPID_CONTEXT_INTRA_PT2PT, &request_ptr);
    if (mpi_errno != MPI_SUCCESS) goto fn_fail;

    MPIR_SENDQ_REMEMBER(request_ptr,dest,tag,comm_ptr->context_id);

    /* return the handle of the request to the user */
    /* MPIU_OBJ_HANDLE_PUBLISH is unnecessary for isend, lower-level access is
     * responsible for its own consistency, while upper-level field access is
     * controlled by the completion counter */
    *request = request_ptr->handle;

    /* ... end of body of routine ... */
    
  fn_exit:
    MPID_MPI_PT2PT_FUNC_EXIT(MPID_STATE_MPI_ISEND);
    MPID_THREAD_CS_EXIT(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    return mpi_errno;
    
  fn_fail:
    /* --BEGIN ERROR HANDLING-- */
#   ifdef HAVE_ERROR_CHECKING
    {
	mpi_errno = MPIR_Err_create_code(
	    mpi_errno, MPIR_ERR_RECOVERABLE, FCNAME, __LINE__, MPI_ERR_OTHER, "**mpi_isend",
	    "**mpi_isend %p %d %D %i %t %C %p", buf, count, datatype, dest, tag, comm, request);
    }
#   endif
    mpi_errno = MPIR_Err_return_comm( comm_ptr, FCNAME, mpi_errno );
    goto fn_exit;
    /* --END ERROR HANDLING-- */
}

#if ( BORINGSSL_LIB)
/*Variable nonce*/
int MPI_SEC_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{

    int mpi_errno = MPI_SUCCESS;
    MPI_Status status;
    MPI_Request req;

    unsigned long ciphertext_len=0;
    int  sendtype_sz;           
    
    MPI_Type_size(datatype, &sendtype_sz);         
    unsigned long   max_out_len = (unsigned long) (16 + (sendtype_sz*count));

    /* Set the nonce in send_ciphertext */
    RAND_bytes(&Iciphertext[isendCounter][0], 12); // 12 bytes of nonce
    /*nonceCounter++;
    memset(&Iciphertext[isendCounter][0], 0, 8);
    Iciphertext[isendCounter][8] = (nonceCounter >> 24) & 0xFF;
    Iciphertext[isendCounter][9] = (nonceCounter >> 16) & 0xFF;
    Iciphertext[isendCounter][10] = (nonceCounter >> 8) & 0xFF;
    Iciphertext[isendCounter][11] = nonceCounter & 0xFF;*/

    if(!EVP_AEAD_CTX_seal(ctx, &Iciphertext[isendCounter][12],
                        &ciphertext_len, max_out_len,
                        &Iciphertext[isendCounter][0], 12,
                        buf,  (unsigned long)(count * sendtype_sz),
                        NULL, 0)){
                printf("Error in encryption\n");
                fflush(stdout);    
            }
         
    mpi_errno = MPI_Isend(&Iciphertext[isendCounter][0], ciphertext_len+12, MPI_CHAR, dest, tag, comm, &req);
    * request = req;
    isendCounter++;
    if(isendCounter == (NON_BLOCKING_SEND_RECV_SIZE-1))
        isendCounter=0;

    return mpi_errno;
}
#elif ( OPENSSL_LIB)
#elif ( LIBSODIUM_LIB)
/* This implementation is for variable nonce */
int MPI_SEC_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{

int mpi_errno = MPI_SUCCESS;
unsigned long long ciphertext_len; 
MPI_Request req;
int  sendtype_sz=0;           
MPI_Type_size(datatype, &sendtype_sz); 

/* Set the nonce in send_ciphertext */
randombytes_buf(&Iciphertext[isendCounter][0], 12);
/*nonceCounter++;
memset(&Iciphertext[isendCounter][0], 0, 8);
Iciphertext[isendCounter][8] = (nonceCounter >> 24) & 0xFF;
Iciphertext[isendCounter][9] = (nonceCounter >> 16) & 0xFF;
Iciphertext[isendCounter][10] = (nonceCounter >> 8) & 0xFF;
Iciphertext[isendCounter][11] = nonceCounter & 0xFF;*/

int var = crypto_aead_aes256gcm_encrypt_afternm(&Iciphertext[isendCounter][12],&ciphertext_len,
            buf, count*sendtype_sz,
            NULL, 0,
            NULL, &Iciphertext[isendCounter][0], (const crypto_aead_aes256gcm_state *) &ctx);

mpi_errno=MPI_Isend(&Iciphertext[isendCounter][0], (ciphertext_len+12), MPI_CHAR, dest, tag, comm, &req);
* request = req;
isendCounter++;

if(isendCounter == (NON_BLOCKING_SEND_RECV_SIZE-1))
    isendCounter=0;

return mpi_errno;
}
#elif ( CRYPTOPP_LIB)
int MPI_SEC_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{

    int mpi_errno = MPI_SUCCESS;
    //MPI_Status status;
    MPI_Request req;

    //unsigned long ciphertext_len=0;
    int  sendtype_sz;           
    
    MPI_Type_size(datatype, &sendtype_sz);   
	
    //unsigned long   max_out_len = (unsigned long) (12 + (sendtype_sz*count));
	//wrapper_nonce(unsigned char * nonce, unsigned long nonce_len)
	wrapper_nonce(&Iciphertext[isendCounter][0], 12);

   /*  nonceCounter++;
    memset(&Iciphertext[isendCounter][0], 0, 8);
    Iciphertext[isendCounter][8] = (nonceCounter >> 24) & 0xFF;
    Iciphertext[isendCounter][9] = (nonceCounter >> 16) & 0xFF;
    Iciphertext[isendCounter][10] = (nonceCounter >> 8) & 0xFF;
    Iciphertext[isendCounter][11] = nonceCounter & 0xFF; */

    /* int var = crypto_aead_aes256gcm_encrypt_afternm(&Iciphertext[isendCounter][12],&ciphertext_len,
            buf, count*sendtype_sz,
            NULL, 0,
            NULL, &Iciphertext[isendCounter][0], (const crypto_aead_aes256gcm_state *) &ctx);
 */
				
	//wrapper_encrypt( char *sendbuf ,  char *ciphertext , int datacount, unsigned long key_size, unsigned char *key, unsigned char *nonce)
	wrapper_encrypt( buf ,  &Iciphertext[isendCounter][12] , sendtype_sz*count, key_size, gcm_key,  &Iciphertext[isendCounter][0]);

	//ciphertext_len= count* sendtype_sz+12+12;
	
    mpi_errno = MPI_Isend(&Iciphertext[isendCounter][0], count* sendtype_sz+12+12, MPI_CHAR, dest, tag, comm, &req);
    * request = req;
    isendCounter++;
    if(isendCounter == (NON_BLOCKING_SEND_RECV_SIZE-1))
        isendCounter=0;

    return mpi_errno;
}
#endif

/*Fixed nonce*/
#if 0
int MPI_SEC_Isend(const void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request)
{

    int mpi_errno = MPI_SUCCESS;
    MPI_Status status;
    MPI_Request req;

    unsigned long ciphertext_len=0;
    int  sendtype_sz;           
    
    MPI_Type_size(datatype, &sendtype_sz);         
    unsigned long   max_out_len = (unsigned long) (16 + (sendtype_sz*count));

    if(!EVP_AEAD_CTX_seal(ctx, &Iciphertext[isendCounter][0],
                        &ciphertext_len, max_out_len,
                        nonce, 12,
                        buf,  (unsigned long)(count * sendtype_sz),
                        NULL, 0)){
                printf("Error in encryption\n");
                fflush(stdout);    
            }
         
    mpi_errno = MPI_Isend(&Iciphertext[isendCounter][0], ciphertext_len, MPI_CHAR, dest, tag, comm, &req);
    * request = req;
    isendCounter++;
    if(isendCounter == (20000-1))
        isendCounter=0;

    return mpi_errno;
}
#endif
