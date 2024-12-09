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

typedef struct sc {
	ListWithID* Objects;
} Scene;

#define Registry ListWithID
#define AniTemplate Animation
#define ObjTemplate int

#define TRY(x) if (x == -1) return -1;


extern Scene* current_scene;
extern Scene menu;
extern Scene game;
extern Registry Templates_Object;

inline void SetCurrentScene(Scene* next_scene) {
	current_scene = next_scene;
}