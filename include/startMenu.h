#pragma once
#include <windows.h>
#include <winuser.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"

// 全局变量
double winwidth, winheight; // 窗口尺寸

static int start = 0;
// 菜单选项，选中了第几个菜单
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
// 用户的显示函数
void display(void);
