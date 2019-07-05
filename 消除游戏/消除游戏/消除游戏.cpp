// 消除游戏.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>

#include <vector>

// 画布
#define WIDTH 1000
#define HEIGHT 700

// 圆
#define R 20
#define CICLE_NUM_ROW 12
#define CICLE_NUM_COLUMN 15
#define UP_EDGE ((HEIGHT / 2) - (CICLE_NUM_COLUMN * R))
#define DOWN_EDGE ((HEIGHT / 2) + (CICLE_NUM_COLUMN * R))
#define LEFT_EDGE ((WIDTH / 2) - (CICLE_NUM_ROW * R))
#define RIGHT_EDGE ((WIDTH / 2) + (CICLE_NUM_ROW * R))

// 按键
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

#define SPACE 32

struct Point{
	int x;
	int y;
};

Point curP;

std::vector<Point> sameBalls;

COLORREF colors[6] = {RGB(255, 0, 0),
					RGB(255, 255, 0),
					RGB(255, 0, 255),
					RGB(0, 255, 0),
					RGB(0, 255, 255),
					RGB(0, 0, 255)};

void init();
void playGrame();
void close();

void drawCursor(Point & p, COLORREF c);
void drawTime(int second);
void drawScores(int score);
void getSameColorBalls(Point & p, COLORREF color);
bool isValid(Point & p, COLORREF color);

int main(){
	init();
	playGrame();
	close();
    return 0;
}

void init(){
	initgraph(WIDTH, HEIGHT);

	// 绘制矩形
	setlinecolor(RGB(50, 50, 50));
	setlinestyle(PS_SOLID, 10);
	rectangle(LEFT_EDGE - 5,
				UP_EDGE - 5,
				RIGHT_EDGE + 5,
				DOWN_EDGE + 5);

	// 绘制圆形
	srand((unsigned int)time(NULL));
	setlinestyle(PS_SOLID);
	for(int x = LEFT_EDGE + 20; x < RIGHT_EDGE; x += (2 * R)){
		for(int y = UP_EDGE + 20; y < DOWN_EDGE; y += (2 * R)){
			COLORREF curColor = colors[rand() % 6];
			setlinecolor(curColor);
			setfillcolor(curColor);
			fillcircle(x, y, R - 2);
		}
	}

	// 绘制光标
	curP.x = WIDTH / 2 - 20;
	curP.y = HEIGHT / 2;
	drawCursor(curP, WHITE);

	// 绘制时间
	drawTime(30);

	// 绘制分数
	drawScores(0);
}

void playGrame(){
	char input;
	while(1){
		input = _getch();
		if(input == SPACE){
			input = _getch();

			sameBalls.clear();
			getSameColorBalls(curP, getpixel(curP.x, curP.y));

			if(sameBalls.size() >= 3){
				for(auto & ball : sameBalls){
					setlinecolor(BLACK);
					setfillcolor(BLACK);
					fillcircle(ball.x, ball.y, R - 2);
				}
			}
		}
		else{
			input = _getch();
			if(input == UP && curP.y > UP_EDGE + 20){
				drawCursor(curP, BLACK);
				curP.y -= 40;
				drawCursor(curP, WHITE);
			}
			else if(input == DOWN && curP.y < DOWN_EDGE - 20){
				drawCursor(curP, BLACK);
				curP.y += 40;
				drawCursor(curP, WHITE);
			}
			else if(input == LEFT && curP.x > LEFT_EDGE + 20){
				drawCursor(curP, BLACK);
				curP.x -= 40;
				drawCursor(curP, WHITE);
			}
			else if(input == RIGHT && curP.x < RIGHT_EDGE - 20){
				drawCursor(curP, BLACK);
				curP.x += 40;
				drawCursor(curP, WHITE);
			}
		}
	}
}

void close(){
	_getch();
	closegraph();
}

void drawCursor(Point & p, COLORREF c){
	setlinecolor(c);
	rectangle(p.x - R, p.y - R, p.x + R, p.y + R);
}

void drawTime(int second){
	settextcolor(RGB(255, 255, 0));
	settextstyle(25, 0, _T("黑体"));

	TCHAR str[30];
	swprintf_s(str, _T("剩余时间：%d s"), second);
	outtextxy(20, 40, str);
}

void drawScores(int score){
	settextcolor(RGB(255, 0, 0));
	settextstyle(22, 0, _T("黑体"));

	TCHAR str[30];
	swprintf_s(str, _T("分数：%d"), score);
	outtextxy(50, 600, str);
}

void getSameColorBalls(Point & p, COLORREF color){
	sameBalls.push_back(p);

	Point tmpP;
	for(int i = 0; i < 4; ++ i){
		switch(i){
		case 0: tmpP.x = p.x; tmpP.y = p.y - 2 * R; break;
		case 1: tmpP.x = p.x; tmpP.y = p.y + 2 * R; break;
		case 2: tmpP.x = p.x - 2 * R; tmpP.y = p.y; break;
		case 3: tmpP.x = p.x + 2 * R; tmpP.y = p.y; break;
		}

		if(isValid(tmpP, color)){
			getSameColorBalls(tmpP, getpixel(tmpP.x, tmpP.y));
		}
	}
}

bool isValid(Point & p, COLORREF color){
	if(p.x < LEFT_EDGE + 20 || p.x > RIGHT_EDGE - 20 || p.y < UP_EDGE + 20 || p.y > DOWN_EDGE - 20){
		return false;
	}

	if(getpixel(p.x, p.y) != color){
		return false;
	}
	else{
		for(auto & ball : sameBalls){
			if(ball.x == p.x && ball.y == p.y){
				return false;
			}
		}
		return true;
	}
}

