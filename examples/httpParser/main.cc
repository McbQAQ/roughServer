#include "httpParser.h"
#include "httpResponder.h"
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int main() {
    int fd = open((char*) "./typicalHTTPMessage", O_RDONLY);
    char buf[1024];
    memset(buf, '\0', sizeof(buf));
    int len1 = read(fd, buf, 25);

    //printf("%s", buf);

    HttpParser parser(buf, 1024);
    HttpParser::LineParserStatus s = parser.parse();
    printf("%d\n", s);

    
    int len2 = read(fd, buf + len1, 50);

    //c = buf;
    //while(*c) {
        //printf("%c", *c);
        //c++;
    //}


    s = parser.parse();
    printf("%d\n", s);


    int len3 = read(fd, buf + len1 + len2, 1024);
    s = parser.parse();
    printf("%d\n", s);

    HttpResponder hr(&parser, "/var/www");
    hr.padding();

    //printf("\n\n");
    //hr.init(&parser);
    //hr.padding();
    return 0;
}
