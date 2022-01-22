#include "touch-event.h"

void init_lcd()
{
    lcd_draw_bmp24("./000.bmp", 0, 0); //屏幕初始化
    // lcd_draw_bmp24("./w.bmp", 600, 100);  //上
    // lcd_draw_bmp24("./a.bmp", 500, 200);  //左
    // lcd_draw_bmp24("./s.bmp", 600, 200);  //下
    // lcd_draw_bmp24("./d.bmp", 700, 200);  //右

    // 以只读的方式打开触摸屏文件
    fd_touch = open("/dev/input/event0", O_RDONLY);
    if (fd_touch == -1)
    {
        perror("open touch screen error");
        exit(1);
    }
}

char read_key()
{
    struct input_event event;
    int x = -1, y = -1, m = -1, n = -1;
    while (1)
    {
        read(fd_touch, &event, sizeof(event)); // 当触摸屏文件中没有数据时，read会阻塞等待
        //printf("type: %d, code: %d, value: %d \n", event.type, event.code, event.value);
        if (event.type == EV_ABS && event.code == ABS_X)
        {
            if (x == -1)
                x = event.value;
            m = event.value;
        }
        if (event.type == EV_ABS && event.code == ABS_Y)
        {
            if (y == -1)
                y = event.value;
            n = event.value;
        }
        if (event.type == EV_KEY && event.code == BTN_TOUCH && event.value == 0)
            break;
    }

    if (x - m >= 0 && y - n >= 0)
    {
        if (x - m > y - n)
            return 'a';
        else if (x - m < y - n)
            return 'w';
        else
            return 0;
    }

    else if (x - m >= 0 && y - n <= 0)
    {
        if (x - m > n - y)
            return 'a';
        else if (x - m < n - y)
            return 's';
        else
            return 0;
    }

    else if (x - m <= 0 && y - n >= 0)
    {
        if (m - x > y - n)
            return 'd';
        else if (m - x < y - n)
            return 'w';
        else
            return 0;
    }

    else if (x - m <= 0 && y - n <= 0)
    {
        if (m - x > n - y)
            return 'd';
        else if (m - x < n - y)
            return 's';
        else
            return 0;
    }

    else
        return 0;

    // if (y - n > 50 && x - m < 50 && x - m > -50)
    // {
    //     //close(fd);
    //     return 'w';
    // }
    // else if (x - m > 50 && y - n < 50 && y - n > -50)
    // {
    //     //close(fd);
    //     return 'a';
    // }
    // else if (y - n < -50 && x - m < 50 && x - m > -50)
    // {
    //     //close(fd);
    //     return 's';
    // }
    // else if (x - m < -50 && y - n < 50 && y - n > -50)
    // {
    //     //close(fd);
    //     return 'd';
    // }

    //close(fd);
    return 0;
}

void close_touch()
{
    close(fd_touch);
}