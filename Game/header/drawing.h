#pragma once

int CreateAnimationTemplate(AnimationList** templates, Animation** new_ani, int interval, int frame_amounts, POINT atlas_position, IMAGEC* atlas, int width, int height);

int NewAnimationFrom(AnimationList** ani_list, Animation** dst, Animation** src, long newX, long newY);

int RemoveAnimation(AnimationList** ani_list, Animation* todel);

void RenderAnimation(Animation* animation);

void RenderObjectAnimation(Animation* animation);

void RenderAnimationList(AnimationList* ani_list);

void UpdateAnimationList(AnimationList* ani_list, clock_t delta);