/************************************************
Title:   read.c
Purpose: Contains functions used for reading in the
         spec files
Notes:
************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "allvars.h"
#include "proto.h"



/***********************
    read_spec_file
***********************/
int read_spec_file(int file_num)
{
   // Driver function for reading in spectrum file

   FILE *fd;
   FILE *fe;
   char buf[256];
   float dummy;
   int i;
   int file_exists;
   long int file_pos;

   // Set up file
   if(file_num <= 999)
   {
      sprintf(buf, "%s-%03d.txt", spec_file, file_num);
   }

   else if((file_num > 999) && (file_num <= 9999)) 
   {
      sprintf(buf, "%s-%04d.txt", spec_file, file_num);
   }

   else if(file_num > 9999)
   {
      sprintf(buf, "%s-%05d.txt", spec_file, file_num);
   }

   // Open file
   if(!(fd = fopen(buf, "r")))
   {
      if(!(fe = fopen("skipped_los.txt", "a")))
      {
         printf("Error, could not open file for logging skipped LOS!\n");
         exit(EXIT_FAILURE);
      }

      fprintf(fe, "%d\n", file_num);
      fclose(fe);

      return file_exists = 0;
   }

   // Get number of lines in the file (npixels)
   while((i = getc(fd)) != ':')
   {
      continue;
   }

   fscanf(fd, " %d\n", &npixels);

   // Skip the headings line
   while((i = getc(fd)) != '\n')
   {
      continue;
   }

   // If this is a spectra file made with PARALLEL_LOS on in bexspec,
   // then there is a second heading line that gives the position of the
   // first pixel. Need to check for that and skip it if it's there. 
   // Save current position in file
   file_pos = ftell(fd);

   // Check for '#' character
   if((i = getc(fd)) == '#')
   {
      // We're here if the additional header line is present, so we skip it
      while((i = getc(fd)) != '\n')
      {
         continue;
      }
   }

   else
   {
      // We're here if the additional header line is absent, so we go back
      // to end of previous line and then read data
      fseek(fd, file_pos, SEEK_SET);
   }

   // Allocate memory for vel and flux array
   if(!(vels = calloc(npixels, sizeof(float))))
   {
      printf("Error, could not allocate memory for velocity array on file %d\n", file_num);
      exit(EXIT_FAILURE);
   }

   if(!(fluxes = calloc(npixels, sizeof(float))))
   {
      printf("Error, could not allocate memory for flux array on file %d\n", file_num);
      exit(EXIT_FAILURE);
   }

   // Read the data. Column 1 is vel, column 8 is flux
   for(i = 0; i < npixels; i++)
   {
      fscanf(fd, "%f %f %f %f %f %f %f %f\n", &vels[i], &dummy, &dummy, 
            &dummy, &dummy, &dummy, &dummy, &fluxes[i]);
   }

   // Close the file
   fclose(fd);

   return file_exists = 1;
}
