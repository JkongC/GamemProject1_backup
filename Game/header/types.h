#pragma once

typedef struct ani {
	int interval; //帧切换时间间隔（毫秒）
	int counter; //计时器，表示从上次切换帧到目前的时间（毫秒）
	int frame_amounts; //动画帧总数
	int frame_index; //当前播放的帧索引
	int width; //动画帧宽
	int height; //动画帧高
	IMAGEC* atlas; //图集
	POINT atlas_position; //对应图集在给定图集图片中的起始像素坐标（左上角）
	POINT pos; //动画的当前坐标
} Animation;

typedef struct anilst {
	int capacity; //总容量
	int size; //列表内元素数
	Animation* list[];
} AnimationList;

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