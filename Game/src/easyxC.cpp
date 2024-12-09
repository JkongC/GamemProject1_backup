#include <vector>
#include <algorithm>
#include <easyx.h>
#include <graphics.h>
#include "easyxC.h"

std::vector<IMAGEC*> imagec_list;

HWND initgraphC(int x, int y, int flag) {
	return initgraph(x, y, flag);
}

void closegraphC() {
	closegraph();
}

void outtextxyC(int x, int y, TCHAR c) {
	outtextxy(x, y, c);
}

void outtextxyCS(int x, int y, LPCTSTR str) {
	outtextxy(x, y, str);
}

IMAGEC* newimageC(int nWidth, int nHeight) {
	IMAGE* img = new IMAGE(nWidth, nHeight);
	IMAGEC* new_imgC = (IMAGEC*)malloc(sizeof(IMAGEC));
	if (new_imgC == NULL) return NULL;

	new_imgC->image = img;
	imagec_list.push_back(new_imgC);

	return new_imgC;
}

void loadimageC(IMAGEC** pDstImg, LPCTSTR pImgFile, int nWidth = 0, int nHeight = 0, bool bResize = false) {
	*pDstImg = (IMAGEC*)malloc(sizeof(IMAGEC));
	if (*pDstImg == NULL) return;
	
	IMAGE* img = new IMAGE(nWidth, nHeight);
	loadimage(img, pImgFile, nWidth, nHeight, bResize);
	(*pDstImg)->image = img;
	imagec_list.push_back(*pDstImg);
}

void loadimageCR(IMAGEC** pDstImg, LPCTSTR pResType, LPCTSTR pResName, int nWidth = 0, int nHeight = 0, bool bResize = false) {
	*pDstImg = (IMAGEC*)malloc(sizeof(IMAGEC));
	if (*pDstImg == NULL) return;
	
	IMAGE* img = new IMAGE(nWidth, nHeight);
	loadimage(img, pResType, pResName, nWidth, nHeight, bResize);
	(*pDstImg)->image = img;
	imagec_list.push_back(*pDstImg);
}

void putimageC(int dstX, int dstY, const IMAGEC* pSrcImg) {
	IMAGE* img = (IMAGE*)pSrcImg->image;
	putimage(dstX, dstY, img);
}

void putimageCS(int dstX, int dstY, int dstWidth, int dstHeight, const IMAGEC* pSrcImg, int srcX, int srcY) {
	putimage(dstX, dstY, dstWidth, dstHeight, (IMAGE*)pSrcImg->image, srcX, srcY);
}

int imagec_getwidth(IMAGEC* pImg) {
	IMAGE* img = (IMAGE*)pImg->image;
	return img->getwidth();
}

int imagec_getheight(IMAGEC* pImg) {
	IMAGE* img = (IMAGE*)pImg->image;
	return img->getheight();
}

void ResizeC(IMAGEC* pImg, int width, int height) {
	IMAGE* img = (IMAGE*)pImg->image;
	Resize(img, width, height);
}

DWORD* GetImageBufferC(IMAGEC* pImg) {
	IMAGE* img = (IMAGE*)pImg->image;
	return GetImageBuffer(img);
}

HDC GetImageHDCC(IMAGEC* pImg) {
	if (pImg->image == NULL) return GetImageHDC();
	IMAGE* img = (IMAGE*)pImg->image;
	return GetImageHDC(img);
	
}

void deleteimageC(IMAGEC* pImg) {
	delete (IMAGE*)pImg->image;
	for (IMAGEC*& todel : imagec_list) {
		if (todel == pImg) {
			std::swap(todel, imagec_list.back());
			imagec_list.pop_back();
			return;
		}
	}
}

void clearimageC() {
	for (IMAGEC* todel : imagec_list) {
		delete todel->image;
	}
	imagec_list.clear();
}

void saveimageC(LPCTSTR pImgFile, IMAGEC* pImg) {
	IMAGE* img = (IMAGE*)pImg->image;
	saveimage(pImgFile, img);
}

void getimageC(IMAGEC* pDstImg, int srcX, int srcY, int srcWidth, int srcHeight) {
	IMAGE* img = (IMAGE*)pDstImg->image;
	getimage(img, srcX, srcY, srcWidth, srcHeight);
}

IMAGEC* GetWorkingImageC() {
	IMAGE* img = GetWorkingImage();
	for (IMAGEC* toget : imagec_list) {
		if (toget->image == img) {
			return toget;
		}
	}
	return NULL;
}

void SetWorkingImageC(IMAGEC* pImg) {
	IMAGE* img = (IMAGE*)pImg->image;
	SetWorkingImage(img);
}

void BeginBatchDrawC() {
	BeginBatchDraw();
}

void FlushBatchDrawC() {
	FlushBatchDraw();
}

void EndBatchDrawC() {
	EndBatchDraw();
}

void cleardeviceC() {
	cleardevice();
}

HWND GetHWndC() {
	return GetHWnd();
}

HDC getscreenHDC() {
	return GetImageHDC();
}

int peekmessageC(ExMessageC* msg, BYTE filter) {
	static ExMessage exmsg;
	if (msg->ExMessage == NULL) {
		msg->ExMessage = &exmsg;
	}
	bool ret = peekmessage((ExMessage*)msg->ExMessage);
	msg->message = ((ExMessage*)msg->ExMessage)->message;

	switch (msg->message) {
		case WM_MOUSEMOVE:
		case WM_MOUSEWHEEL:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MBUTTONDBLCLK:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_RBUTTONDBLCLK:
			msg->ctrl = exmsg.ctrl;
			msg->shift = exmsg.shift;
			msg->lbutton = exmsg.lbutton;
			msg->mbutton = exmsg.mbutton;
			msg->rbutton = exmsg.rbutton;
			msg->x = exmsg.x;
			msg->y = exmsg.y;
			msg->wheel = exmsg.wheel;

			break;

		case WM_KEYDOWN:
		case WM_KEYUP:
			msg->vkcode = exmsg.vkcode;
			msg->scancode = exmsg.scancode;
			msg->extended = exmsg.extended;
			msg->prevdown = exmsg.prevdown;

			break;

		case WM_CHAR:
			msg->ch = exmsg.ch;

			break;

		case WM_ACTIVATE:
		case WM_MOVE:
		case WM_SIZE:
			msg->wParam = exmsg.wParam;
			msg->lParam = exmsg.lParam;

			break;

		default: break;
	}

	return ret;
}

void flushmessageC() {
	flushmessage();
}

void setcaptureC() {
	setcapture();
}

void releasecaptureC() {
	releasecapture();
}