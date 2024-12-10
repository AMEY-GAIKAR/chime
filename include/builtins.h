#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdio.h>
#include <unistd.h>

int sh_cd(char** args);
int sh_echo(char** args);
int sh_exit();

extern char* builtin[];

extern int (*builtinFunc[]) (char**);

int NumBuiltins();

#endif // !BUILTINS_H
