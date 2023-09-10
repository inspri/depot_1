#pragma once	//和ifndef作用一样,防止头文件相互调用的时候重复定义
//但是在该程序里头文件并没有相互调用
//#ifndef _LIST_H_
//#define _LIST_H_
#include<malloc.h>
#include"Node.h"

char filename[1024] = {'\0'};
char year[10];
char month[10];
double budget_month=0, budget_day=0;
double sum_profit = 0, sum_income = 0, sum_expence = 0;

typedef void (*DoSomething)(Data*);
//定义指向函数的指针类型，DoSomething是void （*）（Data*）的同义词
//其中DoSomething可以定义指向函数的指针变量，
//并且指向的函数中的参数为Data类型的指针变量
void traversal(List* list, DoSomething dos);
void destorylist(List* list);
void save(List* list);
char *loadlist(List* list);
List* createlist();
void push_back(List* list, Data val);
void remove_if(List* list, int val);
Node* find(List* list, int day);
void swap(Node* p1, Node* p2);
void sortlist(List* list);
void sumlist(List* list);
//void get_warn_num(List* list);
void warning_system(List* list);
void warning_day(List* list, Node* p);
//void clearlist(List* list);
//有了destorylist,在程序结束时销毁链表就不用clearlist来清除链表了

//void clearlist(List* list)
//{
//	if (list->front->next == NULL) {
//		return;
//	}
//	Node* move = list->front->next;
//	while (move) {
//		Node* temp = move;
//		free(temp);
//		move = move->next;
//	}
//	list->front->next = NULL;
//}
//销毁链表
void destorylist(List* list)
{
	if (list == NULL) {
		return;
	}
	Node* current;
	current = list->front;
	while (current != NULL) {
		Node* next = current->next;
		free(current);
		current = next;
	}
	free(list);
	list = NULL;
}
//保存数据到文件中
void save(List* list)
{
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		printf("warning\n");
		return;
	}
	//extern char Title[1024];
	//fprintf(file, Title);
	fprintf(file, "%.2lf %.2lf\n", budget_month, budget_day);
	Node* move = list->front->next;
	while (move!=NULL) {
		//fwrite(&move->data, sizeof(Data), 1, file) != 1
		//数据打印到文件
		if (fprintf(file, "%-8d%-8.2lf%-16s%-8.2lf%-16s%-8.2lf%-16s\n",
			move->data.day, move->data.income.number,move->data.income.source,
			move->data.expence.number,move->data.expence.source, move->data.profit, move->data.note)==EOF) {
			printf("cannot input to file!\n");
			return;
		}
		move = move->next;
	}
	fclose(file);
}
//从文件中读取数据
char* loadlist(List* list)
{
	printf("请输入账单年份：\n");
	scanf("%s", year);
	printf("请输入账单月份：\n");
	scanf("%s", month);
	strcat(filename, year);
	int count = 0;
	for (int i = 0;; i++) {
		if (filename[i] == '\0' && count == 0) {
			filename[i] = '_';
			strcat(filename, month);
			count++;
		}
		if (count == 1 && filename[i] == '\0') {
			filename[i] = '.';
			filename[i + 1] = 't';
			filename[i + 2] = 'x';
			filename[i + 3] = 't';
			break;
		}
	}
	//clearlist(list);
	//get_warn_num(list);
	Node* fresh = (Node*)malloc(sizeof(Node));
	fresh->next = NULL;
	//Node* move = list->front;
	//fread(&fresh->data, sizeof(Data), 1, file) == 1
	//从文件中读入数据
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		file = fopen(filename, "w+");
	}
	//Node_1* fresh_1 = (Node_1*)malloc(sizeof(Node_1));
	//fresh_1->next = list->tail;
	//fscanf(file, "%lf %lf\n", fresh_1->data_1.budget_month, fresh_1->data_1.budget_day);
	//list->front->next = fresh_1;
	//list->front = fresh_1;//更新头节点
	fscanf(file, "%lf %lf", &budget_month, &budget_day);
	while (fscanf(file, "%d\t%lf\t%s\t%lf\t%s\t%lf\t%s\n",
		&fresh->data.day, &fresh->data.income.number,fresh->data.income.source,
		&fresh->data.expence.number,fresh->data.expence.source,
		&fresh->data.profit, &fresh->data.note)!=EOF) {
		//move->next = fresh;//fresh里的数据赋给头指针后面的了
		//move = fresh;//move向后移动
		push_back(list, fresh->data);
		fresh = (Node*)malloc(sizeof(Node));//重新申请内存用来放新数据
		fresh->next = NULL;
	}
	free(fresh);//最后多定义的fresh要释放掉内存
	fclose(file);
	printf("read success!\n");
	return filename;
}
//创建链表
List* createlist()
{
	//创建链表
	List* list = (List*)calloc(1, sizeof(List));
	if (!list) {
		return NULL;
	}
	//申请头结点
	list->front=list->tail = (Node*)calloc(1, sizeof(Node));
	if (!list->front) {
		return NULL;
	}
	return list;//返回头结点
}

//插入数据
//动态链表，随着数据的增加，链表结点也在改变
void push_back(List* list, Data val)
{
	Node* newNode = (Node*)calloc(1, sizeof(Node));//使指针指向了新的内存空间
	newNode->next = NULL;
	if (!newNode) {
		return;
	}
	newNode->data = val;//把要插入的结点数据赋给了新结点
	//插入
	list->tail->next = newNode;//将新结点放到链表末尾
	list->tail = newNode;//更新新结点为尾结点
	list->size++;//添加数据成功，链表结点个数加一
}
//按条件删除数据
//typedef bool (*CMP)(Data*, Data*);
//定义指向函数的指针类型，其中CMP可以定义指向特定函数
//（函数有两个Data的指针变量，并且返回值为bool类型）的指针变量
//bool judge(Data* a, Data* b)
//{
//	if (a->number == b->number) {
//		return true;
//	}
//	return false;
//}
void remove_if(List*list,int val)
{
	//链表的头指针指向的结点没有存储数据
	Node* temp = list->front->next;
	Node* p = list->front;
	while (temp!=NULL) {
		if (temp->data.day==val) {
			if(temp->next==NULL){
				p->next = NULL;
			}
			else {
				p->next = temp->next;
			}
			list->size--;
			return;
		}
		p = temp;
		temp = temp->next;
	}
}
//遍历链表
void traversal(List* list, DoSomething dos)
{
	Node* curNode = list->front->next;//链表的头指针中没有东西
	while (curNode) {
	dos(&curNode->data);
	curNode = curNode->next;
	}
}
Node* find(List* list, int day)
{
	Node* current = list->front->next;
	while (current != NULL && (current->data.day != day)) {
		current = current->next;
	}
	if (current!=NULL&&(current->data.day == day)) {
		return(current);
	}
	else {
		return NULL;
	}
}
void swap(Node* p1, Node* p2)
{
	Node* p0 = (Node*)malloc(sizeof(Node));
	//这里是p0指向了新申请的空间
	if (p1->data.day > p2->data.day) {
		p0->data = p1->data;
		p1->data = p2->data;
		p2->data = p0->data;
	}
	free(p0);
	p0 = NULL;
}
void sortlist(List* list)
{
	if (list->front->next == NULL) {
		printf("该月还没有添加数据！\n");
		return;
	}
	Node* p = NULL;
	p = list->front->next;
	Node* move = p;
	while (move != NULL && move->next!=NULL) {
		p = list->front->next;
		while (p != NULL && p->next!=NULL) {
				swap(p, p->next);
				p = p->next;
		}
		move = move->next;
	}
	printf("排序成功！\n");
}
void sumlist(List* list)
{
	printf("当前有%d份账单\n", list->size);
	Node* p = list->front->next;
	while (p != NULL) {
		sum_income += p->data.income.number;
		sum_expence += p->data.expence.number;
		p = p->next;
	}
	sum_profit = sum_income - sum_expence;
	printf("截至目前本月\n收入%.2lf\n支出%.2lf\n利润%.2lf\n", sum_income, sum_expence, sum_profit);
}
//void get_warn_num(List* list)
//{
//	double* budget_month, * budget_day;
//	budget_month = &(list->front->data_1.budget_month);
//	budget_day = &(list->front->data_1.budget_day);
//	FILE* p = fopen(filename, "r");
//	if (p == NULL) {
//		p = fopen(filename, "w+");
//	}
//	fscanf(p, "%lf %lf\n", budget_month, budget_day);
//	if (*budget_month == 0 || *budget_day == 0) {
//		if (*budget_month == 0 && *budget_day == 0) {
//			printf("该月账单%s还没有设置预算（月和天）\n", filename);
//			scanf("%lf %lf", budget_month, budget_day);
//		}
//		else if (*budget_month == 0 && *budget_day != 0) {
//			printf("该月账单%s还没有设置月预算\n", filename);
//			scanf("%lf", &budget_month);
//		}
//		else if (*budget_month != 0 && *budget_day == 0) {
//			printf("该月账单%s还没有设置天预算\n", filename);
//			scanf("%lf", budget_day);
//		}
//		fprintf(p, "%.2lf %.2lf\n", *budget_month, *budget_day);
//	}
//	printf("%.2lf %.2lf\n", *budget_month, *budget_day);
//}
void warning_system(List* list)
{
	if (budget_month==0||budget_day==0) {
		if (budget_month == 0 && budget_day != 0) {
			printf("该月账单%s还未添加月预算！\n",filename);
			scanf("%lf", &budget_month);
		}
		if (budget_month != 0 && budget_day == 0) {
			printf("该月账单%s还未添加每天的预算！\n", filename);
			scanf("%lf", &budget_day);
		}
		if (budget_month == 0 && budget_day == 0) {
			printf("该月账单%s还未添加预算（月和天）\n", filename);
			scanf("%lf %lf", &budget_month, &budget_day);
		}
		return;
	}
	Node* p = list->front->next;
	if (p == NULL) {
		return;
	}
	while (p != NULL) {
		if (p->data.expence.number - budget_day > -5) {
			//这里的-5是设置的时候开始提醒
			double a = p->data.expence.number - budget_day;
			if (a >= 0) {
				printf("第%d日超过预算（%.2lf）%.2lf\n",p->data.day, budget_day, a);
			}
			else {
				printf("第%d日还有%.2lf超过预算（%.2lf）\n", p->data.day,-a,budget_day);
			}
		}
		p = p->next;
	}
	if (sum_expence - budget_month > -50) {
		double b = sum_expence - budget_month;
		if (b >= 0) {
			printf("该月超过预算（%.2lf）%.2lf,利润为%.2lf\n", budget_month, b, sum_profit);
		}
		else {
			printf("该月还有%.2lf超过预算（%.2lf）,利润为%.2lf\n",budget_month,-b, sum_profit);
		}
	}
}
void warning_day(List*list,Node*p)
{
	if (p == NULL) {
		return;
	}
	if (p->data.expence.number - budget_day > -5) {
		//这里的-5是设置的时候开始提醒
		double a = p->data.expence.number - budget_day;
		if (a >= 0) {
			printf("该日超过预算（%.2lf）%.2lf\n", budget_day, a);
		}
		else {
			printf("该日还有%.2lf超过预算（%.2lf）\n",-a, budget_day);
		}
	}
}
//#endif // !_LIST_H_
