/*************************************************************************
	> File Name: client_re_draw.c
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年07月05日 星期日 16时54分48秒
 ************************************************************************/


#include "head.h"

extern struct User bteam[MAX], rteam[MAX];
extern WINDOW *Football_t, *Football;

void client_re_draw() {
    werase(Football_t);
    werase(Football);
    box(Football_t, 0, 0);
    box(Football, 0, 0);
    for (int i = 0; i < MAX; i++) {
        if (!bteam[i].online) continue;
        char p = 'K';
        wattron(Football_t, COLOR_PAIR(6));
        w_gotoxy_putc(Football_t, bteam[i].loc.x, bteam[i].loc.y, p);
        w_gotoxy_puts(Football_t, bteam[i].loc.x + 1, bteam[i].loc.y - 1, bteam[i].name);
    }
    for (int i = 0; i < MAX; i++) {
        if (!rteam[i].online) continue;
        char p = 'K';
        wattron(Football_t, COLOR_PAIR(2));
        w_gotoxy_putc(Football_t, rteam[i].loc.x, rteam[i].loc.y, p);
        w_gotoxy_puts(Football_t, rteam[i].loc.x + 1, rteam[i].loc.y - 1, rteam[i].name);
    }
    return ;
}
