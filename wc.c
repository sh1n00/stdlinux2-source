#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_wc(const char *path);
static void die(const char *s);

int main(int argc, char *argv[])
{
	int i;
	if (argc < 2) {
		do_wc("/dev/stdin");	
		exit(1);
	}
	for(i = 1; i < argc; i++) {
		do_wc(argv[i]);
	}
	exit(0);
}

#define BUFFER_SIZE 2048

static void do_wc(const char *path)
{
	int fd;
	unsigned char buf[BUFFER_SIZE];
	int n;
	int counter = 0;
	
	fd = open(path, O_RDONLY);
	if (fd < 0) die(path);
	for (;;) {
		n = read(fd, buf, 1);
		if (n < 0) die(path);
		if (n == 0) break;
		if(buf[0] == '\n') {
			counter++;
		}
	}
	char counter_str[12];
	int length = snprintf(counter_str, sizeof(counter), "%d\n", counter);
	if (write(STDOUT_FILENO, counter_str, length) < 0) die(path);
	if (close(fd) < 0) die(path);
}

static void die(const char *s)
{
	perror(s);
	exit(1);
}
