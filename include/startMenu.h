#pragma once
#include <windows.h>
#include <winuser.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"

// ȫ�ֱ���
double winwidth, winheight; // ���ڳߴ�

static int start = 0;
// �˵�ѡ�ѡ���˵ڼ����˵�
static int chosenMenu = 0;
static int chosenType = 0;
static int chosenDifficulty = 0;

void mainMenu();
void chooseType();
void chooseDifficult();
void gameRules();
void menu3();
void aboutUs();
void menu5();
void menu6();
// �û�����ʾ����
void display(void);
