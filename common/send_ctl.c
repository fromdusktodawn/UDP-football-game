/*************************************************************************
	> File Name: send_ctl.c
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月17日 星期三 17时28分14秒
 ************************************************************************/

#include "head.h"

extern int sockfd;
extern struct FootBallMsg ctl_msg;
void send_ctl() {
    if (ctl_msg.ctl.dirx | ctl_msg.ctl.diry) {
        send(sockfd, (void *)&ctl_msg, sizeof(ctl_msg), 0);
    }
    ctl_msg.ctl.dirx = ctl_msg.ctl.diry = 0;
}

void send_ctl_stop() {
    struct FootBallMsg msg;
    bzero(&msg, sizeof(msg));
    msg.type = FT_CTL;
    msg.ctl.action = ACTION_STOP;
    send(sockfd, (void *)&msg, sizeof(msg), 0);
    return ;
}

void send_ctl_kick() {
    struct FootBallMsg msg;
    bzero(&msg, sizeof(msg));
    msg.type = FT_CTL;
    msg.ctl.action = ACTION_KICK;
    send(sockfd, (void *)&msg, sizeof(msg), 0);
    return ;
}

void send_ctl_carry() {
    struct FootBallMsg msg;
    bzero(&msg, sizeof(msg));
    msg.type = FT_CTL;
    msg.ctl.action = ACTION_CARRY;
    send(sockfd, (void *)&msg, sizeof(msg), 0);
    return ;
}

