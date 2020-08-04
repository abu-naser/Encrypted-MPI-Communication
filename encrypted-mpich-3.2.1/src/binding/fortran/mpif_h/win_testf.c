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
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak MPI_WIN_TEST = PMPI_WIN_TEST
#pragma weak mpi_win_test__ = PMPI_WIN_TEST
#pragma weak mpi_win_test_ = PMPI_WIN_TEST
#pragma weak mpi_win_test = PMPI_WIN_TEST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_WIN_TEST = pmpi_win_test__
#pragma weak mpi_win_test__ = pmpi_win_test__
#pragma weak mpi_win_test_ = pmpi_win_test__
#pragma weak mpi_win_test = pmpi_win_test__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_WIN_TEST = pmpi_win_test_
#pragma weak mpi_win_test__ = pmpi_win_test_
#pragma weak mpi_win_test_ = pmpi_win_test_
#pragma weak mpi_win_test = pmpi_win_test_
#else
#pragma weak MPI_WIN_TEST = pmpi_win_test
#pragma weak mpi_win_test__ = pmpi_win_test
#pragma weak mpi_win_test_ = pmpi_win_test
#pragma weak mpi_win_test = pmpi_win_test
#endif



#elif defined(HAVE_PRAGMA_WEAK)

#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak MPI_WIN_TEST = PMPI_WIN_TEST
#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_win_test__ = pmpi_win_test__
#elif !defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_win_test = pmpi_win_test
#else
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#pragma weak mpi_win_test_ = pmpi_win_test_
#endif

#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#if defined(F77_NAME_UPPER)
#pragma _HP_SECONDARY_DEF PMPI_WIN_TEST  MPI_WIN_TEST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _HP_SECONDARY_DEF pmpi_win_test__  mpi_win_test__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _HP_SECONDARY_DEF pmpi_win_test  mpi_win_test
#else
#pragma _HP_SECONDARY_DEF pmpi_win_test_  mpi_win_test_
#endif

#elif defined(HAVE_PRAGMA_CRI_DUP)
#if defined(F77_NAME_UPPER)
#pragma _CRI duplicate MPI_WIN_TEST as PMPI_WIN_TEST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma _CRI duplicate mpi_win_test__ as pmpi_win_test__
#elif !defined(F77_NAME_LOWER_USCORE)
#pragma _CRI duplicate mpi_win_test as pmpi_win_test
#else
#pragma _CRI duplicate mpi_win_test_ as pmpi_win_test_
#endif

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_TEST")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_TEST")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_TEST")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_TEST")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test")));

#endif
#endif /* HAVE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */
/* End MPI profiling block */


/* These definitions are used only for generating the Fortran wrappers */
#if defined(USE_WEAK_SYMBOLS) && defined(USE_ONLY_MPI_NAMES)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#if defined(F77_NAME_UPPER)
#pragma weak mpi_win_test__ = MPI_WIN_TEST
#pragma weak mpi_win_test_ = MPI_WIN_TEST
#pragma weak mpi_win_test = MPI_WIN_TEST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak MPI_WIN_TEST = mpi_win_test__
#pragma weak mpi_win_test_ = mpi_win_test__
#pragma weak mpi_win_test = mpi_win_test__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak MPI_WIN_TEST = mpi_win_test_
#pragma weak mpi_win_test__ = mpi_win_test_
#pragma weak mpi_win_test = mpi_win_test_
#else
#pragma weak MPI_WIN_TEST = mpi_win_test
#pragma weak mpi_win_test__ = mpi_win_test
#pragma weak mpi_win_test_ = mpi_win_test
#endif
#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_WIN_TEST")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_WIN_TEST")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("MPI_WIN_TEST")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_test__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_test__")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_test__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_test_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_test_")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * );
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_test_")));

#else
extern FORT_DLL_SPEC void FORT_CALL MPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_test")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_test")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("mpi_win_test")));
extern FORT_DLL_SPEC void FORT_CALL mpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#endif
#endif

#endif

/* Map the name to the correct form */
#ifndef MPICH_MPI_FROM_PMPI
#if defined(USE_WEAK_SYMBOLS)
#if defined(HAVE_MULTIPLE_PRAGMA_WEAK)
/* Define the weak versions of the PMPI routine*/
#ifndef F77_NAME_UPPER
extern FORT_DLL_SPEC void FORT_CALL PMPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_2USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER_USCORE
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * );
#endif
#ifndef F77_NAME_LOWER
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * );

#endif

#if defined(F77_NAME_UPPER)
#pragma weak pmpi_win_test__ = PMPI_WIN_TEST
#pragma weak pmpi_win_test_ = PMPI_WIN_TEST
#pragma weak pmpi_win_test = PMPI_WIN_TEST
#elif defined(F77_NAME_LOWER_2USCORE)
#pragma weak PMPI_WIN_TEST = pmpi_win_test__
#pragma weak pmpi_win_test_ = pmpi_win_test__
#pragma weak pmpi_win_test = pmpi_win_test__
#elif defined(F77_NAME_LOWER_USCORE)
#pragma weak PMPI_WIN_TEST = pmpi_win_test_
#pragma weak pmpi_win_test__ = pmpi_win_test_
#pragma weak pmpi_win_test = pmpi_win_test_
#else
#pragma weak PMPI_WIN_TEST = pmpi_win_test
#pragma weak pmpi_win_test__ = pmpi_win_test
#pragma weak pmpi_win_test_ = pmpi_win_test
#endif /* Test on name mapping */

#elif defined(HAVE_WEAK_ATTRIBUTE)
#if defined(F77_NAME_UPPER)
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_TEST")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_TEST")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("PMPI_WIN_TEST")));

#elif defined(F77_NAME_LOWER_2USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test__")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test__")));

#elif defined(F77_NAME_LOWER_USCORE)
extern FORT_DLL_SPEC void FORT_CALL PMPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test_")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_test( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test_")));

#else
extern FORT_DLL_SPEC void FORT_CALL PMPI_WIN_TEST( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_test__( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test")));
extern FORT_DLL_SPEC void FORT_CALL pmpi_win_test_( MPI_Fint *, MPI_Fint *, MPI_Fint * ) __attribute__((weak,alias("pmpi_win_test")));

#endif /* Test on name mapping */
#endif /* HAVE_MULTIPLE_PRAGMA_WEAK */
#endif /* USE_WEAK_SYMBOLS */

#ifdef F77_NAME_UPPER
#define mpi_win_test_ PMPI_WIN_TEST
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_win_test_ pmpi_win_test__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_win_test_ pmpi_win_test
#else
#define mpi_win_test_ pmpi_win_test_
#endif /* Test on name mapping */

#ifdef F77_USE_PMPI
/* This defines the routine that we call, which must be the PMPI version
   since we're renaming the Fortran entry as the pmpi version.  The MPI name
   must be undefined first to prevent any conflicts with previous renamings. */
#undef MPI_Win_test
#define MPI_Win_test PMPI_Win_test 
#endif

#else

#ifdef F77_NAME_UPPER
#define mpi_win_test_ MPI_WIN_TEST
#elif defined(F77_NAME_LOWER_2USCORE)
#define mpi_win_test_ mpi_win_test__
#elif !defined(F77_NAME_LOWER_USCORE)
#define mpi_win_test_ mpi_win_test
/* Else leave name alone */
#endif


#endif /* MPICH_MPI_FROM_PMPI */

/* Prototypes for the Fortran interfaces */
#include "fproto.h"
FORT_DLL_SPEC void FORT_CALL mpi_win_test_ ( MPI_Fint *v1, MPI_Fint *v2, MPI_Fint *ierr ){
    int l2;
    *ierr = MPI_Win_test( (MPI_Win)*v1, &l2 );
    if (*ierr == MPI_SUCCESS) *v2 = MPIR_TO_FLOG(l2);
}
