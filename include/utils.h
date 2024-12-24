#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <time.h>

#include "../include/colours.h"

void GetTime();

void GetEnvValue(const char* var);
void SetEnvValue(const char* var, const char* value);
void UnsetEnvValue(const char* var);

#endif // !UTILS_H
