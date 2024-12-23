#include <stdio.h>
#include <time.h>

#include "../include/colours.h"

void GetTime() {
  
  time_t t;
  struct tm* timeinfo;
  
  time(&t);
  timeinfo = localtime(&t);

  printf(YEL "%s" COLOR_RESET, asctime(timeinfo));

}

