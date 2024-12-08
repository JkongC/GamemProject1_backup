#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include "easyxC.h"
#include "types.h"
#include "animation.h"
#include "util.h"

int CreateAnimationTemplate(AnimationList** templates, Animation** new_ani, int interval, int frame_amounts, int atlas_position_x, int atlas_position_y, int rc_index, int width, int height, int scale) {
	Animation* new_p = (Animation*)malloc(sizeof(Animation) + sizeof(IMAGEC*));
	if (new_p == NULL) return -1;

	IMAGEC* atlas;
	loadimageCR(&atlas, _T("PNG"), MAKEINTRESOURCE(rc_index), width * frame_amounts, height, false);

	IMAGEC* atlas_scale = newimageC(width * scale * frame_amounts, height * scale);
	if (atlas_scale == NULL) return -1;
	ScalingByPixel(atlas_scale, atlas, scale);
	deleteimageC(atlas);
	
	*new_ani = new_p;
	(*new_ani)->interval = interval;
	(*new_ani)->frame_amounts = frame_amounts;
	(*new_ani)->width = width * scale;
	(*new_ani)->height = height * scale;
	(*new_ani)->atlas = atlas_scale;
	(*new_ani)->atlas_position.x = atlas_position_x;
	(*new_ani)->atlas_position.y = atlas_position_y;

	if (PushToAnimationList(templates, *new_ani) == -1) {
		return -1;
	}

	return 0;
}

int RemoveAnimation(AnimationList** ani_list, Animation* todel) {
	return RemoveFromAnimationList(ani_list, todel);
}

void RenderAnimation(Animation* animation, int frame_index, int pos_x, int pos_y) {
	putimageCS(pos_x, pos_y, animation->width, animation->height, animation->atlas, animation->atlas_position.x + frame_index * animation->width, animation->atlas_position.y);
}