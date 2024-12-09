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
	//初始化动画模板列表
	TRY(InitializeAnimationList(&Templates_Animation));

	//初始化场景变量
	TRY(InitializeScene(&menu));
	TRY(InitializeScene(&game));
	SetCurrentScene(&menu);
	
	//初始化动画模板
	TRY(CreateAnimationTemplate(&Templates_Animation, &peashooter_idle_1, 0, 1, 0, 0, IDB_PNG1, 96, 96, 1));
	TRY(CreateAnimationTemplate(&Templates_Animation, &walk, 200, 4, 0, 0, RC_TEST, 15, 17, 4));
	
	//注册游戏对象
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

//WIN32程序主函数
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevHInstance, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow) {
	SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);  //让窗口大小不受系统缩放设置影响

	TRY(LoadResources());  //加载资源
	
	HWND hWnd = initgraphC(1280, 960, EX_NOCLOSE);  //初始化窗口

	int running = 1;  //标志游戏是否应继续运行

	//以下四行是对象创建的例子
	Object* ps1 = NewObject(peashooter, 200, 200);  //创建peashooter对象并用ps1储存其地址

	Object* littleman = NewObject(ltman, 500, 500); //需要指定对象初始坐标

	Object* littleman_copy = NewObject(ltman, 800, 300);

	NewObject(ltman, 800, 700);  //如果想让对象自生自灭，也可以不接收返回值
	
	
	BeginBatchDrawC();  //开始双缓冲
	clock_t start = clock();
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

		cleardeviceC();  //清空幕后绘图区
		
		RenderAllObjects();  //绘出当前场景所有对象

		FlushBatchDrawC();  //将绘图结果切换至前台

		//计算帧间隔
		clock_t end = clock();
		clock_t delta = end - start;
		start = end;
		
		TickAllObjects(delta);  //更新当前场景所有对象

		//控制FPS
		if (delta < 1000 / 144) {
			Sleep(1000 / 144 - delta);
		}

		if (!running) break;  //如果running为0则退出游戏
	}
	EndBatchDrawC();  //结束双缓冲

	FreeResources(); //释放资源内存

	return 0;
}
