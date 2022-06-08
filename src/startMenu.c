#pragma once
#include <windows.h>
#include <winuser.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"
// 全局变量
static double winwidth, winheight; // 窗口尺寸

double mouseX,mouseY;

extern double curAngle;
extern int start;

static int chosenMenu = 0;	// 菜单选项，选中了第几个菜单
static int chosenType = 0;
static int chosenDifficulty = 0;

double changeDirection(double, double);

void mainMenu();
void chooseType();
void chooseDifficult();
void gameRules();
void menu3();
void aboutUs();
void display(void);// 用户的显示函数


// 用户的字符事件响应函数
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	//display();		 //刷新显示
}

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI获取键盘
	// display();				// 刷新显示
}

// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	mouseX = x;
	mouseY = y;
	uiGetMouse(x, y, button, event); // GUI获取鼠标
	if(!start)
		display();	 // 刷新显示
}

// 用户的计时器时间响应函数
void TimerEventProcess(int timerID)
{
	double ang = curAngle;	// 保存当前蛇的角度

	if (timerID == 1)
	{
		printf("角度%lf\n", curAngle);
		DisplayClear();
		// 判断是否蛇在下一秒能够拾取到食物
		// judgeFood(ang);
		// 每隔1秒移动一下蛇
		running();
		// drawFood();
	}
}


void display()
{
	// 清屏
	DisplayClear();

	printf("%d\n", chosenMenu);
	switch (chosenMenu)
	{
	case 0:
		mainMenu();
		break;
	case 1:
		switch (chosenType)
		{
		case 0:
			chooseType();
			break;
		default:
			switch (chosenDifficulty)
			{
			case 0:
				chooseDifficult();
				break;
			default:startGame(); break;
			}
		}
	case 2:
		menu3();
		break;
	case 3:
		gameRules();
		break;
	case 4:
		aboutUs();
		break;
	}
}

void Main()
{
	
	// 初始化窗口和图形系统
	SetWindowTitle("双人贪吃蛇");
	SetWindowSize(GetFullScreenWidth(), GetFullScreenHeight());
	InitGraphics();
	InitGUI();
	// 获得窗口尺寸
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	// 注册时间响应函数
	// registerCharEvent(CharEventProcess);		 // 字符
	registerKeyboardEvent(KeyboardEventProcess); // 键盘
	registerMouseEvent(MouseEventProcess);		// 鼠标
	registerTimerEvent(TimerEventProcess);      // 定时器

	mainMenu();
}

void mainMenu()
{
	double fH = GetFontHeight();
	double h = fH * 2;			// 控件高度
	double w = winwidth / 5;	// 控件宽度
	double x = winwidth / 2.5;
	double y = winheight / 6 - h;
	int i = 4;
	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "开始游戏"))
		chosenMenu = 1;

	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "继续游戏"))
		chosenMenu = 2;

	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "游戏规则"))
		chosenMenu = 3;

	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "关于我们"))
		chosenMenu = 4;

	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "退出游戏"))
		exit(0);
}
void chooseType()
{
	double fH = GetFontHeight();
	double h = fH * 2;			 // 控件高度
	double w = winwidth / 5; // 控件宽度
	double x = winwidth / 2.5;
	double y = winheight / 4 - h;
	int i = 2;
	if (button(GenUIID(0), x, y + (winheight / 4 * (i--)), w, h, "单人游戏"))
		chosenType = 1;

	if (button(GenUIID(0), x, y + (winheight / 4 * (i--)), w, h, "双人游戏"))
		chosenType = 2;

	if (button(GenUIID(0), x, y + (winheight / 4 * (i--)), w, h, "返回上一级"))
	{
		chosenMenu = 0;
		chosenType = 0;
	}
}


// 选择难度
void chooseDifficult()
{
	double fH = GetFontHeight();
	double h = fH * 2;			 // 控件高度
	double w = winwidth / 5; // 控件宽度
	double x = winwidth / 2.5;
	double y = winheight / 6 - h;
	int i = 4;
	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "难度一"))
		chosenDifficulty = 1;
	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "难度二"))
		chosenDifficulty = 2;

	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "难度三"))
		chosenDifficulty = 3;
	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "难度四"))
		chosenDifficulty = 4;
	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "返回上一级"))
	{
		chosenDifficulty = 0;
		chosenType = 0;
	}
}
void gameRules()
{
	double fH = GetFontHeight();
	double h = fH * 2;			 // 控件高度
	double w = winwidth / 5; // 控件宽度
	double x = winwidth / 2.5;
	double y = winheight / 6 - h;
	char ch[100]="这是一串测试文本";
	sprintf(ch, "%s\n%s", "这是一串测试文本","这是一串测试文本");
	MovePen(1, 5);
	DrawTextString(ch);
	if (button(GenUIID(0), x, y + (winheight / 6), w, h, "返回上一级"))
		chosenMenu = 0;
}
void menu3()
{
}
void aboutUs()
{
	double fH = GetFontHeight();
	double h = fH * 2;			 // 控件高度
	double w = winwidth / 5; // 控件宽度
	double x = winwidth / 2.5;
	double y = winheight / 6 - h;
	char ch[100] = "这是一串测试文本";
	sprintf(ch, "%s\n%s", "这是一串测试文本", "这是一串测试文本");
	MovePen(1, 5);
	DrawTextString(ch);
	if (button(GenUIID(0), x, y + (winheight / 6), w, h, "返回上一级"))
		chosenMenu = 0;
}