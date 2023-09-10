#pragma once
//#ifndef _NODE_H
//#define _NODE_H
#include<stdio.h>
typedef struct Content
{
	double number;
	char source[1024];
}Content;
//定义结构
typedef struct Bill
{
	int day;//日期
	Content income;//收入
	Content expence;//花销
	double profit;//利润
	char note[1024];//总结
}Bill,Data;
void bill_printf(Bill* node)
{
	printf("%-8d%-8.2lf%-16s%-8.2lf%-16s%-8.2lf%-16s\n",
		node->day, node->income.number, node->income.source,
		node->expence.number, node->expence.source, node->profit, node->note);
}

//抽象数字类型
//typedef int Data;
//定义节点
typedef struct Node
{
	Data data;	//数据域
	struct Node* next;//指针域
}Node;
//链表结构
typedef struct List
{
	int size;//链表结点个数
	Node* front;//头指针
	Node* tail;//尾指针
}List;
//#endif // !_NODE_H
