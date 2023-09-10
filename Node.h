#pragma once
//#ifndef _NODE_H
//#define _NODE_H
#include<stdio.h>
typedef struct Content
{
	double number;
	char source[1024];
}Content;
//����ṹ
typedef struct Bill
{
	int day;//����
	Content income;//����
	Content expence;//����
	double profit;//����
	char note[1024];//�ܽ�
}Bill,Data;
void bill_printf(Bill* node)
{
	printf("%-8d%-8.2lf%-16s%-8.2lf%-16s%-8.2lf%-16s\n",
		node->day, node->income.number, node->income.source,
		node->expence.number, node->expence.source, node->profit, node->note);
}

//������������
//typedef int Data;
//����ڵ�
typedef struct Node
{
	Data data;	//������
	struct Node* next;//ָ����
}Node;
//����ṹ
typedef struct List
{
	int size;//���������
	Node* front;//ͷָ��
	Node* tail;//βָ��
}List;
//#endif // !_NODE_H
