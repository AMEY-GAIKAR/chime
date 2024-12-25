#ifndef APP_H
#define APP_H

#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#include "../include/utils.h"
#include "../include/builtins.h"
#include "../include/colours.h"

char* ReadLine();
char** SplitLine(char* line);
int Execute(char** args);
void MainLoop();

#endif // !APP_H
