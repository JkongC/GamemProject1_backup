#pragma once

#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include <graphics.h>
#include "easyxC.h"
#include "types.h"
#include "animation.h"
#include "util.h"
 
class Button 
{
	public:
		Button( RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed )
		{
			region = rect;

			loadimageC(&img_idle, path_img_idle);		
			loadimageC(&img_hovered, path_img_hovered);
			loadimageC(&img_pushed, path_img_pushed);
		}

		~Button() = default;


	void Draw()
	{
		switch (status)
		{
		case Button::Status::Idle:
			putimageC(region.left, region.top, &img_idle);
			break;
		case Button::Status::Hovered:
			putimageC(region.left, region.top, &img_hovered);
			break;
		case Button::Status::Pushed:
			putimageC(region.left, region.top, &img_pushed);
			break;
		default:
			break;
		}
	}

	void ProcessEvent(const ExmessageC& msg)
	{
		switch (msg.message)
		{
		case WM_MOUSEMOVE: // 鼠标移动事件
			if (status == Status::Idle && CheckCursorHit(msg.x, msg.y))
				status = Status::Hovered; // 如果状态为空闲且鼠标在指定区域内，状态变为悬停
			else if (status == Status::Hovered && !CheckCursorHit(msg.x, msg.y))
				status = Status::Idle; // 如果状态为悬停且鼠标不在指定区域内，状态变为空闲
			break;

		case WM_LBUTTONDOWN: // 鼠标左键按下事件
			if (CheckCursorHit(msg.x, msg.y))
				status = Status::Pushed; // 如果鼠标在指定区域内，状态变为按下
			break;

		case WM_LBUTTONUP: // 鼠标左键释放事件
			if (status == Status::Pushed)
				OnClick(); // 如果状态为按下，调用OnClick函数
			break;

		default:
			break; // 默认情况下不执行任何操作
		}
	}

	protected:
		virtual void Onclicked() = 0;

	private:
		enum class Status
		{ 
			Idle = 0,
			Hovered,
			Pushed
		};

	private:
		RECT region;
		IMAGEC img_idle;
		IMAGEC img_hovered;
		IMAGEC img_pushed;
		Status status = Status::Idle;

	private:
		bool ChechCursorHit(int x, int y) {
			return x >= region.left && x <= region.right && y >= region.top && y <= region.bottom;
		}
};

// 开始游戏按钮
class StartGameButton : public Button
{
public:
	// 构造函数，初始化按钮的位置、闲置状态的图片路径、悬停状态的图片路径和按下状态的图片路径
	StartGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
		: Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {
	}
	~StartGameButton() = default; // 默认析构函数

protected:
	// 当按钮被点击时调用的函数
	void OnClick()
	{
		is_game_started = true; // 设置游戏开始标志为真
	}
};

// 退出游戏按钮
class QuitGameButton : public Button
{
public:
	// 构造函数，初始化按钮的位置、闲置状态的图片路径、悬停状态的图片路径和按下状态的图片路径
	QuitGameButton(RECT rect, LPCTSTR path_img_idle, LPCTSTR path_img_hovered, LPCTSTR path_img_pushed)
		: Button(rect, path_img_idle, path_img_hovered, path_img_pushed) {
	}
	~QuitGameButton() = default; // 默认析构函数

protected:
	// 当按钮被点击时调用的函数
	void OnClick()
	{
		running = false; // 设置运行标志为假，通常用于退出游戏循环
	}
};