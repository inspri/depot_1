#pragma once
#include"Node.h"
#include<easyx.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
void graph(List* list)
{
	if (list->front->next == NULL) {
		printf("该月暂时没有数据！\n");
		return;
	}
	else if (list->front->next->next == NULL) {
		printf("该月只有一个数据不能画图\n");
		return;
	}
	initgraph(640, 480);//物理坐标不能改变
	//setbkcolor(WHITE);
	//cleardevice();
	TCHAR temp[4] = _T("100");
	int temp_x = textwidth(temp); int temp_y = textheight(temp);
	setorigin(temp_x, 480- temp_y);//逻辑坐标原点改变
	//setaspectratio(1, -1);
	//setlinecolor(BLACK);
	line(0, temp_y, 0, temp_y-480);//y轴
	line(-temp_x, 0, 640-temp_x, 0);//x轴
	//每个点之间的x坐标相差20
	TCHAR s[3] = { '\0' };
	TCHAR str_1[] = _T("收入");
	TCHAR str_2[] = _T("支出");
	TCHAR str_3[] = _T("利润");
	int x = 0; 
	Node* move = list->front->next;
	while (move->next!=NULL) {
		_stprintf(s, _T("%d"), move->data.day);
		setlinecolor(LIGHTRED);
		line(x, -(int)(move->data.income.number), x + 20, -(int)(move->next->data.income.number));
		//outtextxy(x - 5, -(int)(move->data.income.number) + 15, s);
		setlinecolor(LIGHTBLUE);
		line(x, -(int)(move->data.expence.number), x + 20, -(int)(move->next->data.expence.number));
		//outtextxy(x - 5, -(int)(move->data.expence.number) + 15, s);
		setlinecolor(LIGHTGREEN);
		line(x, -(int)(move->data.profit), x + 20, -(int)(move->next->data.profit));
		//outtextxy(x - 5, -(int)(move->data.profit) + 15, s);
		settextcolor(WHITE);
		outtextxy(x - 5, 1, s);
		x += 20;
		move = move->next;
	}
	_stprintf(s, _T("%d"), move->data.day);
	//outtextxy(x - 5, -(int)(move->data.income.number) + 15, s);
	//outtextxy(x - 5, -(int)(move->data.expence.number) + 15, s);
	//outtextxy(x - 5, -(int)(move->data.profit) + 15, s);
	outtextxy(x - 5, temp_y, s);
	settextcolor(LIGHTRED);
	outtextxy(640-temp_x - textwidth(str_1), temp_y-450 + textheight(str_1), str_1);
	settextcolor(LIGHTBLUE);
	outtextxy(640 - temp_x - textwidth(str_2), temp_y-420 + textheight(str_2), str_2);
	settextcolor(LIGHTGREEN);
	outtextxy(640 - temp_x - textwidth(str_3), temp_y-390 + textheight(str_3), str_3);
	TCHAR y[4] = {'\0'};
	int num = -30;
	while (num <= 480-textheight(temp)) {
		_stprintf(y, _T("%d"), -num);
		settextcolor(WHITE);
		outtextxy(-textwidth(temp), num, y);
		num += -30;
	}
	while (!_kbhit()) {
		Sleep(10);
	}
	closegraph();
}