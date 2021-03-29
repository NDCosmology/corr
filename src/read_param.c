/************************************************
Title:   read_param
Purpose: Contains functions for reading the parameter
         file
Notes:   * This is taken from bexspec's read_param
         * Need spec_file_base, nfiles, L_co(kpc) z
************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "allvars.h"
#include "proto.h"



/***********************
       read_param
***********************/
void read_param(char *paramfile)
{
   // This function reads in the parameter file

   FILE *fd;
   char buffer[256];
   char buffer2[256];
   char *error;
   int  elements;
   void checkforerror(char *error, int elements, char *buf);

   // Open file for reading
   if(!(fd = fopen(paramfile, "r")))
   {
      printf("Error, could not open parameter file for reading!\n");
      exit(EXIT_FAILURE);
   }

   // Spec file basename
   error = fgets(buffer,sizeof(buffer),fd);
   elements = sscanf(buffer,"SpecBase%s",spec_file);
   checkforerror(error,elements,&buffer[0]);
   
   // Omega_m0
   error = fgets(buffer,sizeof(buffer),fd);
   elements = sscanf(buffer,"OmegaM%s",buffer2);  
   checkforerror(error,elements,&buffer[0]);   
   OMEGA_M0 = atof(buffer2);

   // Omega_Lambda0
   error = fgets(buffer,sizeof(buffer),fd);  
   elements = sscanf(buffer,"OmegaLambda%s",buffer2);  
   checkforerror(error,elements,&buffer[0]);   
   OMEGA_DE0 = atof(buffer2);

   // Omega_R0
   error = fgets(buffer,sizeof(buffer),fd);  
   elements = sscanf(buffer,"OmegaR%s",buffer2);  
   checkforerror(error,elements,&buffer[0]);   
   OMEGA_R0 = atof(buffer2);

   // Omega_K0
   error = fgets(buffer,sizeof(buffer),fd);  
   elements = sscanf(buffer,"OmegaK%s",buffer2);  
   checkforerror(error,elements,&buffer[0]);   
   OMEGA_K0 = atof(buffer2);

   // Get the Hubble constant in units of 100 km/s/Mpc
   error = fgets(buffer,sizeof(buffer),fd);
   elements = sscanf(buffer,"Hubble_h%s",buffer2); 
   checkforerror(error,elements,&buffer[0]);    
   LITTLE_H = atof(buffer2);

   // Get 1 GUL in cm/h
   error = fgets(buffer,sizeof(buffer),fd);
   elements = sscanf(buffer,"UnitLength_in_cm%s",buffer2);  
   checkforerror(error,elements,&buffer[0]);
   GUL_IN_CM = atof(buffer2);

   // Get nfiles
   error = fgets(buffer,sizeof(buffer),fd);
   elements = sscanf(buffer,"nfiles%s",buffer2);  
   checkforerror(error,elements,&buffer[0]);
   nfiles = atoi(buffer2);

   // Get nfiles
   error = fgets(buffer,sizeof(buffer),fd);
   elements = sscanf(buffer,"nFilesUse%s",buffer2);  
   checkforerror(error,elements,&buffer[0]);
   nfilesUsed = atoi(buffer2);

   // Get redshift
   error = fgets(buffer,sizeof(buffer),fd);
   elements = sscanf(buffer,"redshift%s",buffer2);  
   checkforerror(error,elements,&buffer[0]);
   redshift = atof(buffer2);

   // Get boxsize
   error = fgets(buffer,sizeof(buffer),fd);
   elements = sscanf(buffer,"BoxSize%s",buffer2);  
   checkforerror(error,elements,&buffer[0]);
   BoxSize = atof(buffer2);

   #ifdef DARKPARAM
      // Get w0
      error = fgets(buffer, sizeof(buffer), fd);
      elements = sscanf(buffer, "w0%s", buffer2);
      checkforerror(error, elements, &buffer[0]);
      DE_W0 = atof(buffer2);

      // Get wa
      error = fgets(buffer, sizeof(buffer), fd);
      elements = sscanf(buffer, "wa%s", buffer2);
      checkforerror(error, elements, &buffer[0]);
      DE_WA = atof(buffer2);
   #endif

   // Close file
   fclose(fd);
}



/***********************
     checkforerror
***********************/
void checkforerror(char *error, int elements, char *buf)
{
   char	buffer2[256]; 

   if (error==NULL) 
   {
      fprintf(stderr,"Couldn't read from parameter file. Stop.\n");
      exit(1);
   }
 
   if (elements==0) 
   {
      strncpy(buffer2,buf,strlen(buf));
      // strncpy does not add a final \0 terminator. It has to be added by hand
      buffer2[strlen(buf)-1]='\0';
      fprintf(stderr,"Couldn't convert '%s'. Stop.\n",buffer2);
      exit(1);
   }
}
