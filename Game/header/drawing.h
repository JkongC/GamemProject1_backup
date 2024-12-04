#pragma once

int NewAnimationFrom(AnimationList** ani_list, Animation** dst, Animation** src, long newX, long newY);

void Render(Animation* animation);

void RenderList(AnimationList* ani_list);