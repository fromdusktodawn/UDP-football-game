/*************************************************************************
	> File Name: server.c
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月11日 星期四 00时19分40秒
 ************************************************************************/

#include "../common/head.h"

char server_ip[20] = {0};
int server_port = 0;
char *conf = "./client.conf";
int sockfd;
struct User bteam[MAX], rteam[MAX];
struct Score score;
struct Bpoint ball;

extern struct Map court;
extern WINDOW *Write;
struct FootBallMsg chat_msg;
struct FootBallMsg ctl_msg;

void logout(int signum) {
    struct FootBallMsg msg;
    msg.type = FT_FIN;
    send(sockfd, (void *)&msg, sizeof(msg), 0);
    endwin();
    exit(1);
}

int main(int argc, char **argv)  {
    int opt;
    pthread_t recv_t, draw_t;
    struct LogRequest request;
    struct LogResponse response;
    bzero(&request, sizeof(request));
    bzero(&chat_msg, sizeof(chat_msg));
    bzero(&ctl_msg, sizeof(ctl_msg));

    chat_msg.type = FT_MSG;
    ctl_msg.type = FT_CTL;

    while ((opt = getopt(argc, argv, "h:p:n:t:m:")) != -1) {
        switch (opt) {
            case 'h':
                strcpy(server_ip, optarg);
                break;
            case 'p':
                server_port = atoi(optarg);
                break;
            case 'n':
                strcpy(request.name, optarg);
                break;
            case 't':
                request.team = atoi(optarg);
                break;
            case 'm': 
                strcpy(request.msg, optarg);
                break;
            default:
                fprintf(stderr, "Usage : %s [-h host] [-p port]!\n", argv[0]);
                exit(1);

        }
    }

    argc -= (optind - 1);
    argv += (optind - 1);

    if (argc  > 1) {
        fprintf(stderr, "Usage : %s [-h host] [-p port]!\n", argv[0]);
        exit(1);
    }

    if (!server_port) server_port = atoi(get_value(conf, "SERVERPORT"));
    if (!strlen(server_ip)) strcpy(server_ip, get_value(conf, "SERVERIP"));
    if (!strlen(request.name)) strcpy(request.name, get_value(conf, "NAME"));
    if (!strlen(request.msg)) strcpy(request.msg, get_value(conf, "LOGMSG"));
    if (!request.team) request.team = atoi(get_value(conf, "TEAM"));
    court.width = atoi(get_value(conf, "COLS"));
    court.heigth = atoi(get_value(conf, "LINES"));
    court.start.x = 3;
    court.start.y = 3;

    signal(SIGINT, logout);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr(server_ip);

    socklen_t len = sizeof(server);

    DBG(GREEN"INFO"NONE" : server_ip = %s, server_port = %d, name = %s, team = %s logmsg = %s\n", server_ip, server_port, request.name, (request.team ? "BLUE" : "RED"), request.msg);

    if ((sockfd = socket_udp()) < 0) {
        perror("socket_udp");
        exit(1);
    }

    sendto(sockfd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&server, len);

    fd_set set;
    FD_ZERO(&set);
    FD_SET(sockfd, &set);
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    int retval = select(sockfd + 1, &set, NULL, NULL, &tv);
    if (retval == -1) {
        perror("select");
        exit(1);
    } else if (retval) {
        int ret = recvfrom(sockfd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&server, &len);
        if (ret != sizeof(response) || response.type) {
            DBG(RED"ERROR : "NONE"The Game Server refused your login.\n\tThis May be helpfull: %s\n", response.msg);
            exit(1);
        }
    } else {
        DBG(RED"ERROR : "NONE"The game error\n");
    }


    DBG(GREEN"SERVER : "NONE" %s \n", response.msg);
    connect(sockfd, (struct sockaddr *)&server, len);

#ifndef _D
    pthread_create(&draw_t, NULL, draw, NULL);
#endif
    pthread_create(&recv_t, NULL, client_recv, NULL);

    signal(14, send_ctl);
    struct itimerval itimer;
    itimer.it_interval.tv_sec = 0;
    itimer.it_interval.tv_usec = 100000;
    itimer.it_value.tv_sec = 0;
    itimer.it_value.tv_usec = 100000;

    setitimer(ITIMER_REAL, &itimer, NULL);
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    while (1) {
        int c = getchar();
        switch (c) {
            case 'a':
            case KEY_LEFT: {
                ctl_msg.ctl.dirx -= 1;
            } break;
            case 'd':
            case KEY_RIGHT: {
                ctl_msg.ctl.dirx += 1;
            } break;
            case 'w':
            case KEY_UP: {
                ctl_msg.ctl.diry -= 1;
            } break;
            case 's':
            case KEY_DOWN: {
                ctl_msg.ctl.diry += 1;
            } break;
            case 13: {
                send_chat();
            } break;
            case ' ': {
                show_strength();
            } break;
            case 'j': {
                send_ctl_stop();
            } break;
            case 'k': {
                send_ctl_kick();
            } break;
            case 'l': {
                send_ctl_carry();
            } break;
            default : break;
        }
    }

    sleep(10);

    return 0;
}
