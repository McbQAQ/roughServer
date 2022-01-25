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
    std::list<HttpRequest*> requestWait;

    const char *ip = "0.0.0.0";
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
        while(!requestWait.empty()) {
#ifdef DEBUG
            printf("try to add from wait request queue\n");
#endif
            if (!pool.add(requestWait.front())) {
                break;
            }
            requestWait.pop_front();
        }
        int num = epoll_wait(epollFd, events, MAX_EVENT_NUM, 5);
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
#ifdef DEBUG
                    printf("socket %d connect\n", connFd);
#endif
                    if (!request[connFd]) {
                    request[connFd] = new HttpRequest(connFd, epollFd);
                    }
                    addFd(epollFd, connFd, EPOLLIN|EPOLLET|EPOLLRDHUP|EPOLLONESHOT);
                }   
            }
            else if (events[i].events & (EPOLLRDHUP|EPOLLHUP|EPOLLERR)) {
#ifdef DEBUG
                printf("socket %d events HUP\n", sockFd);
#endif
                request[sockFd]->closeConnection();
            }
            else if (events[i].events & EPOLLIN) {
#ifdef DEBUG
                printf("socket %d events IN\n", sockFd);
#endif
                if(!pool.add(request[sockFd])) {
#ifdef DEBUG
                    printf("socket %d is added to waiting request queue\n", sockFd);
#endif
                    requestWait.push_back(request[sockFd]);
                }
            }
            else if (events[i].events & EPOLLOUT) {
#ifdef DEBUG
                printf("socket %d events OUT\n", sockFd);
#endif
                if (!pool.add(request[sockFd])) {
#ifdef DEBUG
                    printf("socket %d is added to waiting request queue\n", sockFd);
#endif
                    requestWait.push_back(request[sockFd]);
                }
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
