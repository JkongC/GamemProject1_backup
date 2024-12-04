#pragma once

int NewAnimationFrom(AnimationList** ani_list, Animation** dst, Animation** src, long newX, long newY);

void Render(Animation* animation);

void RenderList(AnimationList* ani_list);

void UpdateList(AnimationList* ani_list, clock_t delta);