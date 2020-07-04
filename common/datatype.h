/*************************************************************************
	> File Name: datatype.h
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月06日 星期六 20时24分01秒
 ************************************************************************/

#ifndef _DATATYPE_H
#define _DATATYPE_H
#define MAXMSG 1024
struct Point {
    int x, y;
};

struct LogRequest {
    char name[20];
    int team; // red is 0, blue is 1
    char msg[512];
};

struct LogResponse {
    int type; //o success
    char msg[512];
};

struct User {
    int online;
    int team, fd;
    int flag; // 未响应的次数
    char name[20];
    //struct sockaddr_in addr;
    struct Point loc;
};

#define ACTION_KICK 0x01
#define ACTION_CARRY 0x02
#define ACTION_STOP 0x04

struct Ctrl {
    int action;
    int dirx;
    int diry;
    int strength;
};

struct Bpoint {
    double x;
    double y;
};

#define FT_TEST 0x01 //服务端心跳信息
#define FT_WALL 0x02 //服务端以字符串方式广播游戏情况
#define FT_MSG 0x04 //客户端发送的信息，服务端转发的信息
#define FT_ACK 0x08 //客户端对心跳的ACK确认
#define FT_FIN 0x10 //客户端、服务端下线前对彼此的告知
#define FT_CTL 0x20 //客户端发送的控制信息
#define FT_GAME 0x40 //服务端向客户端广播的游戏实时图画 json发送
#define FT_SCORE 0x80 //服务端对客户端广播的游戏比分变化 json发送
#define FT_GAMEOVER 0X100 //游戏结束

struct Map {
    int width, heigth;
    struct Point start;
    int gate_width, gate_heigth;
};

struct FootBallMsg {
    int type; //l, c,, k, s, n, e
    int size;
    int team;
    char name[20];
    char msg[MAXMSG];
    struct Ctrl ctl;
};

struct Aspeed {
    double x;
    double y;
};

struct Speed {
    double x;
    double y;
};

struct BallStatus {
    struct Speed v;
    struct Aspeed a;
    int t;
    int who;
    char name[20];
    //pthread_mutex_t mutex;
};

#endif
