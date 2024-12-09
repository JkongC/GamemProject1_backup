#pragma once

int InitializeAnimationList(AnimationList** ani_list);

int PushToAnimationList(AnimationList** ani_list, Animation* ani);

int RemoveFromAnimationList(AnimationList** ani_list, Animation* ani);

void FreeAnimationList(AnimationList* ani_list);

void InitializeListWithID(ListWithID* empty_list);


int InitializeScene(Scene* scene);


Node* ToLastNode(Node** head);

Node* CreateNewNode(void* src);

Node* SearchListNode(Node** head, const int ID);

void AddToNodeList(Node** head, Node* new_node);

int RemoveIDFromList(ListWithID* obj_list, const int ID);

int RemoveFromNodeList(Node** head, Node* to_del);

//ʹ�õĻص��������ܶԽ�㱾�����ɾ��������Ҳ���ܸ�����former��nextָ�룬ID��object���Խ����ظ���
int IterateNodeList(Node** head, int (*callback)(Node* obj));

//����ʱ����ȷ�������������õ�
void FreeNodeList(Node** head);


void ScalingByPixel(IMAGEC* dst, IMAGEC* src, int scale);

