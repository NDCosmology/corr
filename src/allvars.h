/************************************************
Title:   allvars.h
Purpose: Contains global variable and structure defs
Notes:
************************************************/
#ifndef ALLVARS_H
   #define ALLVARS_H

   extern char spec_file[256];  // Holds spectrum file base name
   extern int nfiles;           // Number of total specta files
   extern int nfilesUsed;       // # of random files to use out of the total sample
   extern float BoxSize;        // Size in comoving GUL of the sim box
   extern float redshift;       // Redshift of the sim
   extern float avg_flux;       // The average flux across all LOS
   extern float delta_v;        // The size of the velocity bins in km/s
   extern int tot_npixels;      // Holds the total number of pixels read from all LOS
   extern int nbins;            // Number of velocity bins
   extern int npixels;          // Number of pixels within current LOS
   extern float *vels;          // Array for holding velocities from spec file
   extern float *fluxes;        // Array for holding fluxes from spec file
   extern float *corr;          // Array for holding the actual correlation function
   extern float OMEGA_M0;       // Present value of the matter density parameter
   extern float OMEGA_K0;       // Present value of the curvature density parameter
   extern float OMEGA_R0;       // Present value of the radiation density parameter
   extern float OMEGA_DE0;      // Present value of the dark energy density parameter
   extern float LITTLE_H;       // H = 100hkm/s/Mpc 
   extern float GUL_IN_CM;      // Gadget Unit of Length in cm/h

   #ifdef DARKPARAM
      extern float DE_W0;       // w_0 param from Linder02 de param
      extern float DE_WA;       // w_a param from Linder02 de param
   #endif

   typedef struct BINS
   {
      int count;
      float flux_product;
   } BINS;

   extern BINS *vel_bins;       // Holds info about total counts and correlation func numerator
                                // for each bin
#endif
