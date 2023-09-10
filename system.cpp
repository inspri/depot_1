#define _CRT_SECURE_NO_WARNINGS 1;
#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"
#include"Graph.h"

#define Title  "����\t����\t��Դ\t\t֧��\tȥ��\t\t����\t�ܽ�\t\t\n"
bool key = false;
List* glist = NULL;

typedef void (*Dosome)(void);
//����ָ������ָ�����ͣ���ָ������ָ��ĺ���û�в���
// Dosome��void ��*����void����ͬ���
//����Dosome���Զ���ָ���ض�������ָ�����
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
		printf("��ǰʱ���ǣ�%s\n", getDateTime());
		printf("��ǰ���˵���%s\n", bill);
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
		default:printf("������1~8������\n"); break;
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
	printf("**********����ϵͳ**********\n");
	printf("*         1-�޸�           *\n");
	printf("*         2-����           *\n");
	printf("*         3-ɾ��           *\n");
	printf("*         4-���           *\n");
	printf("*         5-���ȫ��       *\n");
	printf("*         6-�˵�����       *\n");
	printf("*         7-ͳ���˵�       *\n");
	printf("*         8-����ͼ         *\n");
	printf("*         9-�˳�           *\n");
	printf("****************************\n");
	int num=0;
	printf("������ѡ��Ĳ�����\n");
	scanf("%d", &num);
	return num;
}
void modify()
{
	if (glist->front->next == NULL) {
		printf("���»�δ����˵���\n");
		return;
	}
	int day;
	printf("������Ҫ�޸ĵ��˵����ڣ�\n");
	scanf("%d", &day);
	if (find(glist, day) == NULL) {
		printf("δ�ҵ����˵������������룺\n");
		modify();
	}
	Node* p = find(glist, day);
	printf("�޸�ѡ�\n1.�˵�����  2.����  3.֧��  4.�ܽ�\n");
	int number;
	scanf("%d", &number);
	switch (number)
	{
		case 1: {
			printf("�����޸�Ϊ��\n");
			int num;
			scanf("%d", &num);
			if (find(glist, num)) {
				printf("���˵��Ѵ��ڣ�\n");
				modify();
			}
			p->data.day = num;
			break;
		}
		case 2: {
			printf("�޸�ѡ�1.�˵�����  2.������Դ\n");
			int temp_num = 0;
			scanf("%d", &temp_num);
			if (temp_num == 1) {
				printf("�����޸�Ϊ��\n");
				int num_1;
				scanf("%d", &num_1);
				p->data.income.number = num_1;
				p->data.profit = p->data.income.number - p->data.expence.number;
				break;
			}
			else if (temp_num == 2) {
				printf("������Դ�޸�Ϊ��\n");
				scanf("%s", p->data.income.source);
				break;
			}
			else {
				printf("�������\n");
				modify();
			}
		}
		case 3: {
			printf("�޸�ѡ�1.�˵�����  2.֧��ȥ��\n");
			int temp_num = 0;
			scanf("%d", &temp_num);
			if (temp_num == 1) {
				printf("֧���޸�Ϊ��\n");
				int num_2;
				scanf("%d", &num_2);
				p->data.expence.number = num_2;
				p->data.profit = p->data.income.number - p->data.expence.number;
				break;
			}
			else if (temp_num == 2) {
				printf("֧��ȥ���޸�Ϊ��\n");
				scanf("%s", p->data.expence.source);
				break;
			}
			else {
				printf("�������\n");
				modify();
			}
		}
		case 4: {
			printf("�ܽ��޸�Ϊ��\n");
			scanf("%s", p->data.note);
			break;
		}
		default: {
			printf("��������1~4\n"); modify();
		}
	}
	printf("�޸���ɣ�\n"); printf(Title); bill_printf(&(p->data));
	warning_day(glist,p);
	ifcontinue(modify);
	//save(glist);
}
void search()
{
	if (glist->front->next == NULL) {
		printf("���»�δ����˵���\n");
		return;
	}
	int temp;
	printf("������Ҫ���ҵ��˵����ڣ�\n");
	scanf("%d", &temp);
	Node* p;
	p = find(glist, temp);
	if (p==NULL) {
		printf("δ�ҵ����˵������������룺\n");
		search();
	}
	else {
		printf("�����Ǹ��˵�����Ϣ��\n");
		printf(Title);
		bill_printf(&p->data);
		warning_day(glist,p);
		ifcontinue(search);
	}
}
void delete_system()
{
	if (glist->front->next == NULL) {
		printf("���»�δ����˵���\n");
		return;
	}
	int temp;
	printf("������Ҫɾ�����˵����ڣ�\n");
	scanf("%d", &temp);
	if (find(glist, temp) == NULL) {
		printf("û�и��˵���\n");
		delete_system();
	}
	remove_if(glist, temp);
	if (find(glist, temp) == NULL) {
		printf("ɾ���ɹ���\n");
	}
	//save(glist);
	ifcontinue(delete_system);
}
void add()
{
	if (glist->front->next == NULL) {
		printf("���»�δ����˵���������Ӱɣ�\n");
	}
	//Node* bill=NULL;//����û��
	//��Ȼ���ǲ�������Ϊ�գ�ֱ�ӱ���
	Node bill;
	printf("�������˵����ڣ�\n");
	scanf("%d", &bill.data.day);
	if (find(glist, bill.data.day) != NULL) {
		printf("���˵��Ѵ��ڣ�\n");
		add();
	}
	printf("���������������\n");
	scanf("%lf", &bill.data.income.number);
	printf("������������Դ��\n");
	getchar(); scanf("%s", bill.data.income.source);
	printf("������֧�������\n");
	scanf("%lf", &bill.data.expence.number);
	printf("������֧��ȥ��\n");
	getchar(); scanf("%s", bill.data.expence.source);
	printf("�������ܽ᣺\n");
	getchar(); scanf("%s", bill.data.note);
	bill.data.profit = bill.data.income.number - bill.data.expence.number;
	push_back(glist, bill.data);
	//�����ݴ�������
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
	//���ûص���������
	if (glist ->front->next== NULL) {
		printf("��ʱû���˵���¼\n");
		return;
	}
	printf(Title);
	traversal(glist, bill_printf);
}
char* getDateTime()
{
	static char nowtime[20];
	time_t rawtime;//����ṹ�����
	struct tm* ltime;//����ṹ��ָ�����
	time(&rawtime);
	ltime = localtime(&rawtime);
	strftime(nowtime, 20, "%Y-%m-%d %H:%M:%S", ltime);
	return nowtime;
}
void ifcontinue(Dosome dos)
{
	//save(glist);//���ж��Ƿ��������֮ǰ�������ݣ���ֹ���ݶ�ʧ
	printf("�Ƿ�Ҫ������(Y/N)\n");
	char judge;
	//getchar();//��������������Ļ��з�
	//fflush(stdin);//���������
	scanf(" %c", &judge);     
	if (judge == 'Y' || judge == 'y') {
		dos();
	}
	else if(judge=='N'||judge=='n') {
		return;
	}
	else {
		printf("�������\n");
		ifcontinue(dos);
	}
}
void count()
{
	if (glist->front->next == NULL) {
		printf("������ʱû�����ݣ�\n");
		return;
	}
	sumlist(glist);
}