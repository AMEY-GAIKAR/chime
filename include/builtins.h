#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdio.h>
#include <unistd.h>

#include "../include/utils.h"
#include "../include/colours.h"

int sh_cd(char** args);
int sh_echo(char** args);
int sh_exit();
int sh_time();

int sh_getenv(char** args);
int sh_setenv(char** args);
int sh_unsetenv(char** args);

int sh_history();

extern char* builtin[];
extern int (*builtinFunc[]) (char**);
int NumBuiltins();

#endif // !BUILTINS_H
