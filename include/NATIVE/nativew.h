#ifndef __NATIVEW_H__
#define __NATIVEW_H__

#include <windows.h>

typedef void(*PFN_RESIZE)(void*, int, int);

//Naked functions
HWND nativeCreateWindow(int width, int height, const char* title);
bool nativePollEvents(void);	//PeekMsg
void nativeInitialize(void);	//wgl context creation
void nativeUninitialize(void);	//moksh
void nativeSwapBuffers(void);
void nativeInitTimer(void);
double nativeGetTime(void);
void nativeSetWindowSizeCallback(PFN_RESIZE);

#endif /*__NATIVEW_H__*/
