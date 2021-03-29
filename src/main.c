/************************************************
Title:   correlation.c
Author:  Jared Coughlin
Date:    4/14/16
Purpose: Attempt to calculate the flux correlation
         function for simulated spectra
Notes:   Uses the correlation function defined in eq 2
         of Cen98
************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include "allvars.h"
#include "proto.h"



int main(int argc, char **argv)
{
   int i;
   int j;
   int file_exists;
   time_t seed;
   clock_t start;
   clock_t end;

   #ifndef RANDOM_SEED
      const gsl_rng_type *T;
   #endif
   gsl_rng *r;

   // Get start time
   start = clock();

   // Initialize
   init(argc, argv);

   // Set up the rng
   #ifndef RANDOM_SEED
      gsl_rng_env_setup();
      T = gsl_rng_default;
      r = gsl_rng_alloc(T);
   #else
      // Get current time to use as rng seed
      time(&seed);

      // Use same generator as gadget
      r = gsl_rng_alloc(gsl_rng_ranlxd1);
      gsl_rng_set(r, seed);
   #endif

   // Loop over every file
   for(i = 1; i <= nfilesUsed; i++)
   {
      // Select a random file
      j = gsl_rng_uniform_int(r, nfiles);

      // Read the file
      file_exists = read_spec_file(j);

      if(file_exists == 1)
      {
         // Begin to calculate the correlation function
         prep_corr();

         // Clean up resources
         free(vels);
         free(fluxes);
      }
   }

   // Finish calculating the correlation function
   if(tot_npixels > 0)
   {
      fflush(stdout);
      printf("Calculating correlation function...\n");
      calc_corr();

      // Write data to file compatible with gnuplot
      write();
   }

   else
   {
      printf("Error, no pixels were read!\n");
      exit(EXIT_FAILURE);
   }

   // Free rng
   gsl_rng_free(r);

   // Get end time
   end = clock();

   printf("Total run time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
   printf("Have a nice day!\n");

   return 0;
}
