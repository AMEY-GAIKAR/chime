#ifndef APP_H
#define APP_H

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "../include/builtins.h"
#include "../include/colours.h"
#include "../include/utils.h"

char* ReadLine();
char** SplitLine(char* line);
int Execute(char** args);
void MainLoop();

#endif // !APP_H
