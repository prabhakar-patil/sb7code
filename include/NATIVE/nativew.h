#ifndef __NATIVEW_H__
#define __NATIVEW_H__

#include <windows.h>

//Naked functions
HWND nativeCreateWindow(int width, int height, const char* title);
bool nativePollEvents(void);	//PeekMsg
void nativeInitialize(void);	//wgl context creation
void nativeUninitialize(void);	//moksh
void nativeSwapBuffers(void);
double nativeGetTime(void);

#endif /*__NATIVEW_H__*/