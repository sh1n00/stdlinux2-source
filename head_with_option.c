#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define _GNU_SOURCE
#include <getopt.h>

static void do_head(FILE *f, long nlines);

#define DEFAULT_N_LINES 10

static struct option longopts[] = {
    {"lines", required_argument, NULL, 'n'}
};

int main(int argc, char *argv[]){
    int i;
    int opt;
    long nlines = DEFAULT_N_LINES;
    char test[6] = "Thisa";
    while ((opt = getopt_long(argc, argv, "n:", longopts, NULL)) != -1){
        switch(opt){
        case 'n':
            nlines = atol(optarg);
            break;
        case '?':
            fprintf(stderr, "No arguments %s", argv[optind-1]);
            exit(1);
        }
    }
    if(optind == argc){
      do_head(stdin, nlines);
    } else{
      for(i = optind; i < argc; i++){
        FILE *f;
        f = fopen(argv[i], "r");
        if(!f){
          perror(argv[i]);
          exit(1);
        }
        do_head(f, nlines);
        fclose(f);
      }
    }
    exit(0);
}

static void do_head(FILE *f, long nlines){
  int c;
  if(nlines <= 0) return;
  while((c=fgetc(f)) != EOF){
    if(fputc(c, stdout) < 0) exit(1);
    if(c == '\n'){
      nlines--;
      if(nlines == 0) return;
    }  
  }
}

