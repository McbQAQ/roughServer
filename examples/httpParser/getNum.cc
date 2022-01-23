#include <string.h>
#include <stdio.h>
#include "httpParser.h"
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open((char*) "/var/www/index.html", O_RDONLY);
    char buf[1024];
    memset(buf, '\0', sizeof(buf));
    int len = read(fd, buf, 1024);
    printf("%d\n", len);

}
