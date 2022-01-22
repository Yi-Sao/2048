#include"show-bmp.h"

// int main(int argc, char const* argv[])
// {
//     if (argc != 13)
//     {
//         fprintf(stderr, "Usage %s <bmp-name> \n", argv[0]);
//         exit(1);
//     }
//     lcd_init();
//     lcd_draw_bmp24(argv[1], 0, 0);
//     lcd_draw_bmp24(argv[1], 300, 0);

//     return 0;
// }


BMP read_bmp_info(const char* bmpname)
{
    BMP bmp;
    bmp.name = bmpname;
    // 打开BMP文件
    int fd_bmp = open(bmp.name, O_RDONLY);
    if (fd_bmp == -1)
    {
        perror("open error");
        exit(1);
    }
    // 读数据，如大小、宽、高、位深...
    char bm[2] = { 0 };
    read(fd_bmp, bm, 2);
    if (!(bm[0] == 'B' && bm[1] == 'M'))
    {
        printf("%s is not a bmp file!\n", bmp.name);
        exit(1);
    }
    // 2, 12, 16 ,1c
    // 读BMP文件的大小，包括头部和像素数据的大小
    lseek(fd_bmp, 0x2, SEEK_SET);
    read(fd_bmp, &bmp.size, 4);
    // 读宽和高
    lseek(fd_bmp, 0x12, SEEK_SET);
    read(fd_bmp, &bmp.width, 4);
    read(fd_bmp, &bmp.height, 4);
    // 读色深
    lseek(fd_bmp, 0x1c, SEEK_SET);
    read(fd_bmp, &bmp.bpp, 2);

    bmp.data = malloc(bmp.size - 54);
    lseek(fd_bmp, 0x36, SEEK_SET);
    read(fd_bmp, bmp.data, bmp.size - 54);
    // 关闭文件
    close(fd_bmp);

    return bmp;
}

void lcd_draw_bmp24(const char* bmpname, int x, int y)
{
    // 读取位图的基本信息
    BMP bmp = read_bmp_info(bmpname);
    //printf("size: %d \n w: %d \n h: %d \n bpp: %d \n", bmp.size, bmp.width, bmp.height, bmp.bpp);

    // 计算一行的字节数
    int line_bytes = bmp.width * bmp.bpp / 8;
    // 计算每一行的填充字节数
    int pad_bytes = (line_bytes % 4 == 0) ? 0 : (4 - line_bytes % 4);

    // 显示到lcd屏幕上
    char r, g, b;
    char* p = bmp.data;
    int color;
    for (int i = bmp.height - 1; i >= 0; i--)
    {
        for (int j = 0; j < bmp.width; j++)
        {
            b = *p++;
            g = *p++;
            r = *p++;
            color = r << 16 | g << 8 | b;
            lcd_draw_point(j+x, i+y, color);
        }
        p += pad_bytes;
    }
    free(bmp.data);
}




// 屏幕初始化
void lcd_init()
{
    // 打开屏幕
    fd = open("/dev/fb0", O_RDWR);
    if (fd == -1)
    {
        perror("open lcd error");
        exit(1);
    }
    // 把屏幕映射到内存
    addr = mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
    {
        perror("mmap error");
        exit(1);
    }
}
// 画点
void lcd_draw_point(int x, int y, int color)
{
    if (x >= 0 && x < 800 && y >= 0 && y < 480)
        *(addr + 800 * y + x) = color;
}



void close_lcd()
{
    close(fd);
    munmap(addr,800*480*4);
    addr = NULL;
}