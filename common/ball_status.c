/*************************************************************************
	> File Name: ball_status.c
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年07月02日 星期四 18时17分28秒
 ************************************************************************/

#include "head.h"

#define WINDOW *Message;
extern struct Bpoint ball;
extern struct BallStatus ball_status;

int can_kick(struct Point *loc, int strength) {
    //palyer and ball 坐标对器
    //判断palyer and 的坐标在上下左右2个单位内，可踢球
    //根据palyer and ball的相对位置，计算球的运动方向，加速度方向，假设求只能在palyer and ball 延长线运动
    //假设player踢球的接触时间为0.2秒，默认加速度为40，力度增加，加速度也增加
    //可踢返回1 else 0
    int px = loc->x - 2, py = loc->y - 1;
    if (abs(px - (int)ball.x) <= 2 && abs(py - (int)ball.y) <= 2) {
        if (abs(px - (int)ball.x) == 0 && abs(py - (int)ball.y) == 0) {
            return 0;
        }
        double dx = (ball.x - px) / pow(pow((ball.x - px), 2) + pow((ball.y - py), 2), 0.5);
        double dy = (ball.y - py) / pow(pow((ball.x - px), 2) + pow((ball.y - py), 2), 0.5);
        ball_status.a.x = -3 * dx;
        ball_status.a.y = -3 * dy;
        ball_status.v.x = strength * 8 * dx;
        ball_status.v.y = strength * 8 * dy;
        return 1;
    }
    return 0;
}
