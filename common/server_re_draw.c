/*************************************************************************
	> File Name: server_re_draw.c
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月17日 星期三 17时44分13秒
 ************************************************************************/

#include "head.h"

extern struct Map court;
extern struct User *rteam, *bteam;
extern WINDOW *Message, *Football, *Football_t;
extern struct Bpoint ball;
extern struct BallStatus ball_status;
extern struct Score score;

void re_draw_play(int team, char *name, struct Point *loc) {
    char p = 'K';
    if (team) wattron(Football_t, COLOR_PAIR(6));
    else wattron(Football_t, COLOR_PAIR(2));
    w_gotoxy_putc(Football_t, loc->x, loc->y, p);
    w_gotoxy_puts(Football_t, loc->x + 1, loc->y - 1, name);
    return ;
}

void re_draw_team(struct User *team) {
    for (int i = 0; i < MAX; i++) {
        if (!team[i].online) continue;
        re_draw_play(team[i].team, team[i].name, &team[i].loc);
    }
    return ;
}

void re_draw_ball() {
    if ((int)ball_status.v.x || (int)ball_status.v.y) {
        int bx = (int) ball.x, by = (int) ball.y;
        ball.x = ball.x + ball_status.v.x * 0.1 + ball_status.a.x * 0.5 * 0.01;
        ball.y = ball.y + ball_status.v.y * 0.1 + ball_status.a.y * 0.5 * 0.01;
        ball_status.v.x += ball_status.a.x * 0.1;
        ball_status.v.y += ball_status.a.y * 0.1;
        int bbx = (int) ball.x, bby = (int) ball.y;
            char tmp[512] = {0};
    } else {
        ball.x = (int)ball.x;
        ball.y = (int)ball.y;
        if (ball_status.a.x || ball_status.a.y) {
            char tmp[512] = {0};
            struct User user;
            //struct FootBallMsg msg;
            //bzero(&msg, sizeof(msg));
            if (ball_status.who) {
                if (ball.x == 0 && (int)ball.y < court.heigth / 2 + 4 && (int)ball.y > court.heigth / 2 - 4) {
                    sprintf(tmp, "%s of %s team, get 1 score", ball_status.name, "blue");
                    sprintf(user.name, "%s", "Server Info");
                    user.team = ball_status.who;
                    score.blue += 1;
                    Show_Message(, &user, tmp, );
                }
            } else {
                if (ball.x == court.width - 1 && (int)ball.y < court.heigth / 2 + 3 && (int)ball.y > court.heigth / 2 - 3) {
                    sprintf(tmp, "%s of %s team, get 1 score", ball_status.name, "red");
                    sprintf(user.name, "%s", "Server Info");
                    user.team = ball_status.who;
                    score.red += 1;
                    Show_Message(, &user, tmp, );
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

void re_draw() {
    wclear(Football_t);
    wclear(Football);
    box(Football, 0, 0);
    box(Football_t, 0, 0);
    re_draw_team(rteam);
    re_draw_team(bteam);
    re_draw_ball();
    //wrefresh(Football_t);
    //wrefresh(Football);
    return ;
}
