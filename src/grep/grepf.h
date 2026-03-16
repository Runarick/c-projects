#ifndef GREP_H
#define GREP_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
typedef struct {
    int v;
    int i;
    int l;
    int c;
    int n;
    int e;
    char **files;
    regex_t *regex_patterns;
    int files_c;
    int arg_c;
} Flags;
void free_flags(Flags *All);
void parser_f_flags_n_arg(int size, char *all_inp[], Flags *All, int *err);
void flag_add_n_check(char *sus_flags, Flags *All, int *err, int *e_ex);
void print_file_w_flags(Flags *All,char *name);
int print_from_one_line (Flags *All, char *buffer);
void print_current_string(Flags *All,char *buffer, int line_num, int str_found, char *file_name_str);
void fill_files(Flags *All, int size, char *all_inp[], int ent_arr[]);
int compile_regex_patterns(Flags *All, int size, char *all_inp[], int ent_arr[]);
void reg_com_free(Flags *All, int j);
char* rem_q(char *arg);
#endif