#pragma once

int PushToList(AnimationList** ani_list, Animation* ani);

int RemoveFromList(AnimationList** ani_list, Animation* ani);

void FreeList(AnimationList* ani_list);