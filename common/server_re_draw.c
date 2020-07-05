/*************************************************************************
	> File Name: server_re_draw.c
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月17日 星期三 17时44分13秒
 ************************************************************************/

#include "head.h"

extern struct Map court;
extern struct User *rteam, *bteam;
extern WINDOW *Message, *Football, *Football_t, *Score;
extern struct Bpoint ball;
extern struct BallStatus ball_status;
extern struct Score score;

void re_draw_play(int team, char *name, struct Point *loc, int carry) {
    char p = 'K';
    if (team) wattron(Football_t, COLOR_PAIR(6));
    else wattron(Football_t, COLOR_PAIR(2));
    w_gotoxy_putc(Football_t, loc->x, loc->y, p);
    w_gotoxy_puts(Football_t, loc->x + 1, loc->y - 1, name);
    if (carry && ball_status.carry && !strcmp(name, ball_status.name)) {
        ball.x = loc->x - 2;
        ball.y = loc->y - 1 + 1;
        ball_status.a.x = 0;
        ball_status.a.y = 0;
        ball_status.v.x = 0;
        ball_status.v.y = 0;
    }
    return ;
}

void re_draw_team(struct User *team) {
    for (int i = 0; i < MAX; i++) {
        if (!team[i].online) continue;
        re_draw_play(team[i].team, team[i].name, &team[i].loc, team[i].carry);
    }
    return ;
}

void send_cjson(char *string, int type) {
    for (int i = 0; i < MAX; i++) {
        if (bteam[i].online) {
            struct FootBallMsg msg;
            msg.type = type;
            strcpy(msg.msg, string);
            send(bteam[i].fd, (void *)&msg, sizeof(msg), 0);
        }
        if (rteam[i].online) {
            struct FootBallMsg msg;
            msg.type = type;
            strcpy(msg.msg, string);
            send(rteam[i].fd, (void *)&msg, sizeof(msg), 0);
        }
    }
    return ;
}

char *create_cjson_score() {
    char *string = NULL;
    cJSON *monitor = cJSON_CreateObject();
    cJSON *scores = cJSON_AddObjectToObject(monitor, "score");
    cJSON_AddNumberToObject(monitor, "who", ball_status.who);
    cJSON_AddStringToObject(monitor, "name", ball_status.name);
    cJSON_AddNumberToObject(scores, "blue", score.blue);
    cJSON_AddNumberToObject(scores, "red", score.red);
    string = cJSON_Print(monitor);
    return string;
}

void re_draw_ball() {
    if ((int)ball_status.v.x || (int)ball_status.v.y) {
        ball.x = ball.x + ball_status.v.x * 0.1 + ball_status.a.x * 0.5 * 0.01;
        ball.y = ball.y + ball_status.v.y * 0.1 + ball_status.a.y * 0.5 * 0.01;
        ball_status.v.x += ball_status.a.x * 0.1;
        ball_status.v.y += ball_status.a.y * 0.1;
        ball_status.carry = 0;
    } else {
        ball.x = (int)ball.x;
        ball.y = (int)ball.y;
        if (ball_status.a.x || ball_status.a.y || ball_status.carry) {
            char tmp[512] = {0};
            if (ball_status.who) {
                if (ball.x == 0 && (int)ball.y < court.heigth / 2 + 4 && (int)ball.y > court.heigth / 2 - 4) {
                    ball_status.carry = 0;
                    sprintf(tmp, "%s of %s team, get 1 score", ball_status.name, "blue");
                    Show_Message(, , tmp, 1);
                    score.blue += 1;
                    ball_status.carry = 0;
                    Show_Score();
                    char *string = create_cjson_score();
                    send_cjson(string, FT_SCORE);
                }
            } else {
                if (ball.x == court.width - 1 && (int)ball.y < court.heigth / 2 + 3 && (int)ball.y > court.heigth / 2 - 3) {
                    ball_status.carry = 0;
                    sprintf(tmp, "%s of %s team, get 1 score", ball_status.name, "red");
                    Show_Message(, , tmp, 1);
                    score.red += 1;
                    ball_status.carry = 0;
                    Show_Score();
                    char *string = create_cjson_score();
                    send_cjson(string, FT_SCORE);
                }
            }
        }
        ball_status.a.x = 0;
        ball_status.a.y = 0;
    }
    if (ball.x < 0) ball.x = 0;
    if (ball.y < 0) ball.y = 0;
    if ((int)ball.x > court.width - 1) ball.x = court.width - 1;
    if (ball.y > court.heigth - 1) ball.y = court.heigth - 1;
    w_gotoxy_putc(Football, (int)ball.x, (int)ball.y, 'O');
}

char *create_cjson_football() {
    char *string = NULL;
    cJSON *reds = NULL;
    cJSON *blues = NULL;
    cJSON *balls = NULL;
    cJSON *name = NULL;
    cJSON *who = NULL;
    cJSON *x = NULL;
    cJSON *y = NULL;
    //cJSON_CreateStirng("string");
    //cJSON_AddItemToObject(monitor, "name", name);
    //cJSON_AddStringItemToObject(monitor, "name", "string");
    //resolutions = cJSON_CreateArray();
    //cJSON_AddItemToObject(monitor, "resolutions", resolutions);
    //resolution = cJSON_CreateObject();
    //cJSON_AddItemToArray(resolutions, resolution);
    //width = cJSON_CreateNumber(resolution_numbers[index][0]);
    //cJSON_AddItemToObject(resolution, "width", width);
    cJSON *monitor = cJSON_CreateObject();
    reds = cJSON_AddArrayToObject(monitor, "reds");
    blues = cJSON_AddArrayToObject(monitor, "blues");
    for (int i = 0; i < MAX; i++) {
        if (!rteam[i].online) continue;
        cJSON *red = cJSON_CreateObject();
        cJSON_AddStringToObject(red, "name", rteam[i].name);
        cJSON_AddNumberToObject(red, "x", rteam[i].loc.x);
        cJSON_AddNumberToObject(red, "y", rteam[i].loc.y);
        cJSON_AddItemToArray(reds, red);
    }
    for (int i = 0; i < MAX; i++) {
        if (!bteam[i].online) continue;
        cJSON *blue = cJSON_CreateObject();
        cJSON_AddStringToObject(blue, "name", bteam[i].name);
        cJSON_AddNumberToObject(blue, "x", bteam[i].loc.x);
        cJSON_AddNumberToObject(blue, "y", bteam[i].loc.y);
        cJSON_AddItemToArray(blues, blue);
    }
    balls = cJSON_CreateObject();
    cJSON_AddNumberToObject(balls, "who", ball_status.who);
    cJSON_AddStringToObject(balls, "name", ball_status.name);
    cJSON_AddNumberToObject(balls, "x", ball.x);
    cJSON_AddNumberToObject(balls, "y", ball.y);
    cJSON_AddItemToObject(monitor, "ball", balls);
    string = cJSON_Print(monitor);
    return string;
}

void re_draw() {
    werase(Football_t);
    werase(Football);
    box(Football, 0, 0);
    box(Football_t, 0, 0);
    re_draw_team(rteam);
    re_draw_team(bteam);
    re_draw_ball();
    char *string = create_cjson_football();
    send_cjson(string, FT_GAME);
    wrefresh(Football_t);
    wrefresh(Football);
    return ;
}
