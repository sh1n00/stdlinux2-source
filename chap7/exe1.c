#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

static void do_cat(FILE *f, int isVis);

#define DEFAULT_N_LINES 10

int main(int argc, char *argv[]){ 
  int opt;
  long nlines = DEFAULT_N_LINES;
  int isVis = 0;
  while ((opt = getopt(argc, argv, "v")) != -1)
  {
    switch(opt){
      case 'v':
        isVis = 1;
        break;
      case '?':
        fprintf(stderr, "Unexpected arguments %c\n", optopt);
        break;
    }
  }
  argc -= optind;
  argv += optind;
  if (argc == 0){
    do_cat(stdin, isVis);
    exit(0);
  } else {
    int i;
    for(i = 0; i < argc; i++){
      FILE *f;
      f = fopen(argv[i], "r");
      if(!f){
        perror(argv[i]);
        exit(1);
      }
      do_cat(f, isVis);
      fclose(f);
    }
  }
  exit(0);
}


static void do_cat(FILE *f, int isVis){
  int c;
  if (isVis){
    while((c=fgetc(f)) != EOF){
      switch(c){
        case '\t':
          if(fputs("\\t", stdout) == EOF) exit(1);
          break;
        case '\n':
          if(fputs("\\n\n", stdout) == EOF) exit(1);
          break;
        default:
          if(putchar(c) < 0) exit(1);
          break;
      }
    }  
  } else {
      while((c = fgetc(f)) != EOF){
          if(putchar(c) == EOF) {
            exit(1);
          }
      }  
  }
}
