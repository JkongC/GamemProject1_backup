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

//使用的回调函数不能对结点本身进行删除操作，也不能更改其former和next指针，ID和object可以谨慎地更改
int IterateNodeList(Node** head, int (*callback)(Node* obj));

//调用时，请确保该链表不会再用到
void FreeNodeList(Node** head);


void ScalingByPixel(IMAGEC* dst, IMAGEC* src, int scale);

