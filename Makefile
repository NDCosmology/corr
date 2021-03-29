# Makefile for corr








#--------------------------------------- Compile Time Options
# DE model options
#OPT += -DLAMBDA
OPT += -DDARKPARAM

# Random or same seed per run
OPT += -DRANDOM_SEED

#--------------------------------------- Select Target Computer

#SYSTYPE="CRC-Opteron-long"
#SYSTYPE="phillips"
SYSTYPE="jared_home"

#--------------------------------------- System Specifics

ifeq ($(SYSTYPE),"jared_home")
#CC = mpicc
CC = gcc
#OPTIMIZE  = -O3 -Wall
OPTIMIZE = -Wall -g3
#OPTIMIZE = -Wall -fopenmp -g3
GSL_INCL = -I/usr/local/include/gsl
GSL_LIBS = -L/usr/local/lib
endif



ifeq ($(SYSTYPE),"phillips")
CC = gcc
OPTIMIZE = -Wall -g3
GSL_INCL = -I/opt/local/include
GSL_LIBS = -L/opt/local/lib -Wl
endif



ifeq ($(SYSTYPE),"CRC-Opteron-long")
CC       =  mpicc
OPTIMIZE =  -O3 -Wall
#OPTIMIZE = -g3 -Wall
GSL_INCL =  -I/opt/crc/scilib/gsl/1.16/intel-14.0/include
GSL_LIBS =  -L/opt/crc/scilib/gsl/1.16/intel-14.0/lib  -Wl,"-R /opt/crc/scilib/gsl/1.16/intel-14.0/lib"
FFTW_INCL=  -I/opt/crc/scilib/fftw/2.1.5_ompi/intel/1.6.5/include
FFTW_LIBS=  -L/opt/crc/scilib/fftw/2.1.5_ompi/intel/1.6.5/lib
#FFTW_INCL=  -I/opt/crc/scilib/fftw/2.1.5-intel/include
#FFTW_LIBS=  -L/opt/crc/scilib/fftw/2.1.5-intel/lib
MPICHLIB =	-L/opt/crc/o/openmpi/1.10.2/intel/15.0/lib
HDF5INCL =
HDF5LIB  =
endif



#-------------------------------------- Bookkeeping
PREFIX = ./src
OBJ_DIR = $(PREFIX)/obj

OPTIONS =  $(OPTIMIZE) $(OPT)

EXEC   = corr

OBJS   = $(OBJ_DIR)/main.o $(OBJ_DIR)/allvars.o \
         $(OBJ_DIR)/init.o $(OBJ_DIR)/read.o $(OBJ_DIR)/de.o \
         $(OBJ_DIR)/corr.o $(OBJ_DIR)/write.o $(OBJ_DIR)/read_param.o
   
INCL   = $(PREFIX)/allvars.h  $(PREFIX)/proto.h Makefile

INCLUDE =

CFLAGS = $(OPTIONS)

all: $(EXEC)  

#LIBS = -lm
LIBS = $(GSL_LIBS) -lgsl -lgslcblas -lm

#ALI Added 2/6/13  see http://www.apl.jhu.edu/Misc/Unix-info/make/make_10.html#SEC90
#                  for logic 
$(OBJ_DIR)/%.o : $(PREFIX)/%.c $(INCL)
	$(CC) $(OPTIONS) $(INCLUDE) -c $< -o $@

$(EXEC): $(OBJS) 
	$(CC) $(OBJS) $(LIBS) -o  $(EXEC)

clean:
	rm -f $(OBJS) *.gch 
