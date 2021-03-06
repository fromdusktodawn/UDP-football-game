/*************************************************************************
	> File Name: game.h
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月15日 星期一 18时44分45秒
 ************************************************************************/

#ifndef _GAME_H
#define _GAME_H
#include "head.h"
#define MAX 50
#define DEFARG(name, default_value) ((#name[0]) ? (name + 0) : default_value)

#define Show_Message(arg0, arg1, arg2, arg3) show_message(DEFARG(arg0, Message), DEFARG(arg1, NULL), arg2, DEFARG(arg3, 0))

WINDOW *create_newwin(int width, int height, int startx, int starty);
void destroy_win(WINDOW *win);
void gotoxy(int x, int y);
void gotoxy_putc(int x, int y, int c);
void gotoxy_puts(int x, int y, char *s);
void w_gotoxy_putc(WINDOW *win, int x, int y, int c);
void w_gotoxy_puts(WINDOW *win, int x, int y, char *s);
void initfootball();
void *draw(void *arg);
void show_message(WINDOW *win, struct User *user, char *msg, int type);
void Show_Score();

#endif
