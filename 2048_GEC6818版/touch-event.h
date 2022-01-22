#ifndef _TOUCH_EVENT_H
#define _TOUCH_EVENT_H

#include <fcntl.h>
#include <linux/input.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "show-bmp.h"

static int fd_touch = -1;

void init_lcd();

char read_key();

void close_touch();




#endif