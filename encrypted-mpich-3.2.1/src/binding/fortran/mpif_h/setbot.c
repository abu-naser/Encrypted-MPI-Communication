/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*  
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 *
 */
#include "mpi_fortimpl.h"


#ifdef F77_NAME_UPPER
#define mpirinitc_ MPIRINITC
#define mpirinitc2_ MPIRINITC2
#elif defined(F77_NAME_LOWER_2USCORE) || defined(F77_NAME_LOWER_USCORE)
/* leave name alone */
#else
#define mpirinitc_ mpirinitc
#define mpirinitc2_ mpirinitc2
#endif
/* These functions are called from Fortran so only need prototypes in 
   this file.  Note that the second-to-last argument is a character array, so
   we need to include the elements of the Fortran character "dope vector".
*/
FORT_DLL_SPEC void FORT_CALL mpirinitc_( void *si, void *ssi,
                                         void *bt, void *ip,
                                         void *uw, void *ecsi,
                                         void *asn FORT_MIXED_LEN(d1),
                                         void *we
                                         FORT_END_LEN(d1));
FORT_DLL_SPEC void FORT_CALL mpirinitc2_( char * FORT_MIXED_LEN_DECL 
                                          FORT_END_LEN_DECL );

/*
    # These are here rather than in initf.c to solve some link order 
    # problems for Windows when separate libraries are used for the C and
    # Fortran routines.
    # Note that the global variables have values.  This is to work around
    # a bug in some C environments (e.g., Mac OS/X) that don't load
    # external symbols that don't have a value assigned at compile time 
    # (so called common symbols)
*/
#ifndef F77_USE_BOOLEAN_LITERALS
#if defined(F77_RUNTIME_VALUES) || !defined(F77_TRUE_VALUE_SET)
MPI_Fint MPIR_F_TRUE = 1, MPIR_F_FALSE = 0;
#else
const MPI_Fint MPIR_F_TRUE=F77_TRUE_VALUE;
const MPI_Fint MPIR_F_FALSE=F77_FALSE_VALUE;
#endif
#endif

/*
    # MPI-2, section 4.12.5, on the declaration of MPI_F_STATUS_IGNORE
    # MPI_F_STATUSES_IGNORE as global variables in mpi.h (!)
*/
int  MPIR_F_NeedInit        = 1;
void *MPIR_F_MPI_BOTTOM     = 0;
void *MPIR_F_MPI_IN_PLACE   = 0;
void *MPIR_F_MPI_UNWEIGHTED = 0;
/* MPI_F_STATUS_IGNORE etc must be declared within mpi.h (MPI-2 standard 
   requires this) */
/* 
void *MPI_F_STATUS_IGNORE   = 0;
void *MPI_F_STATUSES_IGNORE = 0;
*/
MPI_Fint  *MPI_F_ERRCODES_IGNORE = 0;
void *MPI_F_ARGVS_NULL      = 0;
void *MPIR_F_MPI_WEIGHTS_EMPTY = 0;

FORT_DLL_SPEC void FORT_CALL mpirinitc_( void *si, void *ssi,
                                         void *bt, void *ip, 
                                         void *uw, void *ecsi, 
                                         void *asn FORT_MIXED_LEN(d1),
                                         void *we
                                         FORT_END_LEN(d1))
{
    MPI_F_STATUS_IGNORE   = (MPI_Fint *) si;
    MPI_F_STATUSES_IGNORE = (MPI_Fint *) ssi;
    MPIR_F_MPI_BOTTOM     = bt;
    MPIR_F_MPI_IN_PLACE   = ip;
    MPIR_F_MPI_UNWEIGHTED = uw;
    MPI_F_ERRCODES_IGNORE = (MPI_Fint *)ecsi;
    MPI_F_ARGVS_NULL      = asn;
    MPIR_F_MPI_WEIGHTS_EMPTY = we;
}
/* Initialize the Fortran ARGV_NULL to a blank.  Using this routine
   avoids potential problems with string manipulation routines that
   exist in the Fortran runtime but not in the C runtime libraries */
FORT_DLL_SPEC void FORT_CALL mpirinitc2_( char *an FORT_MIXED_LEN(d1) 
                                          FORT_END_LEN(d1) )
{
    *an = ' ';
}



/*
   Enable all known common block symbols mangling to be alias to each other,
   i.e. [_C]mpifcmb*[_]to one symbol, mpifcmb*r.
   Each common block is defined for one MPI Fortran special constant.
   This is done to avoid alignment problem.
*/

#if defined(HAVE_C_MULTI_ATTR_ALIAS)
#define MPIF_STATUS_SIZE 5

struct mpif_cmblk1_t_ {
    MPI_Fint MPIF_STATUS_IGNORE[MPIF_STATUS_SIZE];
};
typedef struct mpif_cmblk1_t_ mpif_cmblk1_t;
mpif_cmblk1_t mpifcmb1r __attribute__((aligned(32))) = {{0}};
extern mpif_cmblk1_t _CMPIFCMB1  __attribute__ ((alias("mpifcmb1r")));
extern mpif_cmblk1_t   MPIFCMB1  __attribute__ ((alias("mpifcmb1r")));
extern mpif_cmblk1_t   MPIFCMB1_ __attribute__ ((alias("mpifcmb1r")));
extern mpif_cmblk1_t _Cmpifcmb1  __attribute__ ((alias("mpifcmb1r")));
extern mpif_cmblk1_t   mpifcmb1  __attribute__ ((alias("mpifcmb1r")));
extern mpif_cmblk1_t   mpifcmb1_ __attribute__ ((alias("mpifcmb1r")));

struct mpif_cmblk2_t_ {
    MPI_Fint MPIF_STATUSES_IGNORE[1][MPIF_STATUS_SIZE];
};
typedef struct mpif_cmblk2_t_ mpif_cmblk2_t;
mpif_cmblk2_t mpifcmb2r __attribute__((aligned(32))) = {{{0}}};
extern mpif_cmblk2_t _CMPIFCMB2  __attribute__ ((alias("mpifcmb2r")));
extern mpif_cmblk2_t   MPIFCMB2  __attribute__ ((alias("mpifcmb2r")));
extern mpif_cmblk2_t   MPIFCMB2_ __attribute__ ((alias("mpifcmb2r")));
extern mpif_cmblk2_t _Cmpifcmb2  __attribute__ ((alias("mpifcmb2r")));
extern mpif_cmblk2_t   mpifcmb2  __attribute__ ((alias("mpifcmb2r")));
extern mpif_cmblk2_t   mpifcmb2_ __attribute__ ((alias("mpifcmb2r")));

struct mpif_cmblk3_t_ {
    MPI_Fint MPIF_BOTTOM;
};
typedef struct mpif_cmblk3_t_ mpif_cmblk3_t;
mpif_cmblk3_t mpifcmb3r __attribute__((aligned(16))) = {0};
extern mpif_cmblk3_t _CMPIFCMB3  __attribute__ ((alias("mpifcmb3r")));
extern mpif_cmblk3_t   MPIFCMB3  __attribute__ ((alias("mpifcmb3r")));
extern mpif_cmblk3_t   MPIFCMB3_ __attribute__ ((alias("mpifcmb3r")));
extern mpif_cmblk3_t _Cmpifcmb3  __attribute__ ((alias("mpifcmb3r")));
extern mpif_cmblk3_t   mpifcmb3  __attribute__ ((alias("mpifcmb3r")));
extern mpif_cmblk3_t   mpifcmb3_ __attribute__ ((alias("mpifcmb3r")));

struct mpif_cmblk4_t_ {
    MPI_Fint MPIF_IN_PLACE;
};
typedef struct mpif_cmblk4_t_ mpif_cmblk4_t;
mpif_cmblk4_t mpifcmb4r __attribute__((aligned(16))) = {0};
extern mpif_cmblk4_t _CMPIFCMB4  __attribute__ ((alias("mpifcmb4r")));
extern mpif_cmblk4_t   MPIFCMB4  __attribute__ ((alias("mpifcmb4r")));
extern mpif_cmblk4_t   MPIFCMB4_ __attribute__ ((alias("mpifcmb4r")));
extern mpif_cmblk4_t _Cmpifcmb4  __attribute__ ((alias("mpifcmb4r")));
extern mpif_cmblk4_t   mpifcmb4  __attribute__ ((alias("mpifcmb4r")));
extern mpif_cmblk4_t   mpifcmb4_ __attribute__ ((alias("mpifcmb4r")));

struct mpif_cmblk5_t_ {
    MPI_Fint MPIF_UNWEIGHTED;
};
typedef struct mpif_cmblk5_t_ mpif_cmblk5_t;
mpif_cmblk5_t mpifcmb5r __attribute__((aligned(16))) = {0};
extern mpif_cmblk5_t _CMPIFCMB5  __attribute__ ((alias("mpifcmb5r")));
extern mpif_cmblk5_t   MPIFCMB5  __attribute__ ((alias("mpifcmb5r")));
extern mpif_cmblk5_t   MPIFCMB5_ __attribute__ ((alias("mpifcmb5r")));
extern mpif_cmblk5_t _Cmpifcmb5  __attribute__ ((alias("mpifcmb5r")));
extern mpif_cmblk5_t   mpifcmb5  __attribute__ ((alias("mpifcmb5r")));
extern mpif_cmblk5_t   mpifcmb5_ __attribute__ ((alias("mpifcmb5r")));

struct mpif_cmblk6_t_ {
    MPI_Fint MPIF_ERRCODES_IGNORE[1];
};
typedef struct mpif_cmblk6_t_ mpif_cmblk6_t;
mpif_cmblk6_t mpifcmb6r __attribute__((aligned(16))) = {{0}};
extern mpif_cmblk6_t _CMPIFCMB6  __attribute__ ((alias("mpifcmb6r")));
extern mpif_cmblk6_t   MPIFCMB6  __attribute__ ((alias("mpifcmb6r")));
extern mpif_cmblk6_t   MPIFCMB6_ __attribute__ ((alias("mpifcmb6r")));
extern mpif_cmblk6_t _Cmpifcmb6  __attribute__ ((alias("mpifcmb6r")));
extern mpif_cmblk6_t   mpifcmb6  __attribute__ ((alias("mpifcmb6r")));
extern mpif_cmblk6_t   mpifcmb6_ __attribute__ ((alias("mpifcmb6r")));

struct mpif_cmblk7_t_ {
    char MPIF_ARGVS_NULL[1][1];
    char pads[3];
};
typedef struct mpif_cmblk7_t_ mpif_cmblk7_t;
mpif_cmblk7_t mpifcmb7r __attribute__((aligned(16))) = {{{0}}};
extern mpif_cmblk7_t _CMPIFCMB7  __attribute__ ((alias("mpifcmb7r")));
extern mpif_cmblk7_t   MPIFCMB7  __attribute__ ((alias("mpifcmb7r")));
extern mpif_cmblk7_t   MPIFCMB7_ __attribute__ ((alias("mpifcmb7r")));
extern mpif_cmblk7_t _Cmpifcmb7  __attribute__ ((alias("mpifcmb7r")));
extern mpif_cmblk7_t   mpifcmb7  __attribute__ ((alias("mpifcmb7r")));
extern mpif_cmblk7_t   mpifcmb7_ __attribute__ ((alias("mpifcmb7r")));

struct mpif_cmblk8_t_ {
    char MPIF_ARGV_NULL[1];
    char pads[3];
};
typedef struct mpif_cmblk8_t_ mpif_cmblk8_t;
mpif_cmblk8_t mpifcmb8r __attribute__((aligned(16))) = {{0}};
extern mpif_cmblk8_t _CMPIFCMB8  __attribute__ ((alias("mpifcmb8r")));
extern mpif_cmblk8_t   MPIFCMB8  __attribute__ ((alias("mpifcmb8r")));
extern mpif_cmblk8_t   MPIFCMB8_ __attribute__ ((alias("mpifcmb8r")));
extern mpif_cmblk8_t _Cmpifcmb8  __attribute__ ((alias("mpifcmb8r")));
extern mpif_cmblk8_t   mpifcmb8  __attribute__ ((alias("mpifcmb8r")));
extern mpif_cmblk8_t   mpifcmb8_ __attribute__ ((alias("mpifcmb8r")));

struct mpif_cmblk9_t_ {
    MPI_Fint MPIF_WEIGHTS_EMPTY;
};
typedef struct mpif_cmblk9_t_ mpif_cmblk9_t;
mpif_cmblk9_t mpifcmb9r __attribute__((aligned(16))) = {0};
extern mpif_cmblk9_t _CMPIFCMB9  __attribute__ ((alias("mpifcmb9r")));
extern mpif_cmblk9_t   MPIFCMB9  __attribute__ ((alias("mpifcmb9r")));
extern mpif_cmblk9_t   MPIFCMB9_ __attribute__ ((alias("mpifcmb9r")));
extern mpif_cmblk9_t _Cmpifcmb9  __attribute__ ((alias("mpifcmb9r")));
extern mpif_cmblk9_t   mpifcmb9  __attribute__ ((alias("mpifcmb9r")));
extern mpif_cmblk9_t   mpifcmb9_ __attribute__ ((alias("mpifcmb9r")));

#endif

