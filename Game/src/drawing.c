#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include "easyxC.h"
#include "types.h"
#include "drawing.h"
#include "util.h"

int CreateAnimationTemplate(AnimationList** templates, Animation** new_ani, int interval, int frame_amounts, int rc_head_index) {
	Animation* new_p = (Animation*)malloc(sizeof(Animation) + frame_amounts * sizeof(IMAGEC*));
	if (new_p == NULL) return -1;

	*new_ani = new_p;
	(*new_ani)->interval = interval;
	(*new_ani)->frame_amounts = frame_amounts;
	(*new_ani)->rc_head_index = rc_head_index;
	(*new_ani)->counter = 0;
	(*new_ani)->frame_index = 0;
	(*new_ani)->pos.x = 0;
	(*new_ani)->pos.y = 0;

	for (int i = 0; i < frame_amounts; i++) {
		loadimageCR(&(*new_ani)->frames[i], _T("PNG"), (*new_ani)->rc_head_index + i);
	}

	if (PushToList(templates, *new_ani) == -1) {
		return -1;
	}

	return 0;
}

int NewAnimationFrom(AnimationList** ani_list, Animation** dst, Animation** src, long newX, long newY) {
	*dst = (Animation*)malloc(sizeof(Animation) + (*src)->frame_amounts * sizeof(IMAGEC*));
	if (*dst == NULL) return -1;
	**dst = **src;

	for (int i = 0; i < (*src)->frame_amounts; i++) {
		(*dst)->frames[i] = (*src)->frames[i];
	}

	(*dst)->pos.x = newX;
	(*dst)->pos.y = newY;
	(*dst)->counter = 0;

	PushToList(ani_list, *dst);

	return 0;
}

int RemoveAnimation(AnimationList** ani_list, Animation* todel) {
	return RemoveFromList(ani_list, todel);
}

void Render(Animation* animation) {
	if (animation->counter >= animation->interval) {
		animation->counter = 0;
		animation->frame_index++;
		animation->frame_index %= animation->frame_amounts;

		putimageC(animation->pos.x, animation->pos.y, animation->frames[animation->frame_index]);
	}
}

void RenderList(AnimationList* ani_list) {
	for (int i = 0; i < ani_list->size; i++) {
		Animation* cur = ani_list->list[i];
		Render(cur);
	}
}

void UpdateList(AnimationList* ani_list, clock_t delta) {
	for (int i = 0; i < ani_list->size; i++) {
		Animation* cur = ani_list->list[i];
		cur->counter += delta;
	}
}