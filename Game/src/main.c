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

AnimationList* Templates;
AnimationList* Animations;
Animation* peashooter_template;

int LoadResources() {
	Animations = (AnimationList*)malloc(sizeof(AnimationList) + 15 * sizeof(Animation*));
	if (Animations == NULL) return -1;
	Animations->capacity = 15;
	Animations->size = 0;

	Templates = (AnimationList*)malloc(sizeof(AnimationList) + 10 * sizeof(Animation*));
	if (Templates == NULL) return -1;
	Templates->capacity = 15;
	Templates->size = 0;
	
	if (CreateAnimationTemplate(&Templates, &peashooter_template, 125, 9, 101) == -1) return -1;

	return 0;
}

void FreeResources() {
	FreeList(Animations);
	FreeList(Templates);
	clearimageC();
}

//WIN32����������
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevHInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow) {
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

	if (LoadResources() == -1) return -1;
	
	HWND hWnd = initgraphC(1280, 960, EX_NOCLOSE);

	int running = 1;

	//���ӣ�����������AnimationΪģ�壬�½�Animation
	Animation* peashooter1;
	Animation* peashooter2;
	NewAnimationFrom(&Animations, &peashooter1, &peashooter_template, 400, 400);
	NewAnimationFrom(&Animations, &peashooter2, &peashooter_template, 600, 600);

	BeginBatchDrawC();
	clock_t start = clock();
	
	//��Ϸ��ѭ��
	while (1) {
		
		ExMessageC msg;
		memset(&msg, 0, sizeof(ExMessageC));

		while (peekmessageC(&msg)) {
			if (msg.message == WM_KEYDOWN) {
				if (msg.vkcode == VK_ESCAPE) {
					running = 0;
					break;
				}
			}
		}
		
		
		RenderList(Animations); //����б������е�Animation

		FlushBatchDrawC();

		//����֡���
		clock_t end = clock();
		clock_t delta = end - start;
		start = end;
		
		UpdateList(Animations, delta); //���Ը����б�������Animation��֡

		//����FPS
		if (delta < 1000 / 144) {
			Sleep(1000 / 144 - delta);
		}

		if (!running) break;
	}
	EndBatchDrawC();

	FreeResources(); //�ͷ���Դ�ڴ�

	return 0;
}
