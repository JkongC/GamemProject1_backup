#include <Windows.h>
#include <tchar.h>
#include "easyxC.h"
#include "types.h"
#include "animation.h"
#include "util.h"

int InitializeAnimationList(AnimationList** ani_list) {
	*ani_list = (AnimationList*)malloc(sizeof(AnimationList) + 10 * sizeof(Animation*));
	if (*ani_list == NULL) return -1;
	
	(*ani_list)->capacity = 10;
	(*ani_list)->size = 0;
	return 0;
}

int PushToAnimationList(AnimationList** ani_list, Animation* ani) {
	AnimationList* a_list = *ani_list;
	if (a_list->size == a_list->capacity) {
		AnimationList* new_list = (AnimationList*)realloc(a_list, sizeof(AnimationList) + (a_list->capacity + 5) * sizeof(Animation*));
		if (new_list == NULL) return -1;

		*ani_list = new_list;
		(*ani_list)->capacity += 5;
	}

	(*ani_list)->list[(*ani_list)->size] = ani;
	(*ani_list)->size++;

	return 0;
}

int RemoveFromAnimationList(AnimationList** ani_list, Animation* ani) {
	AnimationList* a_list = *ani_list;
	int found = 0;
	for (int i = 0; i < a_list->size; i++) {
		if (a_list->list[i] == ani) {
			a_list->list[i] = a_list->list[a_list->size - 1];
			a_list->size--;

			free(ani);
			found = 1;
			break;
		}
	}

	if (!found) return -1;
	return 0;
}

void FreeAnimationList(AnimationList* ani_list) {
	for (int i = 0; i < ani_list->size; i++) {
		free(ani_list->list[i]);
	}
	free(ani_list);
}

int InitializeListWithID(ListWithID** empty_list) {
	*empty_list = (ListWithID*)malloc(sizeof(ListWithID));
	if (*empty_list == NULL) return -1;
	
	memset(*empty_list, 0, sizeof(ListWithID));
	return 0;
}

int InitializeScene(Scene* scene) {
	if ((InitializeListWithID(&scene->Objects)) == -1) return -1;
	return 0;
}

Node* ToLastNode(Node** head) {
	if (*head == NULL) return NULL;
	Node* cur = *head;

	while (cur->next != NULL) {
		cur = cur->next;
	}

	return cur;
}

Node* CreateNewNode(void* src) {
	Node* new_node = malloc(sizeof(Node));
	if (new_node == NULL) return NULL;

	new_node->object = src;
	new_node->former = NULL;
	new_node->next = NULL;
	return new_node;
}

Node* SearchListNode(Node** head, const int ID) {
	if (*head == NULL) return NULL;
	Node* cur = *head;

	while (cur->ID != ID) {
		if (cur->next == NULL) return NULL;
		cur = cur->next;
	}

	return cur;
}

void AddToNodeList(Node** head, Node* new_node) {
	Node* last = ToLastNode(head);

	if (last == NULL) {
		*head = new_node;
	}
	else {
		last->next = new_node;
		new_node->former = last;
	}
}

int RemoveIDFromList(ListWithID* obj_list, const int ID) {
	if (obj_list->list == NULL) return -2;

	Node* cur = obj_list->list;
	while (cur->next != NULL && cur->ID != ID) {
		cur = cur->next;
	}

	if (cur->ID == ID) {
		Node* aft = cur->next;
		Node* bef = cur->former;

		if (aft != NULL) aft->former = bef;
		if (bef != NULL) bef->next = aft;

		free(cur);
		return 0;
	}

	return -2;
}

int RemoveFromNodeList(Node** head, Node* to_del) {
	if (*head == NULL) return -2;

	Node* cur = *head;
	while (cur->next != NULL && cur != to_del) {
		cur = cur->next;
	}

	if (cur == to_del) {
		Node* aft = cur->next;
		Node* bef = cur->former;

		if (aft != NULL) aft->former = bef;
		if (bef != NULL) bef->next = aft;

		if (cur == *head) *head = NULL;
		free(to_del);
		return 0;
	}
	
	return -2;
}

//使用的回调函数不能对结点进行删除或更改操作，只能对object进行操作
int IterateNodeList(Node** head, int (*callback)(Node* obj)) {
	if (*head == NULL) return -1;
	Node* cur = *head;

	while (cur != NULL) {
		if (callback(cur) == -2) return -2;
		cur = cur->next;
	}

	return 0;
}

//调用时，请确保该链表不会再用到
void FreeNodeList(Node** head) {
	if (*head == NULL) return;
	Node* cur = *head;
	Node* next_node;

	while (cur != NULL) {
		next_node = cur->next;
		free(cur);
		cur = next_node;
	}

	*head = NULL;
}

//请确保dst已经使用newimageC函数按照正确的缩放大小创建好，否则可能导致访问越界
void ScalingByPixel(IMAGEC* dst, IMAGEC* src, int scale) {
	DWORD* dst_buffer = GetImageBufferC(dst);
	DWORD* src_buffer = GetImageBufferC(src);

	int src_w = imagec_getwidth(src);
	int src_h = imagec_getheight(src);
	int dst_w = imagec_getwidth(dst);

	for (int i = 0; i < src_h; i++) {
		for (int j = 0; j < src_w; j++) {
			int dst_x = j * scale;
			int dst_y = i * scale;

			for (int sub_X = 0; sub_X < scale; sub_X++) {
				for (int sub_Y = 0; sub_Y < scale; sub_Y++) {
					dst_buffer[dst_x + (dst_y + sub_Y) * dst_w + sub_X] = src_buffer[j + i * src_w];
				}
			}
		}
	}
}