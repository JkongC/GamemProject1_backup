#pragma once

typedef struct ani {
	int frame_amounts; //动画帧总数
	int interval;
	int width; //动画帧宽
	int height; //动画帧高
	IMAGEC* atlas; //图集
	POINT atlas_position; //对应图集在给定图集图片中的起始像素坐标（左上角）
} Animation;

typedef struct anilst {
	int capacity; //总容量
	int size; //列表内元素数
	Animation* list[];
} AnimationList;

int CreateAnimationTemplate(AnimationList** templates, Animation** new_ani, int interval, int frame_amounts, int atlas_position_x, int atlas_position_y, int rc_index, int width, int height, int scale);

int RemoveAnimation(AnimationList** ani_list, Animation* todel);

void RenderAnimation(Animation* animation, int frame_index, int pos_x, int pos_y);