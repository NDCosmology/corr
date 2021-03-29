/************************************************
Title: allvars.h
Purpose: Contains declarations of globals
Notes:
************************************************/
#include "allvars.h"



char spec_file[256];
int nfiles;
int nfilesUsed;
float BoxSize;
float redshift;
float avg_flux;
float delta_v = 2.0;
int tot_npixels;
int nbins;
int npixels;
float *vels;
float *fluxes;
float *corr;
float OMEGA_M0;
float OMEGA_K0;
float OMEGA_R0;
float OMEGA_DE0;
float LITTLE_H;
float GUL_IN_CM;

#ifdef DARKPARAM
   float DE_W0;
   float DE_WA;
#endif

BINS *vel_bins;
