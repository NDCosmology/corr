/************************************************
Title:   write.c
Purpose: Contains functions related to writing the
         data to files for plotting
Notes:
************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "allvars.h"
#include "proto.h"



/***********************
         write
***********************/
void write(void)
{
   // This function writes the data to a file for use with
   // gnuplot

   FILE *fd;
   int i;

   // Open file
   if(!(fd = fopen("flux_autocorrelation.txt", "w")))
   {
      printf("Error, could not open file for writing data!\n");
      exit(EXIT_FAILURE);
   }

   // Write heading
   fprintf(fd, "# Corr(delta_v) corr(delta_v)+1 delta_v\n");

   // Loop over the data
   for(i = 0; i < nbins; i++)
   {
      fprintf(fd, "%f \t %f \t %f\n", corr[i], corr[i] + 1.0, (float)i * delta_v); 
   }

   // Close the file
   fclose(fd);

   // Free corr
   free(corr);
}
