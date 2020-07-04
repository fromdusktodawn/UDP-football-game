/*************************************************************************
	> File Name: head.h
	> Author: heppyeveryday
	> Mail: w2563546603@gmail.com
	> Created Time: 2020年06月10日 星期三 23时30分25秒
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>
#include <curses.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdbool.h>
#include <pwd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <signal.h>
#include <pthread.h>
#include <poll.h>
#include <sys/select.h>
#include <math.h>
#include <errno.h>
#include "./datatype.h"
#include "./game.h"
#include "./ball_status.h"
#include "./color.h"
#include "./global.h"
#include "./send_chat.h"
#include "./thread_pool.h"
#include "./heart_beat.h"
#include "./thread_pool.h"
#include "./send_ctl.h"
#include "./server_re_draw.h"
#include "./server_exit.h"
#include "./client_recv.h"
#include "./show_data_stream.h"
#include "./show_strength.h"
#include "./sub_reactor.h"
#include "./udp_epoll.h"
#include "./common.h"
#include "./udp_server.h"
#include "./udp_client.h"

#endif
