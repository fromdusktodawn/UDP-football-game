/*************************************************************************
	> File Name: udp_epoll.h
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月04日 星期四 19时24分23秒
 ************************************************************************/

#ifndef _UDP_EPOLL_H
#define _UDP_EPOLL_H

#include "head.h"
void add_event(int epollfd, int fd, int events);
void del_event(int epollfd, int fd);
//int udp_connect(int epollfd, struct sockaddr *serveraddr);
int udp_accept(int epollfd, int fd, struct User *user);
void add_to_sub_reactor(struct User *user);

#endif
