#include <vector>
#include <algorithm>
#include <easyx.h>
#include <graphics.h>
#include "easyxC.h"

std::vector<IMAGEC*> imagec_list;

HWND initgraphC(int x, int y) {
	return initgraph(x, y);
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

void loadimageC(IMAGEC* pDstImg, LPCTSTR pImgFile, int nWidth = 0, int nHeight = 0) {
	IMAGE* img = new IMAGE();
	loadimage(img, pImgFile, nWidth, nHeight);
	pDstImg->image = img;
	imagec_list.push_back(pDstImg);
}

void loadimageCR(IMAGEC** pDstImg, LPCTSTR pResType, LPCTSTR pResName) {
	*pDstImg = (IMAGEC*)malloc(sizeof(IMAGEC));
	if (*pDstImg == NULL) DebugBreak();
	
	IMAGE* img = new IMAGE();
	loadimage(img, pResType, pResName);
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

int peekmessageC(ExMessageC* msg) {
	if (msg->ExMessage == NULL) {
		static ExMessage exmsg;
		msg->ExMessage = &exmsg;
	}
	bool ret = peekmessage((ExMessage*)msg->ExMessage);
	msg->message = ((ExMessage*)msg->ExMessage)->message;
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