#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include <stdarg.h>
#include "easyxC.h"
#include "types.h"
#include "animation.h"
#include "objects.h"
#include "util.h"

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

ObjTemplate RegisterObject(Registry* registry, enum Type type, int life, int ani_sets, Animation* ani_1, ...) {
	
	va_list vars;
	va_start(vars, ani_1);
	
	void* new_object;
	Node* new_node;

	//分配内存--------------------------------------------------------------
	switch (type)
	{
	case button:
		new_object = malloc(sizeof(Player));
		break;
	case player:
		new_object = malloc(sizeof(Player));
		break;
	case enemy:
		new_object = malloc(sizeof(Player));
		break;
	case npc:
		new_object = malloc(sizeof(Player));
		break;
	default:
		new_object = malloc(sizeof(Player));
		break;
	}
	//------------------------------------------------------------------------

	if (new_object == NULL) {
		va_end(vars);
		return -1;
	}

	Object* new_obj = (Object*)new_object;
	if (InitializeAnimationList(&new_obj->animation) == -1) {
		free(new_obj);
		va_end(vars);
		return -1;
	}

	new_obj->type = type;
	new_obj->life = life;
	new_obj->show = false;
	new_obj->pos.x = 0;
	new_obj->pos.y = 0;
	new_obj->ani_sets = ani_sets;
	new_obj->ani_counter = 0;
	new_obj->ani_frameidx = 0;
	new_obj->current_ani_set_idx = 0;
	PushToAnimationList(&new_obj->animation, ani_1);

	for (int i = 0; i < ani_sets - 1; i++) {
		Animation* sub_ani = va_arg(vars, Animation*);
		if (sub_ani == NULL) break;
		PushToAnimationList(&new_obj->animation, sub_ani);
	}

	new_node = CreateNewNode(new_object);
	if (new_node == NULL) {
		FreeAnimationList(new_obj->animation);
		free(new_obj);
		va_end(vars);
		return -1;
	}
	int new_ID = DistributeID(registry);
	new_node->ID = new_ID;

	AddToNodeList(&registry->list, new_node);

	//以下是具体类型的处理----------------------------------------------------------------
	switch (type)
	{
	case button:
		break;
	case player:
		Player* sp = (Player*)new_obj;
		sp->acceleration = 0;
		sp->velocity_X = 0;
		sp->velocity_Y = 0;
		sp->time_counter = 0;
		break;
	case enemy:
		break;
	case npc:
		break;
	default:
		break;
	}
	//------------------------------------------------------------------------------------

	va_end(vars);
	return new_ID;
}

void FreeObjects(ListWithID* obj_list) {
	FreeNodeList(&obj_list->list);
}

void FreeObjectRegistry(Registry* registry) {
	FreeObjects(registry);
}

void* NewObject(ObjTemplate obj_template, int origin_x, int origin_y) {
	Object* src_obj = (Object*)SearchObject(Templates_Object, obj_template);
	if (src_obj == NULL) return NULL;

	int new_ID = DistributeID(current_scene->Objects);

	void* new_object;
	Node* new_node;
	POINT origin = { origin_x, origin_y };

	switch (src_obj->type)
	{
	case button:
		new_object = malloc(sizeof(Player));
		break;
	case player:
		new_object = malloc(sizeof(Player));
		break;
	case enemy:
		new_object = malloc(sizeof(Player));
		break;
	case npc:
		new_object = malloc(sizeof(Player));
		break;
	default:
		new_object = malloc(sizeof(Player));
		break;
	}
	if (new_object == NULL) return NULL;


	Object* new_obj = (Object*)new_object;

	new_obj->type = src_obj->type;
	new_obj->life = src_obj->life;
	new_obj->animation = src_obj->animation;
	new_obj->ID = new_ID;
	new_obj->show = true;
	new_obj->pos = origin;
	new_obj->ani_sets = src_obj->ani_sets;
	new_obj->ani_counter = 0;
	new_obj->ani_frameidx = 0;
	new_obj->current_ani_set_idx = 0;

	new_node = CreateNewNode(new_object);
	if (new_node == NULL) {
		free(new_obj);
		return NULL;
	}

	new_node->ID = new_ID;

	AddToNodeList(&current_scene->Objects->list, new_node);
	
	
	switch (new_obj->type)
	{
	case button:
		break;
	case player:
		Player* sp = (Player*)new_obj;
		sp->acceleration = 0;
		sp->velocity_X = 0;
		sp->velocity_Y = 0;
		sp->time_counter = 0;
		break;
	case enemy:
		break;
	case npc:
		break;
	default:
		break;
	}
	
	return new_obj;
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
	switch (obj->type)
	{
	case player:
		Player_render((Player*)obj);
		break;
	default:
		break;
	}
}

int RenderObjectFromNode(Node* node) {
	RenderObject(node->object);
	return 0;
}

void UpdateObject(void* object, clock_t delta) {
	Object* obj = (Object*)object;
	switch (obj->type)
	{
	case player:
		Player_tick((Player*)obj, delta);
		break;
	default:
		break;
	}
}

int UpdateObjectFromNode(Node* node, clock_t delta) {
	UpdateObject(node->object, delta);
	return 0;
}

void RenderAllObjects() {
	IterateNodeList(&current_scene->Objects->list, RenderObjectFromNode);
}

void TickAllObjects(clock_t delta) {
	if (current_scene->Objects->list == NULL) return;
	Node* cur = current_scene->Objects->list;

	while (cur != NULL) {
		UpdateObjectFromNode(cur, delta);
		cur = cur->next;
	}
}

void RemoveAllObjects() {
	FreeObjects(current_scene->Objects);
}




void Player_render(Player* player) {
	Animation* ani_set = player->animation->list[0];

	if (player->ani_counter >= ani_set[player->current_ani_set_idx].interval) {
		player->ani_counter = 0;
		player->ani_frameidx++;
		player->ani_frameidx %= ani_set[player->current_ani_set_idx].frame_amounts;
	}

	RenderAnimation(&ani_set[player->current_ani_set_idx], player->ani_frameidx, player->pos.x, player->pos.y);
}

void Player_tick(Player* player, clock_t delta) {
	player->ani_counter += delta;
}