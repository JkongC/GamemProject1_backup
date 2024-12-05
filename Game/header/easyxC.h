#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#define EX_SHOWCONSOLE		1		// Maintain the console window when creating a graphics window
#define EX_NOCLOSE			2		// Disable the close button
#define EX_NOMINIMIZE		4		// Disable the minimize button
#define EX_DBLCLKS			8		// Support double-click events

#define EX_MOUSE	1
#define EX_KEY		2
#define EX_CHAR		4
#define EX_WINDOW	8

#define	BLACK			0
#define	BLUE			0xAA0000
#define	GREEN			0x00AA00
#define	CYAN			0xAAAA00
#define	RED				0x0000AA
#define	MAGENTA			0xAA00AA
#define	BROWN			0x0055AA
#define	LIGHTGRAY		0xAAAAAA
#define	DARKGRAY		0x555555
#define	LIGHTBLUE		0xFF5555
#define	LIGHTGREEN		0x55FF55
#define	LIGHTCYAN		0xFFFF55
#define	LIGHTRED		0x5555FF
#define	LIGHTMAGENTA	0xFF55FF
#define	YELLOW			0x55FFFF
#define	WHITE			0xFFFFFF

#define BGR(color)	( (((color) & 0xFF) << 16) | ((color) & 0xFF00FF00) | (((color) & 0xFF0000) >> 16) )

	typedef struct IMAGEX {
		void* image;
	} IMAGEC;

	static IMAGEC nullimagex = { NULL };

#define nullimagec &nullimagex;

	typedef struct ExMessageX {
		void* ExMessage;
		unsigned short message;
	} ExMessageC;

	HWND initgraphC(int x, int y);
	void closegraphC();

	void loadimageC(IMAGEC* pDstImg, LPCTSTR pImgFile, int nWidth, int nHeight);
	void loadimageCR(IMAGEC** pDstImg, LPCTSTR pResType, LPCTSTR pResName);
	void putimageC(int dstX, int dstY, const IMAGEC* pSrcImg);
	void putimageCS(int dstX, int dstY, int dstWidth, int dstHeight, const IMAGEC* pSrcImg, int srcX, int srcY);
	int imagec_getwidth(IMAGEC* pImg);
	int imagec_getheight(IMAGEC* pImg);
	void ResizeC(IMAGEC* pImg, int width, int height);
	DWORD* GetImageBufferC(IMAGEC* pImg);
	void saveimageC(LPCTSTR pImgFile, IMAGEC* pImg);
	void getimageC(IMAGEC* pDstImg, int srcX, int srcY, int srcWidth, int srcHeight);
	HDC GetImageHDCC(IMAGEC* pImg);
	void deleteimageC(IMAGEC* pImg);
	void clearimageC();
	IMAGEC* GetWorkingImageC();
	void SetWorkingImageC(IMAGEC* pImg);

	void BeginBatchDrawC();
	void FlushBatchDrawC();
	void EndBatchDrawC();
	void cleardeviceC();

	HWND GetHWndC();

	void outtextxyC(int x, int y, TCHAR c);
	void outtextxyCS(int x, int y, LPCTSTR str);

	int peekmessageC(ExMessageC* msg);
	void flushmessageC();
	void setcaptureC();
	void releasecaptureC();

#ifdef __cplusplus
}
#endif
