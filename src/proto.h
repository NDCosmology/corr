/************************************************
Title: proto.h
Purpose: Contains function prototypes
Notes:
************************************************/
#ifndef ALLVARS_H
   #include "allvars.h"
#endif



/***********************
         corr.c
***********************/
void calc_corr(void);
void prep_corr(void);



/***********************
         de.c
***********************/
void de_error_check(void);
float get_hubble(void);



/***********************
         init.c
***********************/
void init(int, char **);



/***********************
         read.c
***********************/
int read_spec_file(int);



/***********************
      read_param
***********************/
void read_param(char *);



/***********************
        write.c
***********************/
void write(void);
