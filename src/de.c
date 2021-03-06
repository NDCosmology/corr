/************************************************
Title: de.c
Purpose: Gets a_dot based on the DE model chosen in
         the makefile.
Notes: For either quint or k-essence, it would make sense
       to simply read in the H vs. a file produced by qsolve
       since solving for H in those cases is kind of slow.
       
       I feel like I'm very much leaning towards model-independent
       tests and then maybe trying to make a model fit that data.
       There's just too many models and too large a parameter space
       to explore with gadget in a timely manner.
************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "allvars.h"
#include "proto.h"



/***********************
    de_error_check
***********************/
void de_error_check(void)
{
   // This function does much the same as dark_check in
   // DE_Gadget in that it makes sure that only one DE
   // model is chosen (and that a model is chosen) in the
   // makefile.

   int total = 0;

   #ifdef LAMBDA
      total++;
   #endif

   #ifdef DARKPARAM
      total++;
   #endif

   if((total == 0) || (total > 1))
   {
      printf("Error, either more than one DE model is chosen, or none is!\n");
      exit(EXIT_FAILURE);
   }
}



/***********************
       get_hubble
***********************/
float get_hubble(void)
{
   // Does as the name says. a_dot is required for calculating 
   // tau and is how DE enters into the forest, as different DE
   // models will have different a_dot values for a given a.

   float H0;
   float a_dot;
   float a = 1.0 / (1.0 + redshift);

   // Set H0 in s^-1. H0 := 100h km s^-1 Mpc^-1
   H0 = 3.2407e-18 * LITTLE_H;

   #ifdef LAMBDA
      // The cosmological constant case. This is pretty easy. It's just the 
      // standard Hubble function (Amendola eq. 5.1 w/ w_DE = -1) MAKE SURE H0
      // is in units of s^-1!!! otherwise a_dot will have the wrong units
      a_dot = a * H0 * sqrt((OMEGA_R0 * pow(a, -4.0)) + 
              (OMEGA_M0 * pow(a, -3.0)) + (OMEGA_K0 * pow(a, -2.0)) + OMEGA_DE0);

      // Check for nans and infinities
      if(isnan(a_dot) == 1)
      {
         printf("Error, a_dot is a nan!\n");
         exit(EXIT_FAILURE);
      }

      if(isfinite(a_dot) == 0)
      {
         printf("Error, a_dot is infinite!\n");
         exit(EXIT_FAILURE);
      }
   #endif

   #ifdef DARKPARAM
      // This is for use with the Linder02 parameterization of w.
      // It's the same Hubble eq as used for Lambda above, but the
      // OMEGA_DE term has to be multiplied by what I call the dark factor.
      // This is the exp(integral) term in Amendola eq. 2.84
      float dark_factor;

      // Calculate the dark factor. See notes from 2/26/15 for deriv
      dark_factor = pow(a, -3.0 * (1.0 + DE_W0 + DE_WA)) * 
                    exp(-3.0 * DE_WA * (1.0 - a));

      // Use the dark factor to get a_dot
      a_dot = a * H0 * sqrt((OMEGA_R0 * pow(a, -4.0)) +
              (OMEGA_M0 * pow(a, -3.0)) + (OMEGA_K0 * pow(a, -2.0)) +
              (OMEGA_DE0 * dark_factor));

      // Check for nans and infinities
      if(isnan(a_dot) == 1)
      {
         printf("Error, a_dot is a nan!\n");
         exit(EXIT_FAILURE);
      }

      if(isfinite(a_dot) == 0)
      {
         printf("Error, a_dot is infinite!\n");
         exit(EXIT_FAILURE);
      }
   #endif

   return (a_dot / a);
}
