#include <Windows.h>
#include <tchar.h>
#include "easyxC.h"
#include "types.h"
#include "util.h"

int PushToList(AnimationList** ani_list, Animation* ani) {
	AnimationList* a_list = *ani_list;
	if (a_list->size == a_list->capacity) {
		AnimationList* new_list = (AnimationList*)realloc(a_list, sizeof(AnimationList) + (a_list->capacity + 5) * sizeof(Animation*));
		if (new_list == NULL) {
			return -1;
		}

		*ani_list = new_list;
		(*ani_list)->capacity += 5;
	}

	(*ani_list)->list[(*ani_list)->size] = ani;
	(*ani_list)->size++;

	return 0;
}

int RemoveFromList(AnimationList** ani_list, Animation* ani) {
	AnimationList* a_list = *ani_list;
	int found = 0;
	for (int i = 0; i < a_list->size; i++) {
		if (a_list->list[i] == ani) {
			a_list->list[i] = a_list->list[a_list->size - 1];
			a_list->size--;

			found = 1;
			break;
		}
	}

	if (!found) return -1;
	return 0;
}

void FreeList(AnimationList* ani_list) {
	for (int i = 0; i < ani_list->size; i++) {
		free(ani_list->list[i]);
	}
	free(ani_list);
}