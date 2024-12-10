#include <stdio.h>
#include <unistd.h>

int sh_cd(char** args) {
  
  if (args[1] == NULL) {
    printf("expected argument, got none\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("invalid directory\n");
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

char* builtin[] = {
  "sh_cd",
  "sh_exit",
  "sh_echo"
};

int (*builtinFunc[]) (char**) = {
  &sh_cd,
  &sh_exit,
  &sh_echo
};

int NumBuiltins() {
  return sizeof(builtin) / sizeof(char*);
}
