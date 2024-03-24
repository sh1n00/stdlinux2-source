#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_cat(FILE *f);
static void die(FILE *f);

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    int i;
    if (argc < 2) {
        do_cat(stdin);
        exit(1);
    }
    for(i = 1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");
        if(!f) {
            perror(argv[i]);
            exit(1);
        }
        do_cat(f);
        fclose(f);
    }
    exit(0);
}


static void do_cat(FILE *f)
{
    char buf[BUFFER_SIZE];
    for (;;) {
        size_t n_read = fread(buf, sizeof(char), sizeof(buf), f);
        size_t n_written = fwrite(buf, sizeof(char), n_read, stdout);
        if (n_written < n_read) die(f);
        if(n_read < sizeof(buf)) break;
    }
    
}


static void die(FILE *f)
{
    ferror(f);
    exit(1);
}
