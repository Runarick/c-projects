#include "catf.h"
int main(int argc, char *argv[]) {
  char flags[8] = "";
  int enfFlags = 1;
  int error = 0;

  parser_f_flags(argc, argv, flags, &enfFlags, &error);
  if (error == 1) {
    printf("Ошибка во влагах");
  } else {
    for (int i = enfFlags; i < argc; i++) {
      just_print_file(argv[i], flags);
    }
  }
  return 0;
}
void just_print_file(char *name, char *flag) {
  int prev_c = '\n';
  int str_num = 1;
  int empty_line = 0;
  FILE *file = fopen(name, "r");
  if (file != NULL) {
    int c;
    while ((c = fgetc(file)) != EOF) {
      print_w_flags(flag, c, &prev_c, &str_num, &empty_line);
    }
    fclose(file);
  } else {
    printf("Путь к файлу %s указан неверно, либо его не существует", name);
  }
}
void print_w_flags(char *flags, int c, int *prev_c, int *str_num,
                   int *empty_line) {
  if (!(strchr(flags, 's') != NULL && *prev_c == '\n' && c == '\n' &&
        *empty_line > 0)) {
    if ((strchr(flags, 'n') != NULL && strchr(flags, 'b') == NULL) &&
        *prev_c == '\n') {
      printf("%6d\t", *str_num);
      *str_num += 1;
    } else if (strchr(flags, 'b') != NULL && *prev_c == '\n' && c != '\n') {
      printf("%6d\t", *str_num);
      *str_num += 1;
    }
    if (strchr(flags, 'E') != NULL && c == '\n') {
      printf("$");
    }
    if (strchr(flags, 'v') != NULL && ((c >= 0 && c <= 31) || c == 127) &&
        c != '\n' &&
        c !=
            '\t') {  // может быть доделать для символов 128-255 по таблице аски
      if (c == 8) {  // искл
        printf("^H");
      } else if (c == 127) {  // искл
        printf("^?");
      } else {
        printf("^");
        putchar(c + 64);
      }
    } else if (strchr(flags, 'T') != NULL && c == '\t') {
      printf("^I");
    } else {
      putchar(c);
    }
  }
  if (*prev_c == '\n' && c == '\n') {
    *empty_line += 1;
  } else {
    *empty_line = 0;
  }
  *prev_c = c;
}
void parser_f_flags(int argc, char *all_inp[], char *flags, int *flend,
                    int *err) {
  int end = 0;
  for (int i = 1; i < argc && end == 0; i++) {
    if (all_inp[i][0] != '-') {
      *flend = i;
      end = 1;
    } else {
      append_n_check_flags(all_inp[i], flags, err);
    }
  }
}
void append_n_check_flags(char *sus_flags, char *flag, int *err) {
  int long_flag = 0;
  int loop = 0;
  EqvFlags all_flags_posible[9] = {{"b", "b"},
                                   {"--number-nonblank", "b"},
                                   {"e", "Ev"},
                                   {"n", "n"},
                                   {"--number", "n"},
                                   {"s", "s"},
                                   {"--squeeze-blank", "s"},
                                   {"t", "Tv"},
                                   {"v", "v"}};
  if (strcmp(sus_flags, "--number-nonblank") == 0 ||
      strcmp(sus_flags, "--number") == 0 ||
      strcmp(sus_flags, "--squeeze-blank") == 0) {
    long_flag = 1;
    for (int i = 0; i < 9; i++) {
      if (strcmp(sus_flags, all_flags_posible[i].flag) == 0) {
        append_finale(all_flags_posible[i].eqflag, flag);
      }
    }
  }
  for (int j = 1; j < (int)strlen(sus_flags) && long_flag == 0;
       j++) {  // если слишком много прохождений, то элемент отсутствует
    loop = 0;
    char temp[2] = "";
    temp[0] = sus_flags[j];
    for (int i = 0; i < 9;
         i++) {  // если хочу убрать E, T и v, то здесь тоже будет -3 : 11->8
      if (strcmp(temp, all_flags_posible[i].flag) == 0) {
        append_finale(all_flags_posible[i].eqflag, flag);
        loop = 0;
      } else if (loop == 8)  // если хочу убрать E, T и v, то здесь тоже будет
                             // -3 : 10->7
      {
        *err = 1;
      } else {
        loop++;
      }
    }
  }
}
void append_finale(char *ap_fl, char *flag) {
  for (int i = 0; i < (int)strlen(ap_fl); i++) {
    if (strchr(flag, ap_fl[i]) == NULL) {
      char temp[2] = "";
      temp[0] = ap_fl[i];
      strcat(flag, temp);
    }
  }
}
