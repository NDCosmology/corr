/************************************************
Title:   corr.c
Purpose: Contains functions related to calculating
         the flux correlation function
Notes:   Using the flux correlation function as defined in
         Cen98 equation 2
************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "allvars.h"
#include "proto.h"



/***********************
       prep_corr
***********************/
void prep_corr(void)
{
   // This function loops over all pairs of pixels
   // (not double counting) in the current LOS. For
   // these pairs, it calcs F(v + v')F(v') and gets the
   // current LOS's contribution to the average F 
   // (the denominator)

   int i;
   int j;
   int bin_ind;
   float vel_sep;

   // Update the total number of pixels across all LOS
   // for use in getting <F>
   tot_npixels += npixels;

   // Loop over all pairs of pixels
   for(i = 0; i < npixels; i++)
   {
      for(j = i; j < npixels; j++)
      {
         // Get contributions to average flux across all LOS
         // (only do this once!)
         if(i == 0)
         {
            avg_flux += fluxes[j];
         }

         // Now we have to get F(v')F(v+v'), but we need to know which
         // bin this total should go towards (so we get vel sep first)
         vel_sep = vels[j] - vels[i];

         // Get the bin index that this pair belongs in
         bin_ind = floor(vel_sep / delta_v);

         // Do an error check on the bounds of bin_ind
         if((bin_ind < 0) || (bin_ind > nbins))
         {
            printf("Error, bin_ind is outside allowed bounds!\n");
            exit(EXIT_FAILURE);
         }

         // Update the corresponding bin
         vel_bins[bin_ind].count++;
         vel_bins[bin_ind].flux_product += fluxes[i] * fluxes[j];
      }
   }
}



/***********************
       calc_corr
***********************/
void calc_corr(void)
{
   // This function finishes calculating the flux correlation function
   // by evaluating the averages for <F> and in the numerator

   int i;

   // Finish calculating <F> by dividing total by total number of pixels
   avg_flux = avg_flux / (float)tot_npixels;

   // Loop over the number of bins
   for(i = 0; i < nbins; i++)
   {
      // Finalize average in numerator
      corr[i] = vel_bins[i].flux_product / (float)vel_bins[i].count;

      // Divide by <F>^2
      corr[i] = corr[i] / (avg_flux * avg_flux);

      // Subtract 1
      corr[i] = corr[i] - 1.0;
   }

   // Free vel_bins
   free(vel_bins);
}
