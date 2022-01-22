/*************************************************************************
	> File Name: game2048.c
	> Author: yisao
	> Mail: 5201314@qq.com 
	> Created Time: 2021年08月03日 星期二 13时32分51秒
 ************************************************************************/

#include "game2048.h"
#include "show-bmp.h"


void random_number(int tmp[]) //产生一个由两个随机数组成的数组
{
	tmp[0] = (rand() % 2 + 1) * 2; //随机生成2或4
	tmp[1] = rand() % 16;		   //随机生成数组下标
}

void init_array2(int arr[4][4]) //在二维数组的随机位置生成一个随机的2或4
{
	int tmp[2] = {0};			 //初始化一个数组用以存放随机数
	int i = 2;					 //使循环进行两次准确的赋值
	srand((unsigned)time(NULL)); //播种
	while (i)
	{
		random_number(tmp); //生成随机数

		if (arr[(tmp[1]) / 4][tmp[1] % 4] == 0) //判断是否可以插入随机数
		{
			arr[(tmp[1]) / 4][tmp[1] % 4] = tmp[0];
			i--;
		}
	}
}

void init_array1(int arr[4][4]) //在二维数组的随机位置生成一个随机的2或4
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (arr[i][j] == 0)
			{
				int tmp[2] = {0};			 //初始化一个数组用以存放随机数
				srand((unsigned)time(NULL)); //播种
				while (1)
				{
					random_number(tmp); //生成随机数

					if (arr[(tmp[1]) / 4][tmp[1] % 4] == 0) //判断是否可以插入随机数
					{
						arr[(tmp[1]) / 4][tmp[1] % 4] = tmp[0];
						return;
					}
				}
			}
			else if (i == 3 && j == 3 && arr[i][j] != 0)
				return;
}

void execute(int arr[4][4], char r) //对游戏进行可执行的操作(上下左右)
{
	// char r;
	// while (r != 'a' && r != 's' && r != 'd' && r != 'w') //输入不为w、a、s、d时需重新输入
	// {
	// 	if (r != 'a' && r != 's' && r != 'd' && r != 'w' && r != '\0') //输入不为w、a、s、d时进行提醒
	// 		printf("错误输入，请重新输入(如果还是出错，请按一次回车再输入)：");
	// 	else
	// 		printf("\n~~a为左移，d为右移，w为上移，s为下移~~\n"); //操作提示

	// 	scanf("%c", &r); //获取输入的字符
	// 	getchar();		 //获取回车键的值
	// }

	switch (r) //进行游戏操作
	{
	case 'w': //输入a时向左移动
	{
		int m, n = 1; //临时工具
		for (int i = 0; i < 4; i++)
		{
			m = 0;
			for (int j = 0; j < 4; j++)
				if (arr[i][j] != 0)
				{
					if (m != 0 && arr[i][j] == n) //数值相等时进行相加合并
					{
						arr[i][m - 1] += arr[i][j];
						arr[i][j] = 0;
						n = 1;
					}
					else
					{
						n = arr[i][j];
						arr[i][j] = 0;
						arr[i][m] = n;
						m++;
					}
				}
		}
		break;
	}

	case 'd': //输入s时向下移动
	{
		int m, n; //临时工具
		for (int j = 0; j < 4; j++)
		{
			m = 3;
			for (int i = 3; i >= 0; i--)
				if (arr[i][j] != 0)
				{
					if (m != 3 && arr[i][j] == n) //数值相等时进行相加合并
					{
						arr[m + 1][j] += arr[i][j];
						arr[i][j] = 0;
						n = 1;
					}
					else
					{
						n = arr[i][j];
						arr[i][j] = 0;
						arr[m][j] = n;
						m--;
					}
				}
		}
		break;
	}

	case 's': //输入d时向右移动
	{
		int m, n; //临时工具
		for (int i = 0; i < 4; i++)
		{
			m = 3;
			for (int j = 3; j >= 0; j--)
				if (arr[i][j] != 0)
				{
					if (m != 3 && arr[i][j] == n) //数值相等时进行相加合并
					{
						n = 1;
						arr[i][m + 1] += arr[i][j];
						arr[i][j] = 0;
					}
					else
					{
						n = arr[i][j];
						arr[i][j] = 0;
						arr[i][m] = n;
						m--;
					}
				}
		}
		break;
	}

	case 'a': //输入w时向上移动
	{
		int m, n; //临时工具
		for (int j = 0; j < 4; j++)
		{
			m = 0;
			for (int i = 0; i < 4; i++)
				if (arr[i][j] != 0)
				{
					if (m != 0 && arr[i][j] == n) //数值相等时进行相加合并
					{
						arr[m - 1][j] += arr[i][j];
						arr[i][j] = 0;
						n = 1;
					}
					else
					{
						n = arr[i][j];
						arr[i][j] = 0;
						arr[m][j] = n;
						m++;
					}
				}
		}
		break;
	}
	
	default:
		break;
	}
}

void print_game(int arr[4][4]) //打印游戏数组
{
	printf("*********************************\n");
	for (int i = 0; i < 4; i++) //使游戏界面更美观
	{
		printf("|");
		for (int j = 0; j < 4; j++)
			if (arr[i][j] != 0)
				printf("%4d   |", arr[i][j]);
			else
				printf("       |");
		printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	}
}

bool find_2048(int arr[4][4]) //判断游戏是否能够继续运行（胜利退出或失败退出）
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			//如果游戏运行至产生一个2048，则以胜利退出
			if (arr[i][j] == 2048)
			{
				lcd_draw_bmp24("./end.bmp", 280, 180);
				system("clear");
				print_game(arr);
				printf("you are win !!!\n");
				return false;
			}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)

			//只要游戏有一个0，游戏可继续运行条件
			if (arr[i][j] == 0)
				return true;

			//如果游戏运行至没有一个0，则判断是否还有邻居相等
			else if (i == 3 && j == 3 && arr[i][j] != 0)
			{
				for (int m = 0; m < 4; m++)
					for (int n = 0; n < 3; n++)
						if (arr[m][n] == arr[m][n + 1])
							return true;
						else if (arr[n][m] == arr[n + 1][m])
							return true;

				//以上条件均未满足，则以失败退出
				lcd_draw_bmp24("./end.bmp", 280, 180);
				system("clear");
				print_game(arr);
				printf("you are lost !!!\n");
				printf("~~输入任意键退出~~\n");
				getchar();
				return false;
			}
	}
}

void print2048(int arr[4][4])
{

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			switch (arr[i][j])
			{
			case 0:
				lcd_draw_bmp24("./0.bmp", i * 100, j * 100);	//	调位置
				break;
			case 2:
				lcd_draw_bmp24("./2.bmp", i * 100, j * 100);
				break;
			case 4:
				lcd_draw_bmp24("./4.bmp", i * 100, j * 100);
				break;
			case 8:
				lcd_draw_bmp24("./8.bmp", i * 100, j * 100);
				break;
			case 16:
				lcd_draw_bmp24("./16.bmp", i * 100, j * 100);
				break;
			case 32:
				lcd_draw_bmp24("./32.bmp", i * 100, j * 100);
				break;
			case 64:
				lcd_draw_bmp24("./64.bmp", i * 100, j * 100);
				break;
			case 128:
				lcd_draw_bmp24("./128.bmp", i * 100, j * 100);
				break;
			case 256:
				lcd_draw_bmp24("./256.bmp", i * 100, j * 100);
				break;
			case 512:
				lcd_draw_bmp24("./512.bmp", i * 100, j * 100);
				break;
			case 1024:
				lcd_draw_bmp24("./1024.bmp", i * 100, j * 100);
				break;
			case 2048:
				lcd_draw_bmp24("./2048.bmp", i * 100, j * 100);
				break;

			default:
				break;
			}
		}
}