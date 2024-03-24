#include <stdio.h>

#define PROMPT "$ "

void main(int argc, char *argv[]) {
  for(;;) {
    fputs(PROMPT, stdout);
        
  }
}

static void* xmalloc(size_t size) {
  void *p;
  p = malloc(size);
  if(p == NULL) {
    perror("malloc");
    exit(1);
  }
  return p;
}

