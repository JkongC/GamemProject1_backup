#pragma once

int CreateAnimationTemplate(AnimationList** templates, Animation** new_ani, int interval, int frame_amounts, int rc_head_index);

int NewAnimationFrom(AnimationList** ani_list, Animation** dst, Animation** src, long newX, long newY);

int RemoveAnimation(AnimationList** ani_list, Animation* todel);

void Render(Animation* animation);

void RenderList(AnimationList* ani_list);

void UpdateList(AnimationList* ani_list, clock_t delta);