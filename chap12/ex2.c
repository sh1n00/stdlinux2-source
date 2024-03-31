#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "$ "
#define LINE_BUF_SIZE 2024

static char* read_cmd();
static char** parse_cmd(char* buf);
static void* xmalloc(size_t size);

void main(int argc, char *argv[]) {
  for(;;) {
    fputs(PROMPT, stdout);
    char* buf = read_cmd();
    char** cmdline = parse_cmd(buf);
    
    pid_t pid;
    pid = fork();
    // fork失敗
    if(pid < 0) {
      perror("fork failed");
      exit(1);
    }
    if(pid > 0) {
      waitpid(pid, NULL, 0);
    } else {
      execvp(cmdline[0], cmdline);
      fprintf(stderr, "%s: command not found \n", cmdline[0]);
      exit(1);
    }
    free(buf);
    free(cmdline);
  }
}

static char* read_cmd() {
  char* buf = xmalloc(sizeof(char) * LINE_BUF_SIZE);
  char c;
  int position = 0;
  for(;;) {
    c = getchar();
    if(c == EOF || c == '\n') {
      buf[position] = '\0';
      break;
    } else {
      buf[position] = c;
    }
    position++;
  }
  return buf;
}

static char** parse_cmd(char* buf) {
  char** cmdline = xmalloc(sizeof(char**) * LINE_BUF_SIZE);
  cmdline[0] = strtok(buf, " ");
  int i = 1;
  for(;;) {
    cmdline[i] = strtok(NULL, " ");
    if(cmdline[i] == NULL) {
      cmdline[i] = NULL;
      break;
    }
    i++;
  }
  return cmdline;
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

