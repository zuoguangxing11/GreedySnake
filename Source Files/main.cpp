// main.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//贪吃蛇游戏的主函数入口
#include "pch.h"
#include "GameController.h"
#include <iostream>

int main()
{
	GameController gc;
	gc.GameLoop();	//游戏循环开始

	return 0;
}