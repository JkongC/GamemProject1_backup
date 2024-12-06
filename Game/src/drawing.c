#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include "easyxC.h"
#include "types.h"
#include "drawing.h"
#include "util.h"

int CreateAnimationTemplate(AnimationList** templates, Animation** new_ani, int interval, int frame_amounts, POINT atlas_position, IMAGEC* atlas, int width, int height) {
	Animation* new_p = (Animation*)malloc(sizeof(Animation) + sizeof(IMAGEC*));
	if (new_p == NULL) return -1;

	*new_ani = new_p;
	(*new_ani)->interval = interval;
	(*new_ani)->counter = 0;
	(*new_ani)->frame_amounts = frame_amounts;
	(*new_ani)->frame_index = 0;
	(*new_ani)->width = width;
	(*new_ani)->height = height;
	(*new_ani)->atlas = atlas;
	(*new_ani)->atlas_position = atlas_position;
	(*new_ani)->pos.x = 0;
	(*new_ani)->pos.y = 0;

	if (PushToAnimationList(templates, *new_ani) == -1) {
		return -1;
	}

	return 0;
}

int NewAnimationFrom(AnimationList** ani_list, Animation** dst, Animation** src, long newX, long newY) {
	*dst = (Animation*)malloc(sizeof(Animation) + sizeof(IMAGEC*));
	if (*dst == NULL) return -1;

	(*dst)->interval = (*src)->interval;
	(*dst)->counter = 0;
	(*dst)->frame_amounts = (*src)->frame_amounts;
	(*dst)->frame_index = 0;
	(*dst)->width = (*src)->width;
	(*dst)->height = (*src)->height;
	(*dst)->atlas = (*src)->atlas;
	(*dst)->atlas_position = (*src)->atlas_position;
	(*dst)->pos.x = 0;
	(*dst)->pos.y = 0;

	if (ani_list == NULL) return 0;
	PushToAnimationList(ani_list, *dst);
	return 0;
}

int RemoveAnimation(AnimationList** ani_list, Animation* todel) {
	return RemoveFromAnimationList(ani_list, todel);
}

void RenderAnimation(Animation* animation) {
	if (animation->counter >= animation->interval) {
		animation->counter = 0;
		animation->frame_index++;
		animation->frame_index %= animation->frame_amounts;

		putimageCS(animation->pos.x, animation->pos.y, animation->width, animation->height, animation->atlas, animation->atlas_position.x + animation->frame_index * animation->width, animation->atlas_position.y);
	}
}

void RenderObjectAnimation(Animation* animation) {

}

void RenderAnimationList(AnimationList* ani_list) {
	for (int i = 0; i < ani_list->size; i++) {
		Animation* cur = ani_list->list[i];
		RenderAnimation(cur);
	}
}

void UpdateAnimationList(AnimationList* ani_list, clock_t delta) {
	for (int i = 0; i < ani_list->size; i++) {
		Animation* cur = ani_list->list[i];
		cur->counter += delta;
	}
}