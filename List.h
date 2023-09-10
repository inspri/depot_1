#pragma once	//��ifndef����һ��,��ֹͷ�ļ��໥���õ�ʱ���ظ�����
//�����ڸó�����ͷ�ļ���û���໥����
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
//����ָ������ָ�����ͣ�DoSomething��void ��*����Data*����ͬ���
//����DoSomething���Զ���ָ������ָ�������
//����ָ��ĺ����еĲ���ΪData���͵�ָ�����
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
//����destorylist,�ڳ������ʱ��������Ͳ���clearlist�����������

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
//��������
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
//�������ݵ��ļ���
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
		//���ݴ�ӡ���ļ�
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
//���ļ��ж�ȡ����
char* loadlist(List* list)
{
	printf("�������˵���ݣ�\n");
	scanf("%s", year);
	printf("�������˵��·ݣ�\n");
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
	//���ļ��ж�������
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		file = fopen(filename, "w+");
	}
	//Node_1* fresh_1 = (Node_1*)malloc(sizeof(Node_1));
	//fresh_1->next = list->tail;
	//fscanf(file, "%lf %lf\n", fresh_1->data_1.budget_month, fresh_1->data_1.budget_day);
	//list->front->next = fresh_1;
	//list->front = fresh_1;//����ͷ�ڵ�
	fscanf(file, "%lf %lf", &budget_month, &budget_day);
	while (fscanf(file, "%d\t%lf\t%s\t%lf\t%s\t%lf\t%s\n",
		&fresh->data.day, &fresh->data.income.number,fresh->data.income.source,
		&fresh->data.expence.number,fresh->data.expence.source,
		&fresh->data.profit, &fresh->data.note)!=EOF) {
		//move->next = fresh;//fresh������ݸ���ͷָ��������
		//move = fresh;//move����ƶ�
		push_back(list, fresh->data);
		fresh = (Node*)malloc(sizeof(Node));//���������ڴ�������������
		fresh->next = NULL;
	}
	free(fresh);//���ඨ���freshҪ�ͷŵ��ڴ�
	fclose(file);
	printf("read success!\n");
	return filename;
}
//��������
List* createlist()
{
	//��������
	List* list = (List*)calloc(1, sizeof(List));
	if (!list) {
		return NULL;
	}
	//����ͷ���
	list->front=list->tail = (Node*)calloc(1, sizeof(Node));
	if (!list->front) {
		return NULL;
	}
	return list;//����ͷ���
}

//��������
//��̬�����������ݵ����ӣ�������Ҳ�ڸı�
void push_back(List* list, Data val)
{
	Node* newNode = (Node*)calloc(1, sizeof(Node));//ʹָ��ָ�����µ��ڴ�ռ�
	newNode->next = NULL;
	if (!newNode) {
		return;
	}
	newNode->data = val;//��Ҫ����Ľ�����ݸ������½��
	//����
	list->tail->next = newNode;//���½��ŵ�����ĩβ
	list->tail = newNode;//�����½��Ϊβ���
	list->size++;//������ݳɹ��������������һ
}
//������ɾ������
//typedef bool (*CMP)(Data*, Data*);
//����ָ������ָ�����ͣ�����CMP���Զ���ָ���ض�����
//������������Data��ָ����������ҷ���ֵΪbool���ͣ���ָ�����
//bool judge(Data* a, Data* b)
//{
//	if (a->number == b->number) {
//		return true;
//	}
//	return false;
//}
void remove_if(List*list,int val)
{
	//�����ͷָ��ָ��Ľ��û�д洢����
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
//��������
void traversal(List* list, DoSomething dos)
{
	Node* curNode = list->front->next;//�����ͷָ����û�ж���
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
	//������p0ָ����������Ŀռ�
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
		printf("���»�û��������ݣ�\n");
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
	printf("����ɹ���\n");
}
void sumlist(List* list)
{
	printf("��ǰ��%d���˵�\n", list->size);
	Node* p = list->front->next;
	while (p != NULL) {
		sum_income += p->data.income.number;
		sum_expence += p->data.expence.number;
		p = p->next;
	}
	sum_profit = sum_income - sum_expence;
	printf("����Ŀǰ����\n����%.2lf\n֧��%.2lf\n����%.2lf\n", sum_income, sum_expence, sum_profit);
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
//			printf("�����˵�%s��û������Ԥ�㣨�º��죩\n", filename);
//			scanf("%lf %lf", budget_month, budget_day);
//		}
//		else if (*budget_month == 0 && *budget_day != 0) {
//			printf("�����˵�%s��û��������Ԥ��\n", filename);
//			scanf("%lf", &budget_month);
//		}
//		else if (*budget_month != 0 && *budget_day == 0) {
//			printf("�����˵�%s��û��������Ԥ��\n", filename);
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
			printf("�����˵�%s��δ�����Ԥ�㣡\n",filename);
			scanf("%lf", &budget_month);
		}
		if (budget_month != 0 && budget_day == 0) {
			printf("�����˵�%s��δ���ÿ���Ԥ�㣡\n", filename);
			scanf("%lf", &budget_day);
		}
		if (budget_month == 0 && budget_day == 0) {
			printf("�����˵�%s��δ���Ԥ�㣨�º��죩\n", filename);
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
			//�����-5�����õ�ʱ��ʼ����
			double a = p->data.expence.number - budget_day;
			if (a >= 0) {
				printf("��%d�ճ���Ԥ�㣨%.2lf��%.2lf\n",p->data.day, budget_day, a);
			}
			else {
				printf("��%d�ջ���%.2lf����Ԥ�㣨%.2lf��\n", p->data.day,-a,budget_day);
			}
		}
		p = p->next;
	}
	if (sum_expence - budget_month > -50) {
		double b = sum_expence - budget_month;
		if (b >= 0) {
			printf("���³���Ԥ�㣨%.2lf��%.2lf,����Ϊ%.2lf\n", budget_month, b, sum_profit);
		}
		else {
			printf("���»���%.2lf����Ԥ�㣨%.2lf��,����Ϊ%.2lf\n",budget_month,-b, sum_profit);
		}
	}
}
void warning_day(List*list,Node*p)
{
	if (p == NULL) {
		return;
	}
	if (p->data.expence.number - budget_day > -5) {
		//�����-5�����õ�ʱ��ʼ����
		double a = p->data.expence.number - budget_day;
		if (a >= 0) {
			printf("���ճ���Ԥ�㣨%.2lf��%.2lf\n", budget_day, a);
		}
		else {
			printf("���ջ���%.2lf����Ԥ�㣨%.2lf��\n",-a, budget_day);
		}
	}
}
//#endif // !_LIST_H_
