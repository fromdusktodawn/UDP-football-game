/*************************************************************************
	> File Name: send_ctl_stop.c
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年07月04日 星期六 14时21分53秒
 ************************************************************************/

#include "head.h"


extern int sockfd;
void send_ctl_stop() {
    struct FootBallMsg msg;
    msg.type = FT_CTL;
    msg.ctl.dirx = 0;
    msg.ctl.diry = 0;
    msg.ctl.action = ACTION_STOP;
    send(sockfd, &msg, sizeof(msg), 0);
    return ;
}
