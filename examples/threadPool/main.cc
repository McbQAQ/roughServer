#include <stdio.h>
#include "threadPool.h"
#include "httpRequest.h"
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>

#define MAX_FD 1024
#define MAX_EVENT_NUM 1000


int main() {
    HttpRequest *request[MAX_FD] {nullptr};

    const char *ip = "192.168.220.137";
    int port = 80;
    int lisSock = socket(PF_INET, SOCK_STREAM, 0);

    sockaddr_in lisAddr;
    bzero(&lisAddr, sizeof(lisAddr));
    lisAddr.sin_family = AF_INET;
    lisAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &lisAddr.sin_addr);

    if (bind(lisSock, (sockaddr*) &lisAddr, sizeof(lisAddr)) != 0) {
        printf("error occur in binding socket, errno: %d\n", errno);
        return 0;
    }
    if (listen(lisSock, 32) != 0) {
        printf("error occur in listening socket\n");
        return 0;
    }

    ThreadPool pool(4, 8);

    epoll_event events[MAX_EVENT_NUM];
    int epollFd = epoll_create(5);
    
    addFd(epollFd, lisSock, EPOLLIN|EPOLLET|EPOLLRDHUP);
    while(1) {
        int num = epoll_wait(epollFd, events, MAX_EVENT_NUM, -1);
        if (num < 0 && errno != EINTR) {
            printf("epoll error\n");
            break;
        }

        for(int i = 0; i < num; ++i) {
            int sockFd = events[i].data.fd;
            if (sockFd == lisSock) {
                sockaddr_in clientAddr;
                socklen_t clientAddrLen = sizeof(clientAddr);
                int connFd;
                while(1) {
                    connFd = accept(lisSock, (sockaddr*) &clientAddr, &clientAddrLen);
                    if (connFd < 0) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            break;
                        }
                        else {
                            printf("accept fail, errno: %d\n", errno);
                            return 1;
                        }
                    }
                    if (connFd > MAX_FD) {
                        printf("internal busy\n");
                        continue;
                    }
                    //printf("new connection fd: %d\n", connFd);
                    if (!request[connFd]) {
                    request[connFd] = new HttpRequest(connFd, epollFd);
                    }
                    addFd(epollFd, connFd, EPOLLIN|EPOLLET|EPOLLRDHUP|EPOLLONESHOT);
                }   
            }
            else if (events[i].events & (EPOLLRDHUP|EPOLLHUP|EPOLLERR)) {
                //printf("client close connection\n");
                request[sockFd]->closeConnection();
            }
            else if (events[i].events & EPOLLIN) {
                pool.add(request[sockFd]);
            }
            else if (events[i].events & EPOLLOUT) {
                pool.add(request[sockFd]);
            }
            else {

            }
        }
    }

    for (int i = 0; i < MAX_FD; ++i) {
        if (request[i]) {
            request[i]->closeConnection();
            delete request[i];
        }
    }
    close(epollFd);
    close(lisSock);
    
    return 0;
    
}
