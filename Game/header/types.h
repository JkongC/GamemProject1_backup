#pragma once

typedef struct node {
	void* object;
	int ID;
	struct node* former;
	struct node* next;
} Node;

//不要手动改里面的数据
typedef struct unqlst {
	unsigned long long table0; //1到63的ID
	unsigned long long table64; //64到127的ID
	Node* list;	//链表
} ListWithID;

#define Registry ListWithID
#define ObjTemplate int