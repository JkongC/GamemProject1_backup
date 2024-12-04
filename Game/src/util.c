#include <Windows.h>
#include <tchar.h>
#include "easyxC.h"
#include "types.h"
#include "util.h"

int PushToList(AnimationList** ani_list, Animation* ani) {
	if ((*ani_list)->size == (*ani_list)->capacity) {
		Animation* new_list;
		new_list = realloc(*ani_list, sizeof(AnimationList) + (*ani_list)->capacity + 5);
		if (new_list == NULL) {
			return -1;
		}
		else {
			*ani_list = new_list;
		}
		(*ani_list)->capacity += 5;
	}

	(*ani_list)->list[(*ani_list)->size] = ani;
	(*ani_list)->size++;

	return 0;
}

void FreeList(AnimationList* ani_list) {
	for (int i = 0; i < ani_list->size; i++) {
		free(ani_list->list[i]);
	}
	free(ani_list);
}