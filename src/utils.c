#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../include/colours.h"

#define SH_HISTORY ".history"

#define MAX_HISTORY 1024

void GetTime() {

  time_t t;
  struct tm *timeinfo;

  time(&t);
  timeinfo = localtime(&t);

  printf(YEL "%s" COLOR_RESET, asctime(timeinfo));
}

void GetEnvValue(const char *var) {

  char *value = getenv(var);

  if (value) {
    printf("%s=%s\n", var, value);
  } else {
    printf(RED "Environment variable '%s' not found.\n" COLOR_RESET, var);
  }
}

void SetEnvValue(const char *var, const char *value) {
  if (setenv(var, value, 1) == 0) {
    printf("Environment variable %s set to %s.\n", var, value);
  } else {
    printf(RED "Could not set %s to %s.\n" COLOR_RESET, var, value);
  }
}

void UnsetEnvValue(const char *var) {
  if (unsetenv(var) == 0) {
    printf("Environment variable '%s' has been unset.\n", var);
  } else {
    printf(RED "Could not unset %s.\n" COLOR_RESET, var);
  }
}

void AddToHistory(char *command) {

  FILE *history = fopen(SH_HISTORY, "a");

  if (history == NULL) {
    printf("No history file found.\n");
    return;
  }

  fprintf(history, "%s\n", command);
  fclose(history);
}

void PrintHistory() {

  FILE *history = fopen(SH_HISTORY, "r");

  if (history == NULL) {
    printf("No history file found.\n");
    return;
  }

  char buffer[MAX_HISTORY];

  while (fgets(buffer, MAX_HISTORY, history)) {
    printf("%s", buffer);
  }

  fclose(history);
}
