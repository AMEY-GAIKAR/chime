#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#include "../include/builtins.h"

char* ReadLine() {

  int buffersize = 1024;
  int position = 0;
  char* buffer = (char*) malloc(sizeof(char) * buffersize);
  int c;

  if (!buffer) {
    printf("Allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= buffersize) {
      buffersize += 1024;
      buffer = realloc(buffer, buffersize);
    }

    if (!buffer) {
      printf("Allocation error\n");
      exit(EXIT_FAILURE);
    }
  }
}

char** SplitLine(char* line) {

  int buffersize = 64;
  int position = 0;
  char** tokens = malloc(sizeof(char*) * buffersize);
  char* token;
 
  if (!tokens) {
    printf("Allocation error\n");
  }

  token = strtok(line, " ");

  while (token != NULL) {
    tokens[position] = token;
    position++;

    if (position >= buffersize) {
      buffersize += 1024;

      tokens = realloc(tokens, sizeof(char*) * buffersize);
      
      if (!tokens) {
        printf("Allocation error\n");
      }
    }
    
    token = strtok(NULL, " ");
  }

  tokens[position] = NULL;
  
  return tokens;
}

int Execute(char** args) {

  if (args[0] == NULL) {
    return 1;
  }

  for (int i = 0; i < NumBuiltins(); i++) {
    if (strcmp(args[0], builtin[i]) == 0) {
      return (*builtinFunc[i])(args);
    }
  }

  pid_t cpid;
  int status;
  
  if (strcmp(args[0], "exit") == 0) {
    exit(0);
  }

  cpid = fork();

  if (cpid == 0) {
    if (execvp(args[0], args) < 0) {
      printf("dash: command not found: %s\n", args[0]);
    }
    exit(EXIT_FAILURE);
  } else if (cpid < 0) {
    printf("Error forking\n");
  } else {
    waitpid(cpid, &status, WUNTRACED);
  }

  return 1;
}

void MainLoop() {

  char* line;
  char** args;
  int status = 1;

  do {
  
    time_t t;
    struct tm* timeinfo;
    time(&t);
    timeinfo = localtime(&t);

    printf("\e[1;32m" "%s" "\e[0m", asctime(timeinfo));
    printf("\e[1;32m" "%s " "\e[0m", getlogin());
    char pwd[1024];
    if (getcwd(pwd, sizeof(pwd)) != NULL) {
      printf("%s\n", pwd);
    } 

    printf("\e[1;34m" "> " "\e[0m");

    line = ReadLine(); 
    args = SplitLine(line);
    status = Execute(args);
    
    free(line);
    free(args);
  
  } while(status);
}
