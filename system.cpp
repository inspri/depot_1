#define _CRT_SECURE_NO_WARNINGS 1;
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"
#include"Graph.h"

#define Title  "日期\t收入\t来源\t\t支出\t去向\t\t利润\t总结\t\t\n"
bool key = false;
List* glist = NULL;

typedef void (*Dosome)(void);
//定义指向函数的指针类型，该指针类型指向的函数没有参数
// Dosome是void （*）（void）的同义词
//其中Dosome可以定义指向特定函数的指针变量
void modify();
void search();
void delete_system();
void add();
void put_all();
char* getDateTime();
void ifcontinue(Dosome dos);
void count();
int menu();

int main()
{
	char bill[1024];
	glist = createlist();
	strcpy(bill, loadlist(glist));
	while (!key) {
		printf("当前时间是：%s\n", getDateTime());
		printf("当前在账单：%s\n", bill);
		warning_system(glist);
		switch (menu()) {
		case 1:modify(); break;
		case 2:search(); break;
		case 3:delete_system(); break;
		case 4:add(); break;
		case 5:put_all(); break;
		case 6:sortlist(glist); break;
		case 7:count(); break;
		case 8:graph(glist); break;
		case 9:key = true; system("pause"); exit(0);
		default:printf("请输入1~8的数字\n"); break;
		}
		//stu_printf(&glist->front->data);
		//stu_printf(&glist->tail->data);
		save(glist);
		system("pause");
		system("cls");
	}
	destorylist(glist);
	return 0;
}
int menu()
{
	printf("**********管理系统**********\n");
	printf("*         1-修改           *\n");
	printf("*         2-查找           *\n");
	printf("*         3-删除           *\n");
	printf("*         4-添加           *\n");
	printf("*         5-输出全部       *\n");
	printf("*         6-账单排序       *\n");
	printf("*         7-统计账单       *\n");
	printf("*         8-折线图         *\n");
	printf("*         9-退出           *\n");
	printf("****************************\n");
	int num=0;
	printf("请输入选择的操作：\n");
	scanf("%d", &num);
	return num;
}
void modify()
{
	if (glist->front->next == NULL) {
		printf("该月还未添加账单！\n");
		return;
	}
	int day;
	printf("请输入要修改的账单日期：\n");
	scanf("%d", &day);
	if (find(glist, day) == NULL) {
		printf("未找到该账单，请重新输入：\n");
		modify();
	}
	Node* p = find(glist, day);
	printf("修改选项：\n1.账单日期  2.收入  3.支出  4.总结\n");
	int number;
	scanf("%d", &number);
	switch (number)
	{
		case 1: {
			printf("日期修改为：\n");
			int num;
			scanf("%d", &num);
			if (find(glist, num)) {
				printf("该账单已存在！\n");
				modify();
			}
			p->data.day = num;
			break;
		}
		case 2: {
			printf("修改选项：1.账单数据  2.收入来源\n");
			int temp_num = 0;
			scanf("%d", &temp_num);
			if (temp_num == 1) {
				printf("收入修改为：\n");
				int num_1;
				scanf("%d", &num_1);
				p->data.income.number = num_1;
				p->data.profit = p->data.income.number - p->data.expence.number;
				break;
			}
			else if (temp_num == 2) {
				printf("收入来源修改为：\n");
				scanf("%s", p->data.income.source);
				break;
			}
			else {
				printf("输入错误\n");
				modify();
			}
		}
		case 3: {
			printf("修改选项：1.账单数据  2.支出去向\n");
			int temp_num = 0;
			scanf("%d", &temp_num);
			if (temp_num == 1) {
				printf("支出修改为：\n");
				int num_2;
				scanf("%d", &num_2);
				p->data.expence.number = num_2;
				p->data.profit = p->data.income.number - p->data.expence.number;
				break;
			}
			else if (temp_num == 2) {
				printf("支出去向修改为：\n");
				scanf("%s", p->data.expence.source);
				break;
			}
			else {
				printf("输入错误\n");
				modify();
			}
		}
		case 4: {
			printf("总结修改为：\n");
			scanf("%s", p->data.note);
			break;
		}
		default: {
			printf("输入数字1~4\n"); modify();
		}
	}
	printf("修改完成！\n"); printf(Title); bill_printf(&(p->data));
	warning_day(glist,p);
	ifcontinue(modify);
	//save(glist);
}
void search()
{
	if (glist->front->next == NULL) {
		printf("该月还未添加账单！\n");
		return;
	}
	int temp;
	printf("请输入要查找的账单日期：\n");
	scanf("%d", &temp);
	Node* p;
	p = find(glist, temp);
	if (p==NULL) {
		printf("未找到该账单，请重新输入：\n");
		search();
	}
	else {
		printf("以下是该账单的信息：\n");
		printf(Title);
		bill_printf(&p->data);
		warning_day(glist,p);
		ifcontinue(search);
	}
}
void delete_system()
{
	if (glist->front->next == NULL) {
		printf("该月还未添加账单！\n");
		return;
	}
	int temp;
	printf("请输入要删除的账单日期：\n");
	scanf("%d", &temp);
	if (find(glist, temp) == NULL) {
		printf("没有该账单！\n");
		delete_system();
	}
	remove_if(glist, temp);
	if (find(glist, temp) == NULL) {
		printf("删除成功！\n");
	}
	//save(glist);
	ifcontinue(delete_system);
}
void add()
{
	if (glist->front->next == NULL) {
		printf("该月还未添加账单，快来添加吧！\n");
	}
	//Node* bill=NULL;//心里没底
	//果然还是不能设置为空，直接报错
	Node bill;
	printf("请输入账单日期：\n");
	scanf("%d", &bill.data.day);
	if (find(glist, bill.data.day) != NULL) {
		printf("该账单已存在！\n");
		add();
	}
	printf("请输入收入情况：\n");
	scanf("%lf", &bill.data.income.number);
	printf("请输入收入来源：\n");
	getchar(); scanf("%s", bill.data.income.source);
	printf("请输入支出情况：\n");
	scanf("%lf", &bill.data.expence.number);
	printf("请输入支出去向：\n");
	getchar(); scanf("%s", bill.data.expence.source);
	printf("请输入总结：\n");
	getchar(); scanf("%s", bill.data.note);
	bill.data.profit = bill.data.income.number - bill.data.expence.number;
	push_back(glist, bill.data);
	//把数据储存起来
	//save(glist);
	//if (find(glist, &bill->data) == NULL) {
	//	printf("push fail\n");
	//}
	printf(Title);
	bill_printf(&(bill.data));
	warning_day(glist, &bill);
	ifcontinue(add);
}
void put_all()
{
	//运用回调函数处理
	if (glist ->front->next== NULL) {
		printf("暂时没有账单记录\n");
		return;
	}
	printf(Title);
	traversal(glist, bill_printf);
}
char* getDateTime()
{
	static char nowtime[20];
	time_t rawtime;//定义结构体变量
	struct tm* ltime;//定义结构体指针变量
	time(&rawtime);
	ltime = localtime(&rawtime);
	strftime(nowtime, 20, "%Y-%m-%d %H:%M:%S", ltime);
	return nowtime;
}
void ifcontinue(Dosome dos)
{
	//save(glist);//在判断是否继续输入之前保存数据，防止数据丢失
	printf("是否要继续？(Y/N)\n");
	char judge;
	//getchar();//清除缓冲区里多余的换行符
	//fflush(stdin);//清除缓冲区
	scanf(" %c", &judge);     
	if (judge == 'Y' || judge == 'y') {
		dos();
	}
	else if(judge=='N'||judge=='n') {
		return;
	}
	else {
		printf("输入错误！\n");
		ifcontinue(dos);
	}
}
void count()
{
	if (glist->front->next == NULL) {
		printf("该月暂时没有数据！\n");
		return;
	}
	sumlist(glist);
}