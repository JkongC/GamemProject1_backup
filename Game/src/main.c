#pragma comment(lib, "Shcore.lib")

#include <Windows.h>
#include <tchar.h>
#include <malloc.h>
#include <time.h>
#include <ShellScalingApi.h>
#include "easyxC.h"
#include "types.h"
#include "animation.h"
#include "util.h"
#include "objects.h"
#include "resource.h"

AnimationList* Templates_Animation;
Animation* peashooter_idle_1;
Animation* walk;


Registry Templates_Object;
ListWithID Objects;

ObjTemplate peashooter;
ObjTemplate ltman;

int LoadResources() {
	Templates_Animation = (AnimationList*)malloc(sizeof(AnimationList) + 10 * sizeof(Animation*));
	if (Templates_Animation == NULL) return -1;
	Templates_Animation->capacity = 15;
	Templates_Animation->size = 0;

	InitializeListWithID(&Objects);
	
	CreateAnimationTemplate(&Templates_Animation, &peashooter_idle_1, 0, 1, 0, 0, IDB_PNG1, 96, 96, 1);
	CreateAnimationTemplate(&Templates_Animation, &walk, 200, 4, 0, 0, RC_TEST, 15, 17, 4);
	
	peashooter = RegisterObject(&Templates_Object, OBJ_NORMAL, LIFE_INF, &peashooter_idle_1);
	ltman = RegisterObject(&Templates_Object, OBJ_NORMAL, LIFE_INF, &walk);

	return 0;
}

void FreeResources() {
	FreeAnimationList(Templates_Animation);
	FreeObjectRegistry(&Templates_Object);
	FreeObjects(&Objects);
	clearimageC();
}

//WIN32程序主函数
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevHInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow) {
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

	if (LoadResources() == -1) return -1;
	
	HWND hWnd = initgraphC(1280, 960, EX_NOCLOSE);

	int running = 1;

	BeginBatchDrawC();
	clock_t start = clock();

	Object* ps1 = NewObject(&Objects, &Templates_Object, peashooter);
	ps1->pos.x = 200;
	ps1->pos.y = 200;

	Object* littleman = NewObject(&Objects, &Templates_Object, ltman);
	littleman->pos.x = 500;
	littleman->pos.y = 500;

	Object* littleman_copy = NewObject(&Objects, &Templates_Object, ltman);
	littleman_copy->pos.x = 700;
	littleman_copy->pos.y = 700;
	
	//游戏主循环
	while (1) {
		
		ExMessageC msg;
		memset(&msg, 0, sizeof(ExMessageC));

		while (peekmessageC(&msg, EX_ALL)) {
			if (msg.message == WM_KEYDOWN) {
				if (msg.vkcode == VK_ESCAPE) {
					running = 0;
					break;
				}
			}
		}

		RenderObjectList(&Objects);

		FlushBatchDrawC();

		//计算帧间隔
		clock_t end = clock();
		clock_t delta = end - start;
		start = end;
		
		UpdateObjectList(&Objects, delta);

		//控制FPS
		if (delta < 1000 / 144) {
			Sleep(1000 / 144 - delta);
		}

		if (!running) break;
	}
	EndBatchDrawC();

	FreeResources(); //释放资源内存

	return 0;
}
