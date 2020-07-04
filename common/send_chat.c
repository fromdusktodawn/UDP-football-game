/*************************************************************************
	> File Name: send_chat.c
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月16日 星期二 13时13分27秒
 ************************************************************************/

#include "head.h"

extern int sockfd;
extern WINDOW *Write;
extern struct FootBallMsg chat_msg;

void send_chat() {
#ifndef _D
    echo();
    nocbreak();
    bzero(chat_msg.msg, sizeof(chat_msg.msg));
    w_gotoxy_puts(Write, 1, 1, "Input Message : ");
    mvwscanw(Write, 2, 1, "%[^\n]s", chat_msg.msg);
    if (strlen(chat_msg.msg)) {
        send(sockfd, (void *)&chat_msg, sizeof(chat_msg.msg), 0);
    }
    //wclear(Write);
    werase(Write);
    box(Write, 0, 0);
    wrefresh(Write);
    noecho();
    cbreak();
#else
    DBG(GREEN"Input Message : ");
    scanf("%[^\n]s", chat_msg.msg);
    getchar();
    if (strlen(chat_msg.msg)) {
        send(sockfd, (void *)&chat_msg, sizeof(chat_msg.msg), 0);
    }
#endif
    return ;
}
