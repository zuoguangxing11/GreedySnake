// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//贪吃蛇游戏的主函数入口
#include "pch.h"
#include "GameController.h"
#include <iostream>

#pragma warning(disable:4996)

//这个游戏可以看成几个循环：1.整个游戏就是在一个循环里的，只有退出才会结束
//2.

int main()
{
	GameController gc;
	gc.GameLoop();	//游戏循环开始

	return 0;
}