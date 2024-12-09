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
AniTemplate* peashooter_idle_1;
AniTemplate* walk;

Registry Templates_Object;
ObjTemplate peashooter;
ObjTemplate ltman;

Scene* current_scene;
Scene menu;
Scene game;

int LoadResources() {
	//��ʼ������ģ���б�
	TRY(InitializeAnimationList(&Templates_Animation));

	//��ʼ����������
	TRY(InitializeScene(&menu));
	TRY(InitializeScene(&game));
	SetCurrentScene(&menu);
	
	//��ʼ������ģ��
	TRY(CreateAnimationTemplate(&Templates_Animation, &peashooter_idle_1, 0, 1, 0, 0, IDB_PNG1, 96, 96, 1));
	TRY(CreateAnimationTemplate(&Templates_Animation, &walk, 200, 4, 0, 0, RC_TEST, 15, 17, 4));
	
	//ע����Ϸ����
	peashooter = RegisterObject(&Templates_Object, OBJ_NORMAL, LIFE_INF, 1, peashooter_idle_1);
	ltman = RegisterObject(&Templates_Object, OBJ_NORMAL, LIFE_INF, 1, walk);

	return 0;
}

void FreeResources() {
	FreeAnimationList(Templates_Animation);
	FreeObjectRegistry(&Templates_Object);
	FreeObjects(current_scene->Objects);
	free(menu.Objects);
	free(game.Objects);
	clearimageC();
}

//WIN32����������
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevHInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow) {
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);  //�ô��ڴ�С����ϵͳ��������Ӱ��

	TRY(LoadResources());  //������Դ
	
	HWND hWnd = initgraphC(1280, 960, EX_NOCLOSE);  //��ʼ������

	int running = 1;  //��־��Ϸ�Ƿ�Ӧ��������

	//���������Ƕ��󴴽�������
	Object* ps1 = NewObject(peashooter, 200, 200);  //����peashooter������ps1�������ַ

	Object* littleman = NewObject(ltman, 500, 500); //��Ҫָ�������ʼ����

	Object* littleman_copy = NewObject(ltman, 800, 300);

	NewObject(ltman, 800, 700);  //������ö�����������Ҳ���Բ����շ���ֵ
	
	
	BeginBatchDrawC();  //��ʼ˫����
	clock_t start = clock();
	//��Ϸ��ѭ��
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

		cleardeviceC();  //���Ļ���ͼ��
		
		RenderAllObjects();  //�����ǰ�������ж���

		FlushBatchDrawC();  //����ͼ����л���ǰ̨

		//����֡���
		clock_t end = clock();
		clock_t delta = end - start;
		start = end;
		
		TickAllObjects(delta);  //���µ�ǰ�������ж���

		//����FPS
		if (delta < 1000 / 144) {
			Sleep(1000 / 144 - delta);
		}

		if (!running) break;  //���runningΪ0���˳���Ϸ
	}
	EndBatchDrawC();  //����˫����

	FreeResources(); //�ͷ���Դ�ڴ�

	return 0;
}
