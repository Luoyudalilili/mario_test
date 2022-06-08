#pragma once
#include <windows.h>
#include <winuser.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"
// ȫ�ֱ���
static double winwidth, winheight; // ���ڳߴ�

double mouseX,mouseY;

extern double curAngle;
extern int start;

static int chosenMenu = 0;	// �˵�ѡ�ѡ���˵ڼ����˵�
static int chosenType = 0;
static int chosenDifficulty = 0;

double changeDirection(double, double);

void mainMenu();
void chooseType();
void chooseDifficult();
void gameRules();
void menu3();
void aboutUs();
void display(void);// �û�����ʾ����


// �û����ַ��¼���Ӧ����
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	//display();		 //ˢ����ʾ
}

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); // GUI��ȡ����
	// display();				// ˢ����ʾ
}

// �û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event)
{
	mouseX = x;
	mouseY = y;
	uiGetMouse(x, y, button, event); // GUI��ȡ���
	if(!start)
		display();	 // ˢ����ʾ
}

// �û��ļ�ʱ��ʱ����Ӧ����
void TimerEventProcess(int timerID)
{
	double ang = curAngle;	// ���浱ǰ�ߵĽǶ�

	if (timerID == 1)
	{
		printf("�Ƕ�%lf\n", curAngle);
		DisplayClear();
		// �ж��Ƿ�������һ���ܹ�ʰȡ��ʳ��
		// judgeFood(ang);
		// ÿ��1���ƶ�һ����
		running();
		// drawFood();
	}
}


void display()
{
	// ����
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
	
	// ��ʼ�����ں�ͼ��ϵͳ
	SetWindowTitle("˫��̰����");
	SetWindowSize(GetFullScreenWidth(), GetFullScreenHeight());
	InitGraphics();
	InitGUI();
	// ��ô��ڳߴ�
	winwidth = GetWindowWidth();
	winheight = GetWindowHeight();

	// ע��ʱ����Ӧ����
	// registerCharEvent(CharEventProcess);		 // �ַ�
	registerKeyboardEvent(KeyboardEventProcess); // ����
	registerMouseEvent(MouseEventProcess);		// ���
	registerTimerEvent(TimerEventProcess);      // ��ʱ��

	mainMenu();
}

void mainMenu()
{
	double fH = GetFontHeight();
	double h = fH * 2;			// �ؼ��߶�
	double w = winwidth / 5;	// �ؼ����
	double x = winwidth / 2.5;
	double y = winheight / 6 - h;
	int i = 4;
	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "��ʼ��Ϸ"))
		chosenMenu = 1;

	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "������Ϸ"))
		chosenMenu = 2;

	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "��Ϸ����"))
		chosenMenu = 3;

	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "��������"))
		chosenMenu = 4;

	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "�˳���Ϸ"))
		exit(0);
}
void chooseType()
{
	double fH = GetFontHeight();
	double h = fH * 2;			 // �ؼ��߶�
	double w = winwidth / 5; // �ؼ����
	double x = winwidth / 2.5;
	double y = winheight / 4 - h;
	int i = 2;
	if (button(GenUIID(0), x, y + (winheight / 4 * (i--)), w, h, "������Ϸ"))
		chosenType = 1;

	if (button(GenUIID(0), x, y + (winheight / 4 * (i--)), w, h, "˫����Ϸ"))
		chosenType = 2;

	if (button(GenUIID(0), x, y + (winheight / 4 * (i--)), w, h, "������һ��"))
	{
		chosenMenu = 0;
		chosenType = 0;
	}
}


// ѡ���Ѷ�
void chooseDifficult()
{
	double fH = GetFontHeight();
	double h = fH * 2;			 // �ؼ��߶�
	double w = winwidth / 5; // �ؼ����
	double x = winwidth / 2.5;
	double y = winheight / 6 - h;
	int i = 4;
	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "�Ѷ�һ"))
		chosenDifficulty = 1;
	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "�Ѷȶ�"))
		chosenDifficulty = 2;

	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "�Ѷ���"))
		chosenDifficulty = 3;
	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "�Ѷ���"))
		chosenDifficulty = 4;
	if (button(GenUIID(0), x, y + (winheight / 6 * (i--)), w, h, "������һ��"))
	{
		chosenDifficulty = 0;
		chosenType = 0;
	}
}
void gameRules()
{
	double fH = GetFontHeight();
	double h = fH * 2;			 // �ؼ��߶�
	double w = winwidth / 5; // �ؼ����
	double x = winwidth / 2.5;
	double y = winheight / 6 - h;
	char ch[100]="����һ�������ı�";
	sprintf(ch, "%s\n%s", "����һ�������ı�","����һ�������ı�");
	MovePen(1, 5);
	DrawTextString(ch);
	if (button(GenUIID(0), x, y + (winheight / 6), w, h, "������һ��"))
		chosenMenu = 0;
}
void menu3()
{
}
void aboutUs()
{
	double fH = GetFontHeight();
	double h = fH * 2;			 // �ؼ��߶�
	double w = winwidth / 5; // �ؼ����
	double x = winwidth / 2.5;
	double y = winheight / 6 - h;
	char ch[100] = "����һ�������ı�";
	sprintf(ch, "%s\n%s", "����һ�������ı�", "����һ�������ı�");
	MovePen(1, 5);
	DrawTextString(ch);
	if (button(GenUIID(0), x, y + (winheight / 6), w, h, "������һ��"))
		chosenMenu = 0;
}