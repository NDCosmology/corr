/************************************************
Title:   init.c
Purpose: Sets up the run
Notes:
************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "allvars.h"
#include "proto.h"



/***********************
         init
***********************/
void init(int nargs, char **args)
{
   // This function error checks and assigns args
   // and sets up the velocity bins

   float Hubble;
   float vel_extent;
   int i;

   // Check number of args
   if(nargs != 2)
   {
      printf("Usage: ./corr param_file.param\n");
      exit(EXIT_FAILURE);
   }

   // Do a DE check
   de_error_check();

   // Read parameter file
   read_param(args[1]);

   // Initialize total flux sum and pixel counts
   avg_flux = 0.0;
   tot_npixels = 0;

   // Calculate the Hubble parameter for given redshift and DE model
   // (used in getting velocity extent of box) 
   // NOTE: Hubble returned in s^-1!!!!!!!
   Hubble = get_hubble();

   // Get velocity extent of box
   // (used in getting number of velocity bins)
   vel_extent = BoxSize * Hubble / (1.0 + redshift);

   // Convert to km/s
   vel_extent = vel_extent * GUL_IN_CM / (LITTLE_H * 10000.0);

   // Get the number of velocity bins (I AM NOT SURE ABOUT THIS!!!!)
   printf("Check the nbins calc! I'm not sure about it!\n");
   nbins = ceil(vel_extent / delta_v);

   // Allocate memory for velocity bins
   if(!(vel_bins = calloc(nbins, sizeof(BINS))))
   {
      printf("Error, could not allocate memory for velocity bins!\n");
      exit(EXIT_FAILURE);
   }

   // Allocate memory for correlation function
   if(!(corr = calloc(nbins, sizeof(float))))
   {
      printf("Error, could not allocate memory for correlation function!\n");
      exit(EXIT_FAILURE);
   }

   // Initialize the bins struct
   for(i = 0; i < nbins; i++)
   {
      vel_bins[i].count = 0;
      vel_bins[i].flux_product = 0.0;
   }
}
