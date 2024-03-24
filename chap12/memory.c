#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char *p;
  char *rp;

  // メモリ取得
  p = malloc(128);
  if (p == NULL) {
    exit(1);
  }
  
  snprintf(p, 128, "Hello World");
  printf("%s", p);
  // メモリサイズの変更
  rp = realloc(p, 256);
  if (rp == NULL) {
    free(p);
    exit(1);
  }

  printf("%p\n", p);
  printf("%p\n", rp);

  free(rp);
  return 0;
}

void *xmalloc(size_t size) {
  void *ret;
  ret = malloc(size);
  if(ret == NULL) {
    exit(1);
  }

  return ret;
}


