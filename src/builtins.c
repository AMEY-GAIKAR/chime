#include <stdio.h>
#include <unistd.h>

#include "../include/colours.h"
#include "../include/utils.h"

int sh_cd(char** args) {
  
  if (args[1] == NULL) {
    printf(RED "no argument passed\n" COLOR_RESET);
  } else {
    if (chdir(args[1]) != 0) {
      perror(RED "chdir" COLOR_RESET);
    }
  }

  return 1;
}

int sh_echo(char** args) {
  
  int c = 1;
  
  while (args[c] != NULL) {
    printf("%s ", args[c]);
    c++;
  }

  printf("\n");

  return 1;
}

int sh_exit() {
  return 0;
} 

int sh_time() {
  GetTime();
  return 1;
}

int sh_getenv(char** args) {

  if (args[1] == NULL) {
    printf(RED "No argument passed.\n" COLOR_RESET);
  } else {
    GetEnvValue(args[1]);  
  }

  return 1;
}

int sh_setenv(char** args) {
  
  if (args[1] == NULL) {
    printf(RED "No arguments passed.\n" COLOR_RESET);
  } else if (args[2] == NULL) {
    printf(RED "Insufficient arguments.\n" COLOR_RESET);
  } else {
    SetEnvValue(args[1], args[2]);
  }

  return 1;
}

int sh_unsetenv(char** args) {

  if (args[1] == NULL) {
    printf(RED "No argument passed.\n" COLOR_RESET);
  } else {
    UnsetEnvValue(args[1]);
  }

  return 1;
}

char* builtin[] = {
  "sh_cd",
  "sh_exit",
  "sh_echo",
  "sh_time",
  "sh_getenv",
  "sh_setenv",
  "sh_unsetenv"
};

int (*builtinFunc[]) (char**) = {
  &sh_cd,
  &sh_exit,
  &sh_echo,
  &sh_time,
  &sh_getenv,
  &sh_setenv,
  &sh_unsetenv,
};

int NumBuiltins() {
  return sizeof(builtin) / sizeof(char*);
}
