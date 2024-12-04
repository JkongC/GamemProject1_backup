#pragma comment(lib, "Shcore.lib")

#include <Windows.h>
#include <tchar.h>
#include <malloc.h>
#include <time.h>
#include <ShellScalingApi.h>
#include "easyxC.h"
#include "types.h"
#include "drawing.h"
#include "util.h"

AnimationList* Animations;
Animation* peashooter;

int LoadResources() {
	Animations = (AnimationList*)malloc(sizeof(AnimationList) + 15 * sizeof(Animation*));
	if (Animations == NULL) return -1;
	Animations->capacity = 15;
	Animations->size = 0;
	
	peashooter = (Animation*)malloc(sizeof(Animation) + 9 * sizeof(IMAGEC));
	if (peashooter == NULL) return -1;
	peashooter->counter = 0;
	peashooter->interval = 125;
	peashooter->frame_index = 0;
	peashooter->frame_amounts = 9;
	peashooter->rc_head_index = 101;
	peashooter->pos.x = 500;
	peashooter->pos.y = 500;

	for (int i = 0; i < 9; i++) {
		loadimageCR(&peashooter->frames[i], _T("PNG"), peashooter->rc_head_index + i);
	}

	PushToList(&Animations, peashooter);

	return 0;
}

void FreeResources() {
	clearimageC();
	FreeList(Animations);
}

//WIN32程序主函数
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevHInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow) {
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

	if (LoadResources() == -1) return -1;
	
	HWND hWnd = initgraphC(1280, 960);

	//例子，可以以已有Animation为模板，新建Animation
	Animation* peashooter1;
	Animation* peashooter2;
	NewAnimationFrom(&Animations, &peashooter1, &peashooter, 400, 400);
	NewAnimationFrom(&Animations, &peashooter2, &peashooter, 600, 600);

	BeginBatchDrawC();
	clock_t start = clock();
	
	//游戏主循环
	while (1) {
		
		RenderList(Animations); //绘出列表中所有的Animation

		FlushBatchDrawC();

		//计算帧间隔
		clock_t end = clock();
		clock_t delta = end - start;
		start = end;
		
		UpdateList(Animations, delta); //尝试更新列表中所有Animation的帧

		//控制FPS
		if (delta < 1000 / 144) {
			Sleep(1000 / 144 - delta);
		}
	}
	EndBatchDrawC();

	FreeResources(); //释放资源内存

	return 0;
}
