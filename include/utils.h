#ifndef UTILS_H
#define UTILS_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../include/colours.h"

void GetTime();

void GetEnvValue(const char *var);
void SetEnvValue(const char *var, const char *value);
void UnsetEnvValue(const char *var);

void AddToHistory(char *command);
void PrintHistory();

#endif // !UTILS_H
