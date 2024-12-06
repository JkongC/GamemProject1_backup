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

//使用的回调函数不能对结点进行删除或更改操作，即没有副作用
int IterateNodeList(Node** head, int (*callback)(Node* obj));

//调用时，请确保该链表不会再用到
void FreeNodeList(Node** head);

