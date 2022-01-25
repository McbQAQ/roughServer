#include <setEpoll.h>
#include <stdio.h>

int setNonBlocking(int fd) {
    int preOp = fcntl(fd, F_GETFL);
    int newOp = preOp | O_NONBLOCK;
    fcntl(fd, F_SETFL, newOp);
    return preOp;
}

void addFd(int epollFd, int fd, int events) {
#ifdef DEBUG
    printf("socket %d is added to epoll\n", fd);
#endif
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = events;
    epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &ev);
    setNonBlocking(fd);
}

void resetOneShot(int epollFd, int fd, int events) {
    epoll_event ev;
    ev.data.fd = fd;
    ev.events = events;
    epoll_ctl(epollFd, EPOLL_CTL_MOD, fd, &ev);
}

void removeFd(int epollFd, int fd) {
    epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, 0);
}
