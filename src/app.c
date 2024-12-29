#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#include "../include/utils.h"
#include "../include/builtins.h"
#include "../include/colours.h"

#define TOKEN_SEP " \t\n\r"

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

  token = strtok(line, TOKEN_SEP);

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
    
    token = strtok(NULL, TOKEN_SEP);
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
      printf(RED "sh: command not found: %s\n" COLOR_RESET, args[0]);
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
  
    printf(BLU "%s " COLOR_RESET, getlogin());
    char pwd[1024];
    if (getcwd(pwd, sizeof(pwd)) != NULL) {
      printf(CYN "%s\n" COLOR_RESET, pwd);
    } 

    printf(BMAG "> " COLOR_RESET);

    line = ReadLine(); 
    args = SplitLine(line);

    AddToHistory(line);

    status = Execute(args);
    
    free(line);
    free(args);
  
  } while(status);
}

#define MAX_CMD_LENGHT 1024

void ExecuteRedirection(char* cmd) {
  
  char* args[MAX_CMD_LENGHT];
  char* input_file = NULL;
  char* output_file = NULL;
  int arg_count = 0;

  char* token = strtok(cmd, TOKEN_SEP);
  while (token != NULL) {
    if (strcmp(token, "<") == 0) {
      token = strtok(NULL, TOKEN_SEP);
      input_file = token;
    } else if (strcmp(token, ">") == 0) {
      token = strtok(NULL, TOKEN_SEP);
      output_file = token;
    } else {
      args[arg_count++] = token;
    }
    token = strtok(NULL, TOKEN_SEP);
  }
  args[arg_count] = NULL;

  pid_t pid = fork();

  if (pid == 0) {

    if (input_file) {
      int fd_in = open(input_file, O_RDONLY);
      if (fd_in < 0) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
      }
      dup2(fd_in, STDIN_FILENO);
      close(fd_in);
    }

    if (output_file) {
      int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC);
      if (fd_out < 0) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
      }
      dup2(fd_out, STDOUT_FILENO);
      close(fd_out);
    }

    execvp(args[0], args);
    perror("Error executing command");
    exit(EXIT_FAILURE);

  } else if (pid > 0) {
    wait(NULL);
  } else {
    perror("Fork failed");
  }
} 

void ExecutePipeline(char* cmd1, char* cmd2) {

  int pipefd[2];
  pid_t pid1, pid2;

  if (pipe(pipefd) == -1) {
    perror("Pipe falied");
    exit(EXIT_FAILURE);
  }

  pid1 = fork();
  if (pid1 == -1) {
    perror("Fork failed");
    exit(EXIT_FAILURE);
  } else if (pid1 == 0) {
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);

    execvp(&cmd1[0], &cmd1);
    perror("Invalid commnad");
    exit(EXIT_FAILURE);
  }

  pid2 = fork();
  if (pid2 == -1) {
    perror("Fork failed");
    exit(EXIT_FAILURE);
  } else if (pid2 == 0) {
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);

    execvp(&cmd2[0], &cmd2);
    perror("Invalid commnad");
    exit(EXIT_FAILURE);
  }

  close(pipefd[0]);
  close(pipefd[1]);
  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);

}
