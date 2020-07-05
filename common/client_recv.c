/*************************************************************************
	> File Name: client_recv.c
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月13日 星期六 14时13分24秒
 ************************************************************************/

#include "head.h"

extern int sockfd;
extern WINDOW *Message;
extern struct User bteam[MAX], rteam[MAX];

void *client_recv(void *arg) {
    while (1) {
        struct FootBallMsg msg;
        struct User user;
        bzero(&msg, sizeof(msg));
        recv(sockfd, (void *)&msg, sizeof(msg), 0);
        strcpy(user.name, msg.name);
        user.team = msg.team;
        if (msg.type & FT_TEST) {
            DBG(RED"HearBeat form server 💓\n"NONE);
            msg.type = FT_ACK;
            send(sockfd, (void *)&msg, sizeof(msg), 0);
        } else if (msg.type & FT_MSG) {
            DBG(GREEN"%s : "NONE"%s\n", user.name, msg.msg);
            Show_Message(, &user, msg.msg, 0);
        } else if (msg.type & FT_WALL) {
            DBG(GREEN"server msg: "NONE"%s\n", msg.msg);
            Show_Message(, NULL, msg.msg, 1);
        } else if (msg.type & FT_FIN) {
            DBG(GREEN"Server is going to stop.\n"NONE);
            endwin();
            exit(0);
        } else if (msg.type & FT_GAME) {
            cJSON *monitor_json = cJSON_Parse(msg.msg);
            cJSON *reds = cJSON_GetObjectItemCaseSensitive(monitor_json, "reds");
            cJSON *blues = cJSON_GetObjectItemCaseSensitive(monitor_json, "blues");
            cJSON *balls = cJSON_GetObjectItemCaseSensitive(monitor_json, "ball");
            cJSON *red = NULL, *blue = NULL;
            //int cnt = 0;
            //cJSON_ArrayForEach(red, reds) {
            //    if (red == NULL) break;
            //    cJSON *name = cJSON_GetObjectItemCaseSensitive(red, "name");
            //    cJSON *x = cJSON_GetObjectItemCaseSensitive(red, "x");
            //    cJSON *y = cJSON_GetObjectItemCaseSensitive(red, "y");
            //    rteam[cnt].online = 1;
            //    rteam[cnt].loc.x = (int)x->valueint;
            //    rteam[cnt].loc.y = (int)y->valueint;
            //    strcpy(rteam[cnt].name, name->valuestring);
            //    cnt++;
            //}
            //cnt = 0;
            //cJSON_ArrayForEach(blue, blues) {
            //    if (blue == NULL) break;
            //    cJSON *name = cJSON_GetObjectItemCaseSensitive(blue, "name");
            //    cJSON *x = cJSON_GetObjectItemCaseSensitive(blue, "x");
            //    cJSON *y = cJSON_GetObjectItemCaseSensitive(blue, "y");
            //    if (x == NULL) {
            //        char tmp[512] = {0};
            //        sprintf(tmp, "NULL");
            //        Show_Message(, , tmp, 1);
            //    }
            //    //rteam[cnt].online = 1;
            //    //rteam[cnt].loc.x = x->valueint;
            //    //rteam[cnt].loc.y = y->valueint;
            //    //strcpy(rteam[cnt++].name, name->valuestring);
            //}
            int rsize = cJSON_GetArraySize(reds);
            int bsize = cJSON_GetArraySize(blues);
            //char tmp[512] = {0};
            //sprintf(tmp, "%d", bsize);
            //Show_Message(, , tmp, 1);
            for (int i = 0; i < rsize; i++) {
                //
            }
            for (int i = 0; i < bsize; i++) {
                blue = cJSON_GetArrayItem(blues, i);
                cJSON *name = cJSON_GetObjectItemCaseSensitive(blue, "name");
                if (name == NULL) {
                    char tmp[512] = {0};
                    sprintf(tmp, "blue == NULL");
                    Show_Message(, , tmp, 1);
                }
                //cJSON *x = cJSON_GetObjectItemCaseSensitive(blue, "x");
                //cJSON *y = cJSON_GetObjectItemCaseSensitive(blue, "y");
                //rteam[i].online = 1;
                //rteam[i].loc.x = x->valueint;
                //rteam[i].loc.y = y->valueint;
                //strcpy(rteam[i].name, name->valuestring);
            }
            client_re_draw();
        } else {
            DBG(GREEN"MSG unsupprotable\n"NONE);
        }
    }
    return NULL;
}
