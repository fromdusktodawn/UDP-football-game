/*************************************************************************
	> File Name: show_data_stream.c
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月30日 星期二 19时22分43秒
 ************************************************************************/

#include "head.h"

extern char data_stream[20];
extern WINDOW *Help;
extern struct Map court;
// l, c, k, s, n, e
void show_data_stream(int type) {
    for (int i = 17; i >= 0; --i) {
        if (i > 0) data_stream[i] = data_stream[i - 1];
        else data_stream[i] = type;
        switch (data_stream[i]) {
            case 'l': {
                wattron(Help, COLOR_PAIR(7));
            } break;
            case 'c': {
                wattron(Help, COLOR_PAIR(9));
            } break;
            case 'k': {
                wattron(Help, COLOR_PAIR(8));
            } break;
            case 's': {
                wattron(Help, COLOR_PAIR(10));
            } break;
            case 'n': {
                wattron(Help, COLOR_PAIR(11));
            } break;
            case 'e': {
                wattron(Help, COLOR_PAIR(12));
            } break;
        }
        mvwprintw(Help, court.heigth, i + 1, " ");
        wrefresh(Help);
        wattron(Help, COLOR_PAIR(3));
    } 
    return; 
}
