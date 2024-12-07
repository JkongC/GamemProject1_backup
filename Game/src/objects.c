#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include "easyxC.h"
#include "types.h"
#include "util.h"
#include "animation.h"
#include "objects.h"

int DistributeID(ListWithID* obj_list) {
	for (int i = 1; i <= 63; i++) {
		if (!((obj_list->table0 >> i) & 1)) {
			obj_list->table0 += (long long)1 << i;
			return i;
		}
	}

	for (int j = 0; j <= 63; j++) {
		if (!((obj_list->table64 >> j) & 1)) {
			obj_list->table64 += (long long)1 << j;
			return j + 64;
		}
	}

	return -1;
}

int RegisterObject(Registry* registry, int type, int life, Animation** ani) {
	int new_ID = DistributeID(registry);
	
	void* new_object;
	Node* new_node;

	switch (type)
	{
	case OBJ_NORMAL:
		new_object = malloc(sizeof(Object));
		if (new_object == NULL) return -1;

		Object* new_obj = (Object*)new_object;
		new_obj->type = OBJ_NORMAL;
		new_obj->life = life;
		new_obj->animation = *ani;
		new_obj->ID = new_ID;
		new_obj->show = false;

		new_node = CreateNewNode(new_object);
		if (new_node == NULL) {
			free(new_object);
			return -1;
		}
		new_node->ID = new_ID;

		NewAnimationFrom(NULL, &new_obj->animation, ani, 0, 0);

		AddToNodeList(&registry->list, new_node);

		break;

	case OBJ_MOVABLE:
		new_object = malloc(sizeof(MovableObject));
		if (new_object == NULL) return -1;

		MovableObject* new_objM = (MovableObject*)new_object;
		new_objM->type = OBJ_MOVABLE;
		new_objM->life = life;
		new_objM->animation = *ani;
		new_objM->ID = new_ID;
		new_objM->show = false;

		new_node = CreateNewNode(new_object);
		if (new_node == NULL) {
			free(new_object);
			return -1;
		}
		new_node->ID = new_ID;

		NewAnimationFrom(NULL, &new_objM->animation, ani, 0, 0);

		AddToNodeList(&registry->list, new_node);

		break;
	}

	return new_ID;
}

void FreeObjects(ListWithID* obj_list) {
	FreeNodeList(&obj_list->list);
}

void FreeObjectRegistry(Registry* registry) {
	IterateNodeList(&registry->list, FreeObjectAnimation);
	FreeObjects(registry);
}

int FreeObjectAnimation(Node* obj) {
	free(((Object*)(obj->object))->animation);
	return 0;
}

void* NewObject(ListWithID* obj_list, Registry* template_list, const int src) {
	Object* src_obj = (Object*)SearchObject(template_list, src);
	if (src_obj == NULL) return NULL;

	int new_ID = DistributeID(obj_list);

	void* new_object;
	Node* new_node;
	POINT origin = { 0, 0 };

	switch (src_obj->type)
	{
	case OBJ_NORMAL:
		new_object = malloc(sizeof(Object));
		if (new_object == NULL) return NULL;

		Object* new_obj = (Object*)new_object;
		
		new_obj->type = OBJ_NORMAL;
		new_obj->life = src_obj->life;
		new_obj->animation = src_obj->animation;
		new_obj->ID = new_ID;
		new_obj->show = true;
		new_obj->pos = origin;

		new_node = CreateNewNode(new_object);
		if (new_node == NULL) return NULL;

		new_node->ID = new_ID;

		AddToNodeList(&obj_list->list, new_node);
		return new_obj;

		break;

	case OBJ_MOVABLE:
		new_object = malloc(sizeof(MovableObject));
		if (new_object == NULL) return NULL;

		MovableObject* new_objM = (MovableObject*)new_object;

		new_objM->type = OBJ_MOVABLE;
		new_objM->life = src_obj->life;
		new_objM->animation = src_obj->animation;
		new_objM->ID = new_ID;
		new_objM->show = true;
		new_objM->pos = origin;
		new_objM->counter = 0;
		new_objM->acceleration = 0;
		new_objM->velocity_X = 0;
		new_objM->velocity_Y = 0;

		new_node = CreateNewNode(new_object);
		if (new_node == NULL) return NULL;

		new_node->ID = new_ID;

		AddToNodeList(&obj_list->list, new_node);
		return new_objM;

		break;
	}

	return NULL;
}

void* SearchObject(ListWithID* obj_list, const int ID) {
	Node* search_res = SearchListNode(&obj_list->list, ID);
	if (search_res == NULL) return NULL;

	return search_res->object;
}

void RemoveObjectByID(ListWithID* obj_list, const int ID) {
	Node* res = SearchListNode(&obj_list->list, ID);
	if (res == NULL) return;

	free(((Object*)(res->object))->animation);
	RemoveFromNodeList(&obj_list->list, res);
}

void RemoveObject(ListWithID* obj_list, void* object) {
	RemoveObjectByID(obj_list, ((Object*)object)->ID);
}

void RenderObject(void* object) {
	Object* obj = (Object*)object;
	obj->animation->pos.x = obj->pos.x;
	obj->animation->pos.y = obj->pos.y;
	RenderAnimation(obj->animation);
}

int RenderObjectFromNode(Node* node) {
	RenderObject(node->object);
	return 0;
}

void UpdateObject(void* object, clock_t delta) {
	Object* obj = (Object*)object;
	UpdateAnimation(obj->animation, delta);
}

int UpdateObjectFromNode(Node* node, clock_t delta) {
	UpdateObject(node->object, delta);
	return 0;
}

void RenderObjectList(ListWithID* obj_list) {
	IterateNodeList(obj_list->list, RenderObjectFromNode);
}

void UpdateObjectList(ListWithID* obj_list, clock_t delta) {
	if (obj_list->list == NULL) return;
	Node* cur = obj_list->list;

	while (cur != NULL) {
		UpdateObjectFromNode(cur, delta);
		cur = cur->next;
	}
}