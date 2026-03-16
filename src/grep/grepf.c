#include "grepf.h"
int main(int argc, char *argv[]) {
  int err = 0;
  Flags All = {0};
  parser_f_flags_n_arg(argc, argv, &All, &err);
  if (!err) {
    for (int i = 0; i < All.files_c; i++) {
      print_file_w_flags(&All, All.files[i]);
    }
    free_flags(&All);
  } else {
    printf("ERROR, check flags or smth");
  }
  return 0;
}

void free_flags(Flags *All) {
  if (All->files) free(All->files);
  if (All->regex_patterns) {
    for (int i = 0; i < All->arg_c; i++) {
      regfree(&All->regex_patterns[i]);
    }
    free(All->regex_patterns);
  }
}

void print_file_w_flags(Flags *All, char *name) {
  int str_found = 0, l_printed = 0, line_num = 1, c_line_count = 0;
  char file_name_str[128] = "", buffer[1024];
  if (All->files_c != 1) {
    strcpy(file_name_str, name);
    strcat(file_name_str, ":");
  }
  FILE *file = fopen(name, "r");
  if (file != NULL) {
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
      str_found = print_from_one_line(All, buffer);
      if (All->l == 1 && str_found && l_printed == 0) {
        printf("%s\n", name);
        l_printed = 1;
      }
      if (All->c == 1 && ((str_found == 1 && All->v == 0) ||
                          (str_found == 0 && All->v == 1))) {
        c_line_count++;
      }
      if (All->l == 0 && All->c == 0) {
        print_current_string(All, buffer, line_num, str_found, file_name_str);
      }
      line_num++;
    }
    if (All->l == 0 && All->c == 1) {
      printf("%s%d\n", file_name_str, c_line_count);
    }
    fclose(file);
  } else {
    printf("Путь к файлу %s указан неверно, либо его не существует\n", name);
  }
}

void print_current_string(Flags *All, char *buffer, int line_num, int str_found,
                          char *file_name_str) {
  if ((All->v == 1 && str_found == 0) || (All->v == 0 && str_found == 1)) {
    if (All->n == 1) {
      printf("%s%d:%s", file_name_str, line_num, buffer);
    } else {
      printf("%s%s", file_name_str, buffer);
    }
  }
}

int print_from_one_line(Flags *All, char *buffer) {
  int found = 0;
  for (int i = 0; i < All->arg_c; i++) {
    int regex_result = regexec(&All->regex_patterns[i], buffer, 0, NULL, 0);
    if (regex_result == 0) {
      found = 1;
    }
  }
  return found;
}

void parser_f_flags_n_arg(int size, char *all_inp[], Flags *All, int *err) {
  int e_ex = 0, arg_without_e = 0, first = 1, files_ex = 0;
  int *ent_arr = malloc(size * sizeof(int));
  for (int i = 1; i < size; i++) {
    if (all_inp[i][0] == '-' && e_ex == 0) {
      flag_add_n_check(all_inp[i], All, err, &e_ex);
      ent_arr[i] = 0;  // флаг
    } else if (e_ex == 1 || first == 1) {
      if (e_ex == 0) {
        arg_without_e = 1;
      }
      ent_arr[i] = 1;  // аргумент
      All->arg_c++;
      e_ex = first = 0;
    } else if (strcmp(all_inp[i], "") == 0) {
      ent_arr[i] = 3;  // двойные кавычки
      e_ex = 0;
    } else if (all_inp[i][0] != '-' && e_ex == 0) {
      ent_arr[i] = 2;  // файл
      All->files_c++;
      files_ex = 1;
    } else {
      *err = 1;
    }  // флаг после e  например
    if (arg_without_e == 1 && e_ex == 1) {
      *err = 1;
    }  // если аргументы поступают БЕЗ флага e и флаг е встречается, то ошибка
  }
  if (e_ex == 1 || files_ex == 0) {
    *err = 1;
  }  // после флага e не идет ничего - ошибка
  else {
    fill_files(All, size, all_inp, ent_arr);
    // Проверяет regex на ошибки
    if (compile_regex_patterns(All, size, all_inp, ent_arr) != 0) {
      *err = 1;
      free(All->files);
      All->files = NULL;
    }
  }
  free(ent_arr);
}

void fill_files(Flags *All, int size, char *all_inp[], int ent_arr[]) {
  All->files = malloc(All->files_c * sizeof(char *));
  for (int i = 1, j = 0; i < size; i++) {
    if (ent_arr[i] == 2) {
      All->files[j] = all_inp[i];
      j++;
    }
  }
}

int compile_regex_patterns(Flags *All, int size, char *all_inp[],
                           int ent_arr[]) {
  int err = 0;
  int comp_result = 0;
  All->regex_patterns = malloc(All->arg_c * sizeof(regex_t));
  for (int i = 1, j = 0; i < size; i++) {
    if (ent_arr[i] == 1) {
      char *corected_arg = rem_q(all_inp[i]);
      if (All->i == 1) {
        comp_result = regcomp(&All->regex_patterns[j], corected_arg, REG_ICASE);
      } else {
        comp_result =
            regcomp(&All->regex_patterns[j], corected_arg, REG_EXTENDED);
      }
      free(corected_arg);
      if (comp_result != 0) {
        // Ошибка компиляции regex
        reg_com_free(All, j);
        free(All->regex_patterns);
        All->regex_patterns = NULL;
        err = 1;
      }
      j++;
    }
  }
  return err;  // Успех
}

char *rem_q(char *arg) {
  int a_len = strlen(arg);
  char *corrected = NULL;
  if (a_len >= 2 && (arg[0] == '"' && arg[a_len - 1] == '"')) {
    corrected = malloc(a_len - 1);
    if (corrected) {  //
      strncpy(corrected, arg + 1, a_len - 2);
      corrected[a_len - 2] = '\0';
    }
  } else {
    corrected = malloc(a_len + 1);
    if (corrected) {
      strcpy(corrected, arg);
    }
  }
  return corrected;
}

void reg_com_free(Flags *All, int j) {
  for (int k = 0; k < j; k++) {
    regfree(&All->regex_patterns[k]);
  }
}

void flag_add_n_check(char *sus_flags, Flags *All, int *err, int *e_ex) {
  for (int i = 1; i < (int)strlen(sus_flags); i++) {
    // пройтись по всем эллементам и если они не входят в то эррор == 1;
    if (sus_flags[i] == 'e' && i == (int)strlen(sus_flags) - 1) {
      All->e = 1;
      *e_ex = 1;
    } else if (sus_flags[i] == 'v') {
      All->v = 1;
    } else if (sus_flags[i] == 'i') {
      All->i = 1;
    } else if (sus_flags[i] == 'l') {
      All->l = 1;
    } else if (sus_flags[i] == 'c') {
      All->c = 1;
    } else if (sus_flags[i] == 'n') {
      All->n = 1;
    } else {
      *err = 1;
    }
  }
}