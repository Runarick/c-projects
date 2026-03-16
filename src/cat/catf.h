#ifndef CATF_H
#define CATF_H
#include <stdio.h>
#include <string.h>

typedef struct {
    char *flag;
    char *eqflag;
} EqvFlags;

void just_print_file(char *name,char *flag);
void parser_f_flags(int argc, char *all_inp[], char *flags, int *flend,int *err);
void append_n_check_flags(char *sus_flags, char *flag, int *err);
void append_finale(char *ap_fl,char *flag);
void print_w_flags(char *flags, int c, int *prev_c, int *str_num, int *empty_line);
#endif