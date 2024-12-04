#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include "easyxC.h"
#include "types.h"
#include "drawing.h"
#include "util.h"

int NewAnimationFrom(AnimationList** ani_list, Animation** dst, Animation** src, long newX, long newY) {
	*dst = (Animation*)malloc(sizeof(Animation) + (*src)->frame_amounts * sizeof(IMAGEC));
	if (*dst == NULL) return -1;
	**dst = **src;
	(*dst)->pos.x = newX;
	(*dst)->pos.y = newY;
	(*dst)->counter = 0;

	for (int i = 0; i < (*src)->frame_amounts; i++) {
		loadimageCR(&(*dst)->frames[i], _T("PNG"), (*src)->rc_head_index + i);
	}
	PushToList(ani_list, *dst);

	return 0;
}

void Render(Animation* animation) {
	if (animation->counter >= animation->interval) {
		animation->counter = 0;
		animation->frame_index++;
		animation->frame_index %= animation->frame_amounts;

		putimageC(animation->pos.x, animation->pos.y, &animation->frames[animation->frame_index]);
	}
}

void RenderList(AnimationList* ani_list) {
	for (int i = 0; i < ani_list->size; i++) {
		Animation* cur = ani_list->list[i];
		if (cur->counter >= cur->interval) {
			cur->counter = 0;
			cur->frame_index++;
			cur->frame_index %= cur->frame_amounts;

			putimageC(cur->pos.x, cur->pos.y, &cur->frames[cur->frame_index]);
		}
	}
}

void UpdateList(AnimationList* ani_list, clock_t delta) {
	for (int i = 0; i < ani_list->size; i++) {
		Animation* cur = ani_list->list[i];
		cur->counter += delta;
	}
}