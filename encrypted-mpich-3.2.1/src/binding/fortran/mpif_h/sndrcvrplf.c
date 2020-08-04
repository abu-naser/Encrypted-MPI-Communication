/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*  
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 *
 * This file is automatically generated by buildiface 
 * DO NOT EDIT
 */
#include "mpi_fortimpl.h"


/* Begin MPI profiling block */
#if defined(USE_WEAK_SYMBOLS) && !defined(USE_ONLY_MPI_NAMES) 
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak MPI_SENDRECV_REPLACE = PMPI_SENDRECV_REPLACE
#pragma weak mpi_sendrecv_replace__ = PMPI_SENDRECV_REPLACE
#pragma weak mpi_sendrecv_replace_ = PMPI_SENDRECV_REPLACE
#pragma weak mpi_sendrecv_replace = PMPI_SENDRECV_REPLACE
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_SENDRECV_REPLACE = pmpi_sendrecv_replace__
#pragma weak mpi_sendrecv_replace__ = pmpi_sendrecv_replace__
#pragma weak mpi_sendrecv_replace_ = pmpi_sendrecv_replace__
#pragma weak mpi_sendrecv_replace = pmpi_sendrecv_replace__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_SENDRECV_REPLACE = pmpi_sendrecv_replace_
#pragma weak mpi_sendrecv_replace__ = pmpi_sendrecv_replace_
#pragma weak mpi_sendrecv_replace_ = pmpi_sendrecv_replace_
#pragma weak mpi_sendrecv_replace = pmpi_sendrecv_replace_
#else
#pragma weak MPI_SENDRECV_REPLACE = pmpi_sendrecv_replace
#pragma weak mpi_sendrecv_replace__ = pmpi_sendrecv_replace
#pragma weak mpi_sendrecv_replace_ = pmpi_sendrecv_replace
#pragma weak mpi_sendrecv_replace = pmpi_sendrecv_replace
#endif



#elif defined(HAVE_PRAGMA_WEAK)

#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak MPI_SENDRECV_REPLACE = PMPI_SENDRECV_REPLACE
#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_sendrecv_replace__ = pmpi_sendrecv_replace__
#elif !defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_sendrecv_replace = pmpi_sendrecv_replace
#else
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_sendrecv_replace_ = pmpi_sendrecv_replace_
#endif

#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#if defined(F77_NAME_UPPER)
#pragma _HP_SECONDARY_DEF PMPI_SENDRECV_REPLACE  MPI_SENDRECV_REPLACE
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _HP_SECONDARY_DEF pmpi_sendrecv_replace__  mpi_sendrecv_replace__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _HP_SECONDARY_DEF pmpi_sendrecv_replace  mpi_sendrecv_replace
#else
#pragma _HP_SECONDARY_DEF pmpi_sendrecv_replace_  mpi_sendrecv_replace_
#endif

#elif defined(HAVE_PRAGMA_CRI_DUP)
#if defined(F77_NAME_UPPER)
#pragma _CRI duplicate MPI_SENDRECV_REPLACE as PMPI_SENDRECV_REPLACE
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _CRI duplicate mpi_sendrecv_replace__ as pmpi_sendrecv_replace__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _CRI duplicate mpi_sendrecv_replace as pmpi_sendrecv_replace
#else
#pragma _CRI duplicate mpi_sendrecv_replace_ as pmpi_sendrecv_replace_
#endif

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_SENDRECV_REPLACE")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_SENDRECV_REPLACE")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_SENDRECV_REPLACE")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_SENDRECV_REPLACE")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace")));

#endif
#endif /* HAVE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */
/* End MPI profiling block */


/* These definitions are used only for generating the Fortran wrappers */
#if defined(USE_WEAK_SYMBOLS) && defined(USE_ONLY_MPI_NAMES)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak mpi_sendrecv_replace__ = MPI_SENDRECV_REPLACE
#pragma weak mpi_sendrecv_replace_ = MPI_SENDRECV_REPLACE
#pragma weak mpi_sendrecv_replace = MPI_SENDRECV_REPLACE
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_SENDRECV_REPLACE = mpi_sendrecv_replace__
#pragma weak mpi_sendrecv_replace_ = mpi_sendrecv_replace__
#pragma weak mpi_sendrecv_replace = mpi_sendrecv_replace__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_SENDRECV_REPLACE = mpi_sendrecv_replace_
#pragma weak mpi_sendrecv_replace__ = mpi_sendrecv_replace_
#pragma weak mpi_sendrecv_replace = mpi_sendrecv_replace_
#else
#pragma weak MPI_SENDRECV_REPLACE = mpi_sendrecv_replace
#pragma weak mpi_sendrecv_replace__ = mpi_sendrecv_replace
#pragma weak mpi_sendrecv_replace_ = mpi_sendrecv_replace
#endif
#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_SENDRECV_REPLACE")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_SENDRECV_REPLACE")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_SENDRECV_REPLACE")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_sendrecv_replace__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_sendrecv_replace__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_sendrecv_replace__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_sendrecv_replace_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_sendrecv_replace_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_sendrecv_replace_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_sendrecv_replace")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_sendrecv_replace")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_sendrecv_replace")));
extern FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#endif
#endif

#endif

/* Map the name to the correct form */
#ifndef MPICH_MPI_FROM_PMPI
#if defined(USE_WEAK_SYMBOLS)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
/* Define the weak versions of the PMPI routine*/
#ifndef F77_NAME_UPPER
extern FORT_DLL_SPEC void FORT_CALL PMPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_2USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER
extern FORT_DLL_SPEC void FORT_CALL pmpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * );

#endif

#if defined(F77_NAME_UPPER)
#pragma weak pmpi_sendrecv_replace__ = PMPI_SENDRECV_REPLACE
#pragma weak pmpi_sendrecv_replace_ = PMPI_SENDRECV_REPLACE
#pragma weak pmpi_sendrecv_replace = PMPI_SENDRECV_REPLACE
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak PMPI_SENDRECV_REPLACE = pmpi_sendrecv_replace__
#pragma weak pmpi_sendrecv_replace_ = pmpi_sendrecv_replace__
#pragma weak pmpi_sendrecv_replace = pmpi_sendrecv_replace__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak PMPI_SENDRECV_REPLACE = pmpi_sendrecv_replace_
#pragma weak pmpi_sendrecv_replace__ = pmpi_sendrecv_replace_
#pragma weak pmpi_sendrecv_replace = pmpi_sendrecv_replace_
#else
#pragma weak PMPI_SENDRECV_REPLACE = pmpi_sendrecv_replace
#pragma weak pmpi_sendrecv_replace__ = pmpi_sendrecv_replace
#pragma weak pmpi_sendrecv_replace_ = pmpi_sendrecv_replace
#endif /* Test on name mapping */

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL pmpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_SENDRECV_REPLACE")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_SENDRECV_REPLACE")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_SENDRECV_REPLACE")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_sendrecv_replace( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace_")));

#else
extern FORT_DLL_SPEC void FORT_CALL PMPI_SENDRECV_REPLACE( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_sendrecv_replace__( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_sendrecv_replace_( void*, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_sendrecv_replace")));

#endif /* Test on name mapping */
#endif /* HAVE_MULTIPLE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */

#ifdef F77_NAME_UPPER
#define mpi_sendrecv_replace_ PMPI_SENDRECV_REPLACE
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_sendrecv_replace_ pmpi_sendrecv_replace__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_sendrecv_replace_ pmpi_sendrecv_replace
#else
#define mpi_sendrecv_replace_ pmpi_sendrecv_replace_
#endif /* Test on name mapping */

#ifdef F77_USE_PMPI
/* This defines the routine that we call, which must be the PMPI version
   since we're renaming the Fortran entry as the pmpi version.  The MPI name
   must be undefined first to prevent any conflicts with previous renamings. */
#undef MPI_Sendrecv_replace
#define MPI_Sendrecv_replace PMPI_Sendrecv_replace 
#endif

#else

#ifdef F77_NAME_UPPER
#define mpi_sendrecv_replace_ MPI_SENDRECV_REPLACE
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_sendrecv_replace_ mpi_sendrecv_replace__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_sendrecv_replace_ mpi_sendrecv_replace
/* Else leave name alone */
#endif


#endif /* MPICH_MPI_FROM_PMPI */

/* Prototypes for the Fortran interfaces */
#include "fproto.h"
FORT_DLL_SPEC void FORT_CALL mpi_sendrecv_replace_ ( void*v1, MPI_Fint *v2, MPI_Fint *v3, MPI_Fint *v4, MPI_Fint *v5, MPI_Fint *v6, MPI_Fint *v7, MPI_Fint *v8, MPI_Fint *v9, MPI_Fint *ierr ){

#ifndef HAVE_MPI_F_INIT_WORKS_WITH_C
    if (MPIR_F_NeedInit){ mpirinitf_(); MPIR_F_NeedInit = 0; }
#endif

    if (v9 == MPI_F_STATUS_IGNORE) { v9 = (MPI_Fint*)MPI_STATUS_IGNORE; }
    if (v1 == MPIR_F_MPI_BOTTOM) v1 = MPI_BOTTOM;
    *ierr = MPI_Sendrecv_replace( v1, (int)*v2, (MPI_Datatype)(*v3), (int)*v4, (int)*v5, (int)*v6, (int)*v7, (MPI_Comm)(*v8), (MPI_Status *)v9 );
}
