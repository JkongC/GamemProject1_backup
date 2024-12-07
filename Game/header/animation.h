#pragma once

int CreateAnimationTemplate(AnimationList** templates, Animation** new_ani, int interval, int frame_amounts, int atlas_position_x, int atlas_position_y, int rc_index, int width, int height);

int NewAnimationFrom(AnimationList** ani_list, Animation** dst, Animation** src, long newX, long newY);

int RemoveAnimation(AnimationList** ani_list, Animation* todel);

void RenderAnimation(Animation* animation);

void RenderAnimationList(AnimationList* ani_list);

void UpdateAnimation(Animation* animation, clock_t delta);

void UpdateAnimationList(AnimationList* ani_list, clock_t delta);