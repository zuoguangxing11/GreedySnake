#include "pch.h"
#include "GameController.h"
#include "Map.h"
#include "Snake.h"
#include "Food.h"

#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>

GameController::GameController():
	_Speed(100)
	,_Key(1)
	,_Score(0)
{
}

GameController::~GameController()
{

}

void GameController::GameLoop()
{
	Start();

	while (true)
	{
		SelectDifficulty();

		DrawGame();

		int temp = PlayGame();//开启游戏循环，当重新开始或退出游戏时，结束循环并返回值给tmp

		if (temp == 1)    //返回值为1时重新开始游戏
		{
			system("cls");
			continue;
		}
		else if (temp == 2)    //返回值为2时退出游戏
		{
			break;
		}
		else
		{
			break;
		}
	}
}

void GameController::Start()
{
	Tools::Instance()->SetWindowSize(41, 32);
	Tools::Instance()->SetColor(2);

	StartInterface* start = new StartInterface();
	start->AnimationAction();	//播放动画
	delete start;	//释放内存

	//设置光标位置,输出提示语,等待任意键输入结束
	Tools::Instance()->SetCurSorPositon(13, 26);
	std::cout << "====================";
	Tools::Instance()->SetCurSorPositon(13, 27);
	system("pause");
}

void GameController::SelectDifficulty()
{
	//难度信息
	Tools::Instance()->SetColor(3);
	Tools::Instance()->SetCurSorPositon(13, 26);
	std::cout << "                          ";
	Tools::Instance()->SetCurSorPositon(13, 27);
	std::cout << "                          ";
	Tools::Instance()->SetCurSorPositon(6, 21);
	std::cout << "请选择游戏难度：";
	Tools::Instance()->SetCurSorPositon(6, 22);
	std::cout << "(上下键选择,回车确认)";
	Tools::Instance()->SetCurSorPositon(27, 22);
	Tools::Instance()->SetCurBackgroundColor();//第一个选项设置背景色以表示当前选中
	std::cout << "简单模式";
	Tools::Instance()->SetCurSorPositon(27, 24);
	Tools::Instance()->SetColor(3);
	std::cout << "普通模式";
	Tools::Instance()->SetCurSorPositon(27, 26);
	std::cout << "困难模式";
	Tools::Instance()->SetCurSorPositon(27, 28);
	std::cout << "炼狱模式";
	Tools::Instance()->SetCurSorPositon(0, 31);

	_Score = 0;
	int ch ;	//记录键入值
	_Key = 1;	//记录选中项，初始选择第一个
	bool flag = false;//记录是否键入Enter键标记，初始置为否
	while (ch = _getch())
	{
		switch (ch)
		{
			case 72:
				if (_Key > 1)//当此时选中项为第一项时，UP上方向键无效
				{
					switch (_Key)
					{
					case 2:
						Tools::Instance()->SetCurSorPositon(27, 22);//给待选中项设置背景色
						Tools::Instance()->SetCurBackgroundColor();
						std::cout << "简单模式";

						Tools::Instance()->SetCurSorPositon(27, 24);//将已选中项取消背景色
						Tools::Instance()->SetColor(3);
						std::cout << "普通模式";

						--_Key;
						break;
					case 3:
						Tools::Instance()->SetCurSorPositon(27, 24);
						Tools::Instance()->SetCurBackgroundColor();
						std::cout << "普通模式";

						Tools::Instance()->SetCurSorPositon(27, 26);
						Tools::Instance()->SetColor(3);
						std::cout << "困难模式";

						--_Key;
						break;
					case 4:
						Tools::Instance()->SetCurSorPositon(27, 26);
						Tools::Instance()->SetCurBackgroundColor();
						std::cout << "困难模式";

						Tools::Instance()->SetCurSorPositon(27, 28);
						Tools::Instance()->SetColor(3);
						std::cout << "炼狱模式";

						--_Key;
						break;
					}
				}
				break;

			case 80:
				if(_Key < 4)
				{
					switch (_Key)
					{
						case 1:
							Tools::Instance()->SetCurSorPositon(27, 24);
							Tools::Instance()->SetCurBackgroundColor();
							std::cout << "普通模式";
							Tools::Instance()->SetCurSorPositon(27, 22);
							Tools::Instance()->SetColor(3);
							std::cout << "简单模式";

							++_Key;
							break;
						case 2:
							Tools::Instance()->SetCurSorPositon(27, 26);
							Tools::Instance()->SetCurBackgroundColor();
							std::cout << "困难模式";
							Tools::Instance()->SetCurSorPositon(27, 24);
							Tools::Instance()->SetColor(3);
							std::cout << "普通模式";

							++_Key;
							break;
						case 3:
							Tools::Instance()->SetCurSorPositon(27, 28);
							Tools::Instance()->SetCurBackgroundColor();
							std::cout << "炼狱模式";
							Tools::Instance()->SetCurSorPositon(27, 26);
							Tools::Instance()->SetColor(3);
							std::cout << "困难模式";

							++_Key;
							break;
					}
				}
				break;

			case 13:    //回车
				flag = true;
				break;
			default:	//无效按键
				break;
		}

		if (flag)
		{
			break;
		}

		Tools::Instance()->SetCurSorPositon(0, 31);    //设置光标到左下角
	}

	switch (_Key)//根据所选选项设置蛇的移动速度，speed值越大，速度越快
	{
	case 1:
		_Speed = 135;
		break;
	case 2:
		_Speed = 100;
		break;
	case 3:
		_Speed = 60;
		break;
	case 4:
		_Speed = 30;
		break;
	default:
		break;
	}
}

void GameController::DrawGame()
{
	system("cls");    //清屏

	Tools::Instance()->SetColor(3);

	//绘制初始地图
	Map* initMap = new Map();
	initMap->PrintInitMap();   
	delete initMap;

	//绘制侧边栏
	Tools::Instance()->SetCurSorPositon(33, 1);
	std::cout << "Greedy Snake...";

	Tools::Instance()->SetCurSorPositon(34, 2);
	std::cout << "贪吃蛇";

	Tools::Instance()->SetCurSorPositon(31, 4);
	std::cout << "难度";

	Tools::Instance()->SetCurSorPositon(36, 5);
	switch (_Key)
	{
	case 1:
		std::cout << "简单模式";
		break;
	case 2:
		std::cout << "普通模式";
		break;
	case 3:
		std::cout << "困难模式";
		break;
	case 4:
		std::cout << "炼狱模式";
	default:
		break;
	}

	Tools::Instance()->SetCurSorPositon(31, 7);
	std::cout << "得分：";

	Tools::Instance()->SetCurSorPositon(37, 8);
	std::cout << "     0";

	Tools::Instance()->SetCurSorPositon(33, 13);
	std::cout << " 方向键移动";

	Tools::Instance()->SetCurSorPositon(33, 15);
	std::cout << " ESC键暂停";
}

int GameController::PlayGame()
{
	//初始化蛇和食物
	Snake* snake = new Snake();
	Food* food = new Food();

	Tools::Instance()->SetColor(6);
	snake->InitSnake();
	srand((unsigned)time(NULL));    //设置随机数,设置食物出生的位置
	food->DrawFood(*snake);

	//todo:游戏循环 2019.06.03 by zjz

	while (snake->OverEdge() && snake->HitSelf())
	{
		if (!snake->ChangeDirection())
		{
			int temp = CreateMenu();
			switch (temp)
			{
			case 1://继续游戏
				break;

			case 2://重新开始
				delete snake;
				delete food;
				return 1;//将1作为PlayGame函数的返回值返回到Game函数中，表示重新开始

			case 3://退出游戏
				delete snake;
				delete food;
				return 2;//将2作为PlayGame函数的返回值返回到Game函数中，表示退出游戏

			default:
				break;
			}
		}

		//如果吃到食物
		if (snake->GetFood(*food))
		{
			snake->Move();
			UpdateScore(1);
			RedrawUIScore();
			food->DrawFood(*snake);
		}
		else
		{
			snake->InitMove();
		}

		Sleep(_Speed);//制造蛇的移动效果

		//加入限时食物
	}

	return 0;
}

int GameController::CreateMenu()
{
	/*绘制菜单*/
	Tools::Instance()->SetColor(11);
	Tools::Instance()->SetCurSorPositon(32, 19);
	std::cout << "菜单：";
	Sleep(100);
	Tools::Instance()->SetCurSorPositon(34, 21);
	Tools::Instance()->SetCurBackgroundColor();
	std::cout << "继续游戏";
	Sleep(100);
	Tools::Instance()->SetCurSorPositon(34, 23);
	Tools::Instance()->SetColor(11);
	std::cout << "重新开始";
	Sleep(100);
	Tools::Instance()->SetCurSorPositon(34, 25);
	std::cout << "退出游戏";
	Tools::Instance()->SetCurSorPositon(0, 31);

	/*选择部分*/
	int ch;
	int tmp_key = 1;
	bool flag = false;
	while (ch = _getch())
	{
		switch (ch)
		{
		case 72://UP
			if (tmp_key > 1)
			{
				switch (tmp_key)
				{
				case 2:
					Tools::Instance()->SetCurSorPositon(34, 21);
					Tools::Instance()->SetCurBackgroundColor();
					std::cout << "继续游戏";
					Tools::Instance()->SetCurSorPositon(34, 23);
					Tools::Instance()->SetColor(11);
					std::cout << "重新开始";

					--tmp_key;
					break;
				case 3:
					Tools::Instance()->SetCurSorPositon(34, 23);
					Tools::Instance()->SetCurBackgroundColor();
					std::cout << "重新开始";
					Tools::Instance()->SetCurSorPositon(34, 25);
					Tools::Instance()->SetColor(11);
					std::cout << "退出游戏";

					--tmp_key;
					break;
				}
			}
			break;

		case 80://DOWN
			if (tmp_key < 3)
			{
				switch (tmp_key)
				{
				case 1:
					Tools::Instance()->SetCurSorPositon(34, 23);
					Tools::Instance()->SetCurBackgroundColor();
					std::cout << "重新开始";
					Tools::Instance()->SetCurSorPositon(34, 21);
					Tools::Instance()->SetColor(11);
					std::cout << "继续游戏";

					++tmp_key;
					break;
				case 2:
					Tools::Instance()->SetCurSorPositon(34, 25);
					Tools::Instance()->SetCurBackgroundColor();
					std::cout << "退出游戏";
					Tools::Instance()->SetCurSorPositon(34, 23);
					Tools::Instance()->SetColor(11);
					std::cout << "重新开始";

					++tmp_key;
					break;
				}
			}
			break;

		case 13://Enter
			flag = true;
			break;

		default:
			break;
		}

		if (flag)
		{
			break;
		}
		Tools::Instance()->SetCurSorPositon(0, 31);
	}

	if (tmp_key == 1) //选择继续游戏，则将菜单擦除
	{
		Tools::Instance()->SetCurSorPositon(32, 19);
		std::cout << "      ";
		Tools::Instance()->SetCurSorPositon(34, 21);
		std::cout << "        ";
		Tools::Instance()->SetCurSorPositon(34, 23);
		std::cout << "        ";
		Tools::Instance()->SetCurSorPositon(34, 25);
		std::cout << "        ";
	}
	return tmp_key;
}

void GameController::UpdateScore(const int& score)
{
	_Score += _Key * 10 * score;
}

void GameController::RedrawUIScore()
{
	Tools::Instance()->SetCurSorPositon(37, 8);
	Tools::Instance()->SetColor(11);
	int bit = 0;
	int temp = _Score;
	while (temp != 0)
	{
		bit++;
		temp /= 10;
	}

	for (int i = 0; i < (6 - bit); i++)
	{
		std::cout << " ";
	}
	std::cout << _Score;
}
