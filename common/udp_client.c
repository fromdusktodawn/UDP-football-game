/*************************************************************************
	> File Name: udp_client.c
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月04日 星期四 18时57分12秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int socket_udp() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return 1;
    }
    printf("Socket create.\n");
    return sockfd;
}
