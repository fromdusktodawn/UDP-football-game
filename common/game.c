/*************************************************************************
	> File Name: game.c
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月07日 星期日 20时41分49秒
 ************************************************************************/


#include "head.h"

struct Map court;
extern struct Score score;

WINDOW *Football, *Football_t, *Message, *Help, *Score, *Write;
char info[3][1024] = {0};

//void clean(WINDOW, int sx, int sy; int width, int heigth) {
//    for (int i = 0; i < height; i++) {
//        for (int j = 0; j < width; j++) {
//            gotoxy_putc(sx + width)
//        }
//    }
//}

WINDOW *create_newwin(int width, int heigth, int startx, int starty) {
    WINDOW *win;
    win = newwin(heigth, width, starty, startx);
    box(win, 0, 0);
    wrefresh(win);
    move(LINES - 1, 1);
    return win;
}

void destroy_win(WINDOW *win) {
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
    return ;
}

void gotoxy(int x, int y) {
    move(y, x);
}

void gotoxy_putc(int x, int y, int c) {
    move(y, x);
    addch(c);
    move(LINES - 1, 1);
    refresh();
}

void gotoxy_puts(int x, int y, char *s) {
    move(y, x);
    addstr(s);
    move(LINES - 1, 1);
    refresh();
}

void w_gotoxy_putc(WINDOW *win, int x, int y, int c) {
    mvwaddch(win, y, x, c);
    move(LINES - 1, 1);
    wrefresh(win);
    return ;
}

void w_gotoxy_puts(WINDOW *win, int x, int y, char *s) {
    mvwprintw(win, y, x, s);
    move(LINES - 1, 1);
    wrefresh(win);
    return ;
}

void initfootball() {
    initscr();
    clear();
    if (!has_colors() || start_color() == ERR) {
        endwin();
        fprintf(stderr, "终端不支持颜色");
        exit(1);
    }
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    init_pair(7, COLOR_BLACK, COLOR_YELLOW);
    init_pair(8, COLOR_BLUE, COLOR_RED);
    init_pair(9, COLOR_BLUE, COLOR_GREEN);
    init_pair(10, COLOR_BLUE, COLOR_WHITE);
    init_pair(11, COLOR_BLUE, COLOR_CYAN);
    init_pair(12, COLOR_BLUE, COLOR_MAGENTA);

    Football_t = create_newwin(court.width + 4, court.heigth + 2, court.start.x - 2, court.start.y - 1);
    //Football = create_newwin(court.width - 4, court.heigth - 2, court.start.x + 2, court.start.y + 1);
    Football = subwin(Football_t, court.heigth, court.width, court.start.y, court.start.x);
    box(Football, 0, 0);
    wrefresh(Football);
    //move(LINES - 1, 1);
    WINDOW *Message_t = create_newwin(court.width + 4, 7, court.start.x - 2, court.start.y + court.heigth + 1);
    Message = subwin(Message_t, 5, court.width + 2, court.start.y + court.heigth + 2, court.start.x - 1);
    //box(Message, 0, 0);
    scrollok(Message, 1);
    Help = create_newwin(20, court.heigth + 2, court.start.x + court.width + 2, court.start.y - 1);
    Score = create_newwin(20, 7, court.start.x + court.width + 2, court.start.y + court.heigth + 1);
    Write = create_newwin(court.width + 20 + 4, 5, court.start.x - 2, court.start.y + court.heigth + 7 + 1);
    Show_Score();
    return ;
}

void *draw(void *arg) {
    initfootball();
    while (1) {
        sleep(10);
    }
    return NULL;
}

int Message_num = 0;
void show_message(WINDOW *win, struct User *user, char *msg, int type) {
    time_t time_now = time(NULL);
    struct tm* tm = localtime(&time_now);
    char timestr[20] = {0};
    char username[80] = {0};
    sprintf(timestr, "%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
    if (type) {
        wattron(win, COLOR_PAIR(4));
        sprintf(username, "server info : ");
    } else {
        if (user->team) 
            wattron(win, COLOR_PAIR((6)));
        else 
            wattron(win, COLOR_PAIR((2)));
        sprintf(username, "%s : ", user->name);
    }

    if (Message_num >= 5) scroll(win), Message_num = 4;

    w_gotoxy_puts(win, 10, Message_num, username);
    wattron(win, COLOR_PAIR(3));
    w_gotoxy_puts(win, 10 + strlen(username), Message_num, msg);
    wattron(win, COLOR_PAIR(5));
    w_gotoxy_puts(win, 1, Message_num, timestr);
    Message_num++;
    wrefresh(win);
    return ;
}

void Show_Score() {
    werase(Score);
    box(Score, 0, 0);
    char tmp[512] = {0};
    sprintf(tmp, "blue %d : %d red", score.blue, score.red);
    w_gotoxy_puts(Score, 3, 3, tmp);
    wrefresh(Score);
    return ;
}
