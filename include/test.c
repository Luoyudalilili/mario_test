#include <windows.h>
#include <winuser.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"
#include <math.h>
#include <random.h>
#include <time.h>
int start=0;
double curAngle = 0;

char *colorList[1005] = { NULL };
static int totalColor = 0;
typedef struct Snake* Snake;
extern double mouseX, mouseY;
// void drawHead();
void drawBody(struct Snake* snake);
void drawSnake();
double changeDirection(x, y);
void running(double ang);
void drawSnake();
void startGame();
struct Snake {
	double x;
	double y;
	string color;
	double angle;
	Snake next;
};
Snake snake;
// ʳ�������
typedef struct Food Food;
struct Food {
	double x;
	double y;
};
Food food;
// ���㵱ǰ��ǰ�����򣬷���ֵΪdouble���͵ĽǶ�
double changeDirection()
{
	double curX; double curY;
	curX = ScaleXInches(mouseX) - snake->x;
	curY = GetWindowHeight() - ScaleXInches(mouseY) - snake->y ;
	printf("curX%lf\ncurY%lf\n", curX, curY);
	if (curX == 0 && curY > 0)
		return 3.1415926/2;
	if (curX == 0 && curY == 0)
		return curAngle;

	if (curX == 0 && curY < 0)
		return 3.1415926 / 2;
	if (curX < 0 && curY>0)
	{
		return atan(curY / curX)+3.141592654;
	}
	if (curX < 0 && curY<0)
	{
		return atan(curY / curX) + 3.141592654;
	}
	if (curX > 0 && curY>0)
	{
		return atan(curY / curX);
	}
	if (curX > 0 && curY<0)
	{
		return atan(curY / curX);
	}
}
/*
// ��ʰȡʳ���߼�
void judgeFood(double ang)
{
	Snake p = snake;

	// �����ͷ�˴���Ⱦʱ�������ʳ��ķ�Χ�ڣ����ʱ����β���һ�����ں���ɾ��
	if ((10 * cos(ang) + snake->x)==food.x && (10 * sin(ang) + snake->y) == food.y)
	{
		while (p->next) p = p->next;
		p->next = (Snake)malloc(sizeof(struct Snake));
		p->next->x = p->x;
		p->next->y = p->y;
		p->next->next = NULL;
		randFood();
	}
}

void randFood()
{
	Snake p = snake;
	int x[10000];
	int y[10000];
	int cnt = 0;
	int i, j;
	int curX, curY;
	while (p)
	{
		x[cnt] = p->x;
		y[cnt++] = p->y;
	}
	srand((unsigned int)time(NULL));
	while (cnt)
	{
		curX = rand() % 500;	// �������ʳ���X����
		curY = rand() % 500;	// �������ʳ���Y����
		for (i = 0; i < cnt; i++)
		{
			if (curX == x[i] && curY == y[i])
				break;
		}
		if (i == cnt)
			break;
	}
}
*/
// �������߼�
void running()
{
	//double ang = curAngle;
	// ���µ�ǰ��λ�ò���
	curAngle = changeDirection();
	printf("��ǰ�Ƕ�%lf\n", curAngle);
	Snake p = (Snake)malloc(sizeof(struct Snake));
	p->x = 0.2*cos(curAngle)+snake->x;
	p->y = 0.2*sin(curAngle)+snake->y;

	p->angle = curAngle;
	p->next = snake;
	snake = p;
	while (p->next->next!=NULL)
	{
		p = p->next;
	}
	free(p->next);
	p->next = NULL;
	drawSnake();
}
// ����
void drawSnake()
{
	Snake p = snake;
	//drawHead(p);
	//p = p->next;
	int i = 0;
	while(p)
	{
		drawBody(p);
		p=p->next;
	}
}


// ��Ϸ��ʼ��
void startGame()
{
	char *color=(char*)malloc(sizeof(char)*20);
	double i, j, k;
	Snake p = (Snake)malloc(sizeof(struct Snake));
	InitConsole();
	// ������ɫ�б�
	for (i = 1; i < 7; i++)
	{
		for (j = 1; j < 7; j++)
		{
			for (k = 1; k < 7; k++)
			{
				colorList[totalColor] = (char*)malloc(sizeof(char)*20);
				sprintf(color, "color%03d\0", totalColor);
				sprintf(colorList[totalColor++], "color%03d\0", totalColor);
				printf("%d\n", totalColor);
				DefineColor(color,i*40/256, j*40/256,k*40/256);
				//colorList[totalColor++] = color;
				//printf("color :  %s\n", colorList[totalColor-1]);
			}
		}
	}
	srand((unsigned int)time(NULL));
	// ��ͷ��ʼ����
	p->x = 6;	
	p->y = 6;
	p->angle = 0;
	p->color = colorList[rand()%totalColor];
	p->next = (Snake)malloc(sizeof(struct Snake));
	snake = p;
	p = p->next;
	p->x = 5.8;
	p->y = 6;
	p->angle = 0;
	p->next = (Snake)malloc(sizeof(struct Snake));
	p = p->next;
	p->x = 5.6;
	p->y = 6;
	p->angle = 0;
	p->next = NULL;
	// randFood();	// �������ʳ��
	startTimer(1, 100);	// ��Ӷ�ʱ��
	start = 1;
	//InitConsole();


	while (p)
	{
		drawBody(p);
		p = p->next;
	}
 }

void drawBody(struct Snake* snake)
{
	double r;
	r = 0.15;
	MovePen(snake->x, snake->y);
	SetPenColor(snake->color);
	StartFilledRegion(1);
	DrawArc(r, 0, 360);
	EndFilledRegion();
}
