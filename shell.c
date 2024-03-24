#include <stdio.h>

#define PROMPT "$ "

int main(int argc, char* argv[]) {
  for(;;){
    fprintf(stdout, PROMPT);
  }
}
