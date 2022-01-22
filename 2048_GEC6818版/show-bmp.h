#ifndef _SHOW_BMP_H
#define _SHOW_BMP_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

// 屏幕文件描述符
static int fd = -1;
// 屏幕文件映射后的内存首地址
static int* addr = NULL;

typedef struct BMP
{
    const char* name;
    int size;
    int width;
    int height;
    short bpp;    // 位深
    char* data;   // 像素数据首地址
}BMP;

void lcd_init();
BMP read_bmp_info(const char* bmpname);
void lcd_draw_bmp24(const char* bmpname, int x, int y);
void lcd_draw_point(int x, int y, int color);

void close_lcd();

#endif
