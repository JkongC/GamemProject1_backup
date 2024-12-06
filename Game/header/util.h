#pragma once

int PushToAnimationList(AnimationList** ani_list, Animation* ani);

int RemoveFromAnimationList(AnimationList** ani_list, Animation* ani);

void FreeAnimationList(AnimationList* ani_list);


Node* ToLastNode(Node** head);

Node* CreateNewNode(void* src);

Node* SearchListNode(Node** head, const int ID);

void AddToNodeList(Node** head, Node* new_node);

int RemoveIDFromList(ListWithID* obj_list, const int ID);

int RemoveFromNodeList(Node** head, Node* to_del);

//ʹ�õĻص��������ܶԽ�����ɾ������Ĳ�������û�и�����
int IterateNodeList(Node** head, int (*callback)(Node* obj));

//����ʱ����ȷ�������������õ�
void FreeNodeList(Node** head);

