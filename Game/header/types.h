#pragma once

typedef struct ani {
	int interval; //֡�л�ʱ���������룩
	int counter; //��ʱ������ʾ���ϴ��л�֡��Ŀǰ��ʱ�䣨���룩
	int frame_amounts; //����֡����
	int frame_index; //��ǰ���ŵ�֡����
	int width; //����֡��
	int height; //����֡��
	IMAGEC* atlas; //ͼ��
	POINT atlas_position; //��Ӧͼ���ڸ���ͼ��ͼƬ�е���ʼ�������꣨���Ͻǣ�
	POINT pos; //�����ĵ�ǰ����
} Animation;

typedef struct anilst {
	int capacity; //������
	int size; //�б���Ԫ����
	Animation* list[];
} AnimationList;

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