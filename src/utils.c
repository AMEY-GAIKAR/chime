#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "../include/colours.h"

void GetTime() {

  time_t t;
  struct tm* timeinfo;
  
  time(&t);
  timeinfo = localtime(&t);
  
  printf(YEL "%s" COLOR_RESET, asctime(timeinfo));

}

void GetEnvValue(const char* var) {

  char* value = getenv(var);
  
  if (value) {
    printf("%s=%s\n", var, value);
  } else {
    printf(RED "Environment variable '%s' not found.\n" COLOR_RESET, var);
  }
}

void SetEnvValue(const char* var, const char* value) {
  if (setenv(var, value, 1) == 0) {
    printf("Environment variable %s set to %s.\n", var, value);
  } else {
    printf(RED "Could not set %s to %s.\n" COLOR_RESET, var, value);
  }
}

void UnsetEnvValue(const char* var) {
  if (unsetenv(var) == 0) {
    printf("Environment variable '%s' has been unset.\n", var);
  } else {
    printf(RED "Could not unset %s.\n" COLOR_RESET, var);
  }
}
