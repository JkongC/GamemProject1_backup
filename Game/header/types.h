#pragma once

typedef struct node {
	void* object;
	int ID;
	struct node* former;
	struct node* next;
} Node;

//��Ҫ�ֶ������������
typedef struct unqlst {
	unsigned long long table0; //1��63��ID
	unsigned long long table64; //64��127��ID
	Node* list;	//����
} ListWithID;

#define Registry ListWithID
#define ObjTemplate int