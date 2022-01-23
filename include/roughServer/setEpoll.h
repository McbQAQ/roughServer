#ifndef SETEPOLL_H
#define SETEPOLL_H

#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>

int setNonBlocking(int fd);

void addFd(int epollFd, int fd, int events);

void resetOneShot(int epollFd, int fd, int events);

void removeFd(int epollFd, int fd);

#endif //SETEPOLL_H
