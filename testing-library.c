#include <stdio.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char* describe(char* testDescription) {
  printf("%s\n" , testDescription);
}

char* it(char* testDescription, short unsigned int value) {
  printf(
    ANSI_COLOR_YELLOW 
    "   %s %s \n" ANSI_COLOR_RESET, testDescription, 
    value ? "✅" : "❌"
  );
}
