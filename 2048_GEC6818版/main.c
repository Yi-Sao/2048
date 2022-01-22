/*************************************************************************
	> File Name: main.c
	> Author: yisao
	> Mail: 5201314@qq.com 
	> Created Time: 2021年08月03日 星期二 11时41分05秒
 ************************************************************************/

#include "game2048.h"
#include "touch-event.h"


int main(int argc, char const *argv[])
{
	// system("clear"); //清理屏幕
    lcd_init();
	init_lcd();

	int arr[4][4] = {0}, p = 1; //初始化一个空数组,定义一个循环退出条件
	init_array2(arr);			//在空数组中随机生成两个数（2或4）
	char r = 0;
	while (p)
	{
		print2048(arr);
		//print_game(arr); //打印2048游戏数组界面
		r = 0;
		r = read_key();
		execute(arr, r);	 //执行操作（上下左右）
		p = find_2048(arr);	//判断游戏胜利或失败
		if(r != 0)
			init_array1(arr);	 //在数组中值为0的位置随机生成一个数（2或4）
		//p = find_2048(arr);	 //判断游戏是否能够继续运行（胜利退出或失败退出）
		// if (p == 1)			 //如果游戏正常运行
		// 	system("clear"); //清理屏幕
	}
	close_touch();
	close_lcd();
	return 0;
}
