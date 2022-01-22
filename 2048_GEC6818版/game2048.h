/*************************************************************************
	> File Name: game2048.h
	> Author: yisao
	> Mail: 5201314@qq.com 
	> Created Time: 2021年08月03日 星期二 15时58分52秒
 ************************************************************************/

#ifndef _GAME2048_H_
#define _GAME2048_H_

#include "game2048.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

/**
 * @brief 生成一个由两个随机数组成的数组
 * 
 * @param tmp 随机数数组
 */
void random_number(int tmp[]);

/**
 * @brief 在二维数组的随机位置生成两个随机的2或4
 * 
 * @param arr 一个二维数组
 */
void init_array2(int arr[4][4]);

/**
 * @brief 在二维数组的随机位置生成一个随机的2或4
 * 
 * @param arr 一个二维数组
 */
void init_array1(int arr[4][4]);

/**
 * @brief 对游戏进行可执行的操作
 * 
 * @param arr 一个二维数组
 */
void execute(int arr[4][4], char r);

/**
 * @brief 打印游戏数组
 * 
 * @param arr 一个二维数组
 */
void print_game(int arr[4][4]);

/**
 * @brief 判断游戏是否能够继续运行（胜利退出或失败退出）
 * 
 * @param arr 一个二维数组
 * @return true 游戏继续运行
 * @return false 游戏退出（胜利或失败）
 */
bool find_2048(int arr[4][4]);



void print2048(int arr[4][4]);

#endif
