CC          = gcc
AR          = ar
LIBNAME     = /home/naser/encrypted-mpi-communication/encrypted-mpich-3.2.1/lib/libmpi.a
RANLIB      = ranlib
srcdir      = /home/naser/encrypted-mpi-communication/encrypted-mpich-3.2.1/src/mpi/romio/mpi2-other/array
CC_SHL      = 
SHLIBNAME   = /home/naser/encrypted-mpi-communication/encrypted-mpich-3.2.1/lib/libmpi

INCLUDE_DIR = -I. -I../../include -I${srcdir}/../../mpi-io -I${srcdir}/../../adio/include -I../../adio/include
CFLAGS      =   -I/home/naser/encrypted-mpi-communication/encrypted-mpich-3.2.1/src/mpl/include -I/home/naser/encrypted-mpi-communication/encrypted-mpich-3.2.1/src/mpl/include -I/home/naser/encrypted-mpi-communication/encrypted-mpich-3.2.1/src/openpa/src -I/home/naser/encrypted-mpi-communication/encrypted-mpich-3.2.1/src/openpa/src -D_REENTRANT -I/home/naser/encrypted-mpi-communication/encrypted-mpich-3.2.1/src/mpi/romio/include    -O2  -DFORTRANUNDERSCORE -DHAVE_ROMIOCONF_H $(MPIOPROFILE) $(INCLUDE_DIR)

top_builddir  = /home/naser/encrypted-mpi-communication/encrypted-mpich-3.2.1
LIBTOOL       = $(SHELL) $(top_builddir)/libtool
C_COMPILE_SHL = $(CC_SHL)

VPATH=.:${srcdir}

MPIO_OBJECTS = subarray.o darray.o

MPIO_TMP_POBJECTS = subarray.p darray.p

MPIO_REAL_POBJECTS = _subarray.o _darray.o

all: $(LIBNAME)
	@if [ "none" != "none" ] ; then \
	    $(MAKE) $(SHLIBNAME).la ;\
	fi

.SUFFIXES: $(SUFFIXES) .p .sp .lo

.c.o:
	$(CC) $(CFLAGS) -c $<
.c.lo:
	$(C_COMPILE_SHL) $(CFLAGS) -c $< -o _s$*.o
	@mv -f _s$*.o $*.lo

.c.p:
	@cp $(srcdir)/$*.c _$*.c
	$(CC) $(CFLAGS) -c _$*.c
	@rm -f _$*.c

.c.sp:
	$(C_COMPILE_SHL) $(CFLAGS) -c $< -o _$*.lo

profile: $(MPIO_REAL_POBJECTS)
	$(AR) $(LIBNAME) $(MPIO_REAL_POBJECTS)
	$(RANLIB) $(LIBNAME) 
	@if [ "none" != "none" ] ; then \
	    $(MAKE) P$(SHLIBNAME).la ;\
	fi
	@rm -f _*.o

$(LIBNAME): $(MPIO_OBJECTS)
	$(AR) $(LIBNAME) $(MPIO_OBJECTS)
	$(RANLIB) $(LIBNAME) 

MPIO_LOOBJECTS = $(MPIO_OBJECTS:.o=.lo)
$(SHLIBNAME).la: $(MPIO_LOOBJECTS) 
	$(AR) $(SHLIBNAME).la $(MPIO_LOOBJECTS)

# --------------------------------------------------------------------------
# We use P$(SHLBNAME) simply to distinguish the regular lib build from the
# profiling library build
MPIO_LOPOBJECTS = $(MPIO_REAL_POBJECTS:.o=.lo)
MPIO_TMP_LOPOBJECTS = ${MPIO_TMP_POBJECTS:.p=.sp}
P$(SHLIBNAME).la: $(MPIO_TMP_LOPOBJECTS)
	$(AR) $(SHLIBNAME).la $(MPIO_LOPOBJECTS)
# --------------------------------------------------------------------------

clean:
	@rm -f *.o *.lo *.gcno *.gcda *.bb *.bbg
	@rm -f ${srcdir}/*.gcno ${srcdir}/*.gcda 
	@rm -f ${srcdir}/*.bb ${srcdir}/*.bbg

# Rules for the profiling objects
_subarray.o: subarray.c
	$(CC) $(CFLAGS) -c $(srcdir)/subarray.c -o _subarray.o
_darray.o: darray.c
	$(CC) $(CFLAGS) -c $(srcdir)/darray.c -o _darray.o

