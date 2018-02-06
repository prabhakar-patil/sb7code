/*
	Desc	- Native Win32 Windowing Function Implementations
	Author	- Raster/Prabhakar
	Date	- 06-Feb-2018
*/

/**************************************
Programmable Pipeline OpenGL Code
***************************************/
#include <windows.h>
#include <stdio.h>	// for FILE

#if 0
	#include <GL/glew.h>	// for GLSL extensions. MUST be include before gl.h
	#include <GL/gl.h>


	#pragma comment(lib,"opengl32.lib")
	//This defines are passed at built time from commmand line
	#ifdef _WIN64
	#pragma comment(lib,"C:/glew/lib/Release/x64/glew32.lib")
	#else
	#pragma comment(lib,"C:/glew/lib/Release/Win32/glew32.lib")
	#endif
#endif 
// Legends
// (O) : Optional
// (M) : Mandetory 
// 3D  : 3D drawing

#define WIN_WIDTH	800
#define WIN_HEIGHT	600

#if 0
using namespace vmath;
#endif

#if 0
enum
{
	VDG_ATTRIBUTE_POSITION = 0,
	VDG_ATTRIBUTE_COLOR,
	VDG_ATTRIBUTE_NORMAL,
	VDG_ATTRIBUTE_TEXTURE0,
};
#endif

//global variables
FILE *gpLogFile = NULL;
HWND ghwnd;
HDC ghdc;
HGLRC ghrc;
DWORD dwStyle;
bool gbActiveWindow = false;
bool gbEscapeKeyPressed = false;
bool gbFullscreen = false;
int gWinWidth;
int gWinHeight;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

#if 0
GLfloat g_anglePyramid = 0.0f;
GLfloat g_angleCube = 0.0f;

//Shader specific
GLuint gVertexShaderObject;
GLuint gFragmentShaderObject;
GLuint gShaderProgramObject;
GLuint gVao_Pyramid, gVao_Cube;
GLuint gVbo_position, gVbo_color;
GLuint gMVPUniform;

//User define Data types from vmath.h
mat4 gPerspectiveProjectionMatrix;
#endif 

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#if 0
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int iCmdshow)
{
	int nativeWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int iCmdshow);
	return nativeWinMain(hInstance, hPrevInstance, lpCmdline, iCmdshow);
}

int nativeWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int iCmdshow)
{
	WNDCLASSEX wndclass;
	MSG msg;
	TCHAR szAppName[] = TEXT("OpenGL-PP");
	HWND hwnd;
	POINT pt;
	RECT rc;
	BOOL fResult;
	LONG cx, cy;
	bool bDone = false;
	void initialize(void);
	void uninitialize(void);
	void display(void);
	void spin(void);

	if (fopen_s(&gpLogFile, "Log.txt", "w") < 0)
	{
		MessageBox(NULL, TEXT("Failed to open Log.txt\nExiting..."), TEXT("Error!"), MB_OK | MB_ICONSTOP);
		exit(0);
	}
	else
	{
		fprintf(gpLogFile, "Log.txt created successfully\n");
	}

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);
	fResult = SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
	if (fResult)
	{
		cx = (rc.right - rc.left);
		cy = (rc.bottom - rc.top);
		pt.x = (int)((cx - WIN_WIDTH) / 2);
		pt.y = (int)((cy - WIN_HEIGHT) / 2);
	}
	
	hwnd = CreateWindowEx(WS_EX_APPWINDOW, szAppName,
		TEXT("Programmable-Pipeline: 3D Rotation of Pyramid and Cube"),
		(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPCHILDREN | WS_VISIBLE),
		pt.x,
		pt.y,
		WIN_WIDTH,
		WIN_HEIGHT,
		NULL,			/*Parent window handle*/
		NULL,			/*HMENU*/
		hInstance,
		NULL);			/*Something extra info if you want to provide*/

	ghwnd = hwnd;

	ShowWindow(hwnd, iCmdshow);
	SetForegroundWindow(hwnd);		// bring window on top
	SetFocus(hwnd);					// bring focus on window to accept keyboard

	initialize();
	//gameloop
	while (bDone != true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
		{// message is there 
			if (msg.message == WM_QUIT)
				bDone = true;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActiveWindow == true)
			{
				if (gbEscapeKeyPressed == true)
					bDone = true;
			}
			spin();
			/*rendor here*/
			display();
		}
	}
	uninitialize();
	return((int)msg.wParam);
}
#endif
HWND nativeCreateWindow(int width, int height, const char* title)
{
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("OpenGL-PP");
	HWND hwnd;
	POINT pt;
	RECT rc;
	BOOL fResult;
	LONG cx, cy;

	if (fopen_s(&gpLogFile, "Log.txt", "w") < 0)
	{
		MessageBox(NULL, TEXT("Failed to open Log.txt\nExiting..."), TEXT("Error!"), MB_OK | MB_ICONSTOP);
		exit(0);
	}
	else
	{
		fprintf(gpLogFile, "Log.txt created successfully\n");
		fprintf(gpLogFile, "Window Size: %dx%d\n", width, height);
		fprintf(gpLogFile, "Window Title: %s\n", title);
	}

	gWinWidth = width;
	gWinHeight = height;

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = GetModuleHandle(NULL);
	wndclass.lpfnWndProc = WndProc;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;

	RegisterClassEx(&wndclass);
	fResult = SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
	if (fResult)
	{
		cx = (rc.right - rc.left);
		cy = (rc.bottom - rc.top);
		pt.x = (int)((cx - width) / 2);
		pt.y = (int)((cy - height) / 2);
	}

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, szAppName,
		TEXT(title),
		(WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPCHILDREN | WS_VISIBLE),
		pt.x,
		pt.y,
		width,
		height,
		NULL,			/*Parent window handle*/
		NULL,			/*HMENU*/
		GetModuleHandle(NULL),
		NULL);			/*Something extra info if you want to provide*/

	ghwnd = hwnd;

	ShowWindow(hwnd, SW_SHOWDEFAULT);
	SetForegroundWindow(hwnd);		// bring window on top
	SetFocus(hwnd);					// bring focus on window to accept keyboard

	return hwnd;
}

bool nativePollEvents(void)
{
	MSG msg;
	bool bDone = true;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) == TRUE)
	{// message is there 
		if (msg.message == WM_QUIT)
			bDone = false;
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	else
	{
		if (gbActiveWindow == true)
		{
			if (gbEscapeKeyPressed == true)
				bDone = false;
		}
	}

	return bDone;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//void  resize(int, int);
	void ToggleFullScreen(void);
	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			gbEscapeKeyPressed = true;
			break;
		case 0x46:
			ToggleFullScreen();
			break;
		}
		break;

	case WM_ACTIVATE:
		if (HIWORD(wParam) == 0)
			gbActiveWindow = true;
		else
			gbActiveWindow = false;
		break;
	case WM_SIZE:
		//resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_ERASEBKGND:
		return (0);
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void nativeSwapBuffers(void)
{
	if (ghdc)
		SwapBuffers(ghdc);
}

void nativeInitialize(void)
{
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;
	void nativeUninitialize(void);
	void resize(int, int);

	//code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	//01-Initialization of structure 'PIXELFORMATDESCRIPTOR'
	//Parallel to glutInitDisplayMode()
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;	// set to 1, by MSDN
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |		// buffer can draw to window surface
		PFD_SUPPORT_OPENGL |	    // buffer supports OpenGL drawing
		PFD_DOUBLEBUFFER;			// buffer is double buffer
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;	// R+G+B+A
	pfd.cRedBits = 8;		// 256 shades of Red color component
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;	// 3D change 1a(M): added this field for 3D drawing

							//02-Get/Create Device Context
	ghdc = GetDC(ghwnd);

	//03-Choose pixel format which best matches with give pfd
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{//no best match found for give pfd 
		ReleaseDC(ghwnd, ghdc);
		ghdc = 0;
		fprintf(gpLogFile, "ChoosePixelFormat():Failed. Exiting...\n");
		nativeUninitialize();
		exit(0);
	}

	//04-Set the pixel format chose above
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
		fprintf(gpLogFile, "SetPixelFormat():Failed. Exiting...\n");
		nativeUninitialize();
		exit(0);
	}

	//05-Create OpenGL Rendering Context
	ghrc = wglCreateContext(ghdc);			// this is wglXXX api, not Win32
	if (ghrc == NULL)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
		fprintf(gpLogFile, "wglCreateContext():Failed. Exiting...\n");
		nativeUninitialize();
		exit(0);
	}

	//06-Make the rendering context created above as current
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
		fprintf(gpLogFile, "wglMakeCurrent():Failed. Exiting...\n");
		nativeUninitialize();
		exit(0);
	}
	
	//resize(gWinWidth, gWinHeight);
}

void nativeUninitialize(void)
{
	if (gbFullscreen == true)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}

	//Deselect rendering context
	wglMakeCurrent(ghdc, ghrc);

	//Delete Rendoring Context
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	//Delete device context
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (gpLogFile)
	{
		fprintf(gpLogFile, "Log File is successfully closed\n");
		fclose(gpLogFile);
		gpLogFile = NULL;
	}
}

double nativeGetTime(void)
{
	LONGLONG cntPerSec = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&cntPerSec);

	return ((double)cntPerSec);
}

void ToggleFullScreen(void)
{
	// variable declarations
	MONITORINFO mi;

	//code
	if (gbFullscreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi.cbSize = sizeof(MONITORINFO);
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, (dwStyle & ~WS_OVERLAPPEDWINDOW));
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top,
					(mi.rcMonitor.right - mi.rcMonitor.left), (mi.rcMonitor.bottom - mi.rcMonitor.top),
					SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(false);
		gbFullscreen = true;
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(true);
		gbFullscreen = false;
	}
}


#if 0
void initialize(void)
{
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;
	void uninitialize(void);
	void resize(int, int);

	//code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	//01-Initialization of structure 'PIXELFORMATDESCRIPTOR'
	//Parallel to glutInitDisplayMode()
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;	// set to 1, by MSDN
	pfd.dwFlags = PFD_DRAW_TO_WINDOW |		// buffer can draw to window surface
		PFD_SUPPORT_OPENGL |	    // buffer supports OpenGL drawing
		PFD_DOUBLEBUFFER;			// buffer is double buffer
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;	// R+G+B+A
	pfd.cRedBits = 8;		// 256 shades of Red color component
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;	// 3D change 1a(M): added this field for 3D drawing

							//02-Get/Create Device Context
	ghdc = GetDC(ghwnd);

	//03-Choose pixel format which best matches with give pfd
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{//no best match found for give pfd 
		ReleaseDC(ghwnd, ghdc);
		ghdc = 0;
		fprintf(gpLogFile, "ChoosePixelFormat():Failed. Exiting...\n");
		uninitialize();
		exit(0);
	}

	//04-Set the pixel format chose above
	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
		fprintf(gpLogFile, "SetPixelFormat():Failed. Exiting...\n");
		uninitialize();
		exit(0);
	}

	//05-Create OpenGL Rendering Context
	ghrc = wglCreateContext(ghdc);			// this is wglXXX api, not Win32
	if (ghrc == NULL)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
		fprintf(gpLogFile, "wglCreateContext():Failed. Exiting...\n");
		uninitialize();
		exit(0);
	}

	//06-Make the rendering context created above as current
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
		fprintf(gpLogFile, "wglMakeCurrent():Failed. Exiting...\n");
		uninitialize();
		exit(0);
	}

	//07-GLEW Initializtion code for GLSL
	//(IMPORTANT:This call MUST be here. i.e. after creating OpenGL context but before any OpenGL function call)
	GLenum glew_error = glewInit();
	if (glew_error != GLEW_OK)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
		fprintf(gpLogFile, "glewInit():Failed. Exiting...\n");
		uninitialize();
		exit(0);
	}
	//08-Get OpenGL and GLSL version on your machine
	fprintf(gpLogFile, "OpenGL Version: %s\n", glGetString(GL_VERSION));
	fprintf(gpLogFile, "GLSL Version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	/******** VERTEX SHADER *********/
	//01-Create shader : GLuint glCreateShader( GLenum shaderType);
	/*
	shaderType: GL_VERTEX_SHADER / GL_TESS_CONTROL_SHADER / GL_TESS_EVALUATION_SHADER /
	GL_GEOMETRIC_SHADER / GL_FRAGMENT_SHADER / GL_COMPUTE_SHADER (OGL >=V4.3)
	GLuint	  : reference to empty Shader object
	*/
	gVertexShaderObject = glCreateShader(GL_VERTEX_SHADER);

	//02_a: Prepare source code to shader
	const GLchar *vertexShaderSourceCode =
		"#version 400 core" \
		"\n" \
		"in vec4 vPosition;" \
		"in vec4 vColor;" \
		"out vec4 outColor;" \
		"uniform mat4 u_mvp_matrix;" \
		"void main(void)" \
		"{" \
		"gl_Position = u_mvp_matrix * vPosition;" \
		"outColor = vColor;" \
		"}";

	//02_b: Provide source code to shader 
	/* void glShaderSource(GLuint shader, GLsizei count, const GLchar **string, const GLint *length); */
	glShaderSource(gVertexShaderObject,			/*GLuint: Handle of shader object*/
		1,										/*GLsizei: no. of elements in next argument i.e. string*/
		(const GLchar**)&vertexShaderSourceCode,/*const GLchar** : array of pointers to string containing source code*/
		NULL);									/*const Glint* : arry of string lengh*/

												//03-Compile Shader: void glCompileShader(GLuint shader);
	glCompileShader(gVertexShaderObject);
	/*Error Handling*/
	GLint iShaderCompilationStatus = 0;
	glGetShaderiv(gVertexShaderObject, GL_COMPILE_STATUS, &iShaderCompilationStatus);
	if (iShaderCompilationStatus == GL_FALSE)
	{// Get error details
		GLint iInfoLogLength = 0;
		glGetShaderiv(gVertexShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			GLchar* szInfoLog = (GLchar*)malloc(iInfoLogLength);
			if (iInfoLogLength != NULL)
			{
				GLsizei written = 0;
				glGetShaderInfoLog(gVertexShaderObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpLogFile, "Vertex Shader Info Log: %s\n", (const char*)szInfoLog);
				free(szInfoLog);
				uninitialize();
				exit(0);
			}
		}
	}

	/******** FRAGMENT SHADER *********/
	//01-Create Shader 
	/*
	shaderType: GL_VERTEX_SHADER / GL_TESS_CONTROL_SHADER / GL_TESS_EVALUATION_SHADER /
	GL_GEOMETRIC_SHADER / GL_FRAGMENT_SHADER / GL_COMPUTE_SHADER (OGL >=V4.3)
	GLuint	: reference to empty Shader object
	*/
	gFragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

	//02_a: Prepare source code for shader
	const GLchar* fragmentShaderSourceCode =
		"#version 400 core" \
		"\n" \
		"out vec4 FragColor;" \
		"in vec4 outColor;"
		"void main(void)" \
		"{" \
		"FragColor = outColor;"
		"}";

	//02_b: Provide source code to shader
	/* void glShaderSource(GLuint shader, GLsizei count, const GLchar **string, const GLint *length); */
	glShaderSource(gFragmentShaderObject, 1, (const GLchar**)&fragmentShaderSourceCode, NULL);

	//03-Compile Shader: void glCompileShader(GLuint shader);
	glCompileShader(gFragmentShaderObject);
	/*Error Handling*/
	/*void glGetShaderiv(GLuint shader, GLenum pname, GLint *params);*/
	glGetShaderiv(gFragmentShaderObject, GL_COMPILE_STATUS, &iShaderCompilationStatus);
	if (iShaderCompilationStatus == GL_FALSE)
	{// Get error details 
		GLint iInfoLogLength = 0;
		glGetShaderiv(gFragmentShaderObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			GLchar *szInfoLog = (GLchar*)malloc(iInfoLogLength);	// iInfoLogLength includes null character
			if (szInfoLog != NULL)
			{
				GLsizei written = 0;
				/*void glGetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog);*/
				glGetShaderInfoLog(gFragmentShaderObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpLogFile, "Fragment Shader Compilation Log: %s\n", (const char*)szInfoLog);
				free(szInfoLog);
				uninitialize();
				exit(0);
			}
		}
	}

	/******** SHADER PROGRAM *********/
	//01-Create Shader Program: GLuint glCreateProgram(void);
	gShaderProgramObject = glCreateProgram();

	//02: Attach shaders to shader program: void glAttachShader(GLuint program, GLuint shader);
	//02.a: Attach vertext shader
	glAttachShader(gShaderProgramObject, gVertexShaderObject);

	//02.b: Attach fragment shader
	glAttachShader(gShaderProgramObject, gFragmentShaderObject);

	//03_a: Pre-link binding of shader program object with vertex shader position attribute
	/*void glBindAttribLocation(GLuint program, GLuint index, const GLchar *name);*/
	// This binds --> variable name-to-generic attribute index for a program object
	glBindAttribLocation(gShaderProgramObject, VDG_ATTRIBUTE_POSITION, "vPosition");
	glBindAttribLocation(gShaderProgramObject, VDG_ATTRIBUTE_COLOR, "vColor");

	//03_b:Link Shader Program: void glLinkProgram(GLuint program);
	glLinkProgram(gShaderProgramObject);
	/*Error Handling*/
	GLint iShaderProgramLinkStatus = 0;
	glGetProgramiv(gShaderProgramObject, GL_LINK_STATUS, &iShaderProgramLinkStatus);
	if (iShaderProgramLinkStatus == GL_FALSE)
	{
		GLint iInfoLogLength = 0;
		glGetProgramiv(gShaderProgramObject, GL_INFO_LOG_LENGTH, &iInfoLogLength);
		if (iInfoLogLength > 0)
		{
			GLchar *szInfoLog = (GLchar*)malloc(iInfoLogLength);
			if (szInfoLog != NULL)
			{
				GLsizei written = 0;
				glGetProgramInfoLog(gShaderProgramObject, iInfoLogLength, &written, szInfoLog);
				fprintf(gpLogFile, "Shader Program Link Log: %s\n", (const char*)szInfoLog);
				free(szInfoLog);
				uninitialize();
				exit(0);
			}
		}
	}

	//Get MVP uniform location: This step MUST be done after program link
	/*GLint glGetUniformLocation(GLuint program, const GLchar *name);*/
	gMVPUniform = glGetUniformLocation(gShaderProgramObject, "u_mvp_matrix");

	/*----Vertices, Colors, Shader attribs, vbo, vao initialization--------*/
	const GLfloat pyramidVertices[] = {
		/*front tria*/
		/*0*/	0.0f, 1.0f, 0.0f,		//apex
		-1.0f, -1.0f, 1.0f,		//left-bottom
		1.0f, -1.0f, 1.0f,		//right-bottom

		/*right tria*/
		/*9*/	0.0f, 1.0f, 0.0f,		//apex
		1.0f, -1.0f, 1.0f,		//left-bottom
		1.0f, -1.0f, -1.0f,		//right-bottom

		/*back tria*/
		/*18*/	0.0f, 1.0f, 0.0f,		//apex
		1.0f, -1.0f, -1.0f,		//left-bottom
		-1.0f, -1.0f, -1.0f,	//right-bottom

		/*left tria*/
		/*27*/	0.0f, 1.0f, 0.0f,		//apex
		-1.0f, -1.0f, -1.0f,		//left-bottom
		-1.0f, -1.0f, 1.0f,	//right-bottom
	};

	const GLfloat pyramidColor[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};

	//VAO1:Tria
	//Generate vertex array object name
	/*void glGenVertexArrays(GLsizei n, GLuint *arrays);*/
	glGenVertexArrays(1, &gVao_Pyramid);
	//Bind a vertext array object: void glBindVertexArray(GLuint array);
	glBindVertexArray(gVao_Pyramid);

	//VBO1
	//Generate buffer object names: void glGenBuffers(GLsizei n, GLuint * buffers);
	glGenBuffers(1, &gVbo_position);
	//Bind a named buffer object in VRAM: void glBindBuffer(GLenum target, GLuint buffer);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_position);
	//Store data on VRAM: void glBufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);

	//Bind above generated VBO in VRAM to a number in RAM, and specifies how and where to look for position/vertex data
	/*void glVertexAttribPointer(GLuint index, GLint size, GLenum type,
	GLboolean normalized, GLsizei stride, const GLvoid * pointer);*/
	glVertexAttribPointer(VDG_ATTRIBUTE_POSITION,	// index in RAM to point VBO in VRAM
		3,			//triagnleVertices data consists of x,y,z (3 components)
		GL_FLOAT,	//triangleVertices each element is of GL_FLOAT
		GL_FALSE,	//triangleVertices data is not within -1.0f to +1.0f which means non-normalised
		0,			//to get these vertices, look at 0 offset in vbo
		NULL);

	//Enable generic vertex attribute array defined above: 
	/*void glEnableVertexAttribArray(GLuint index);*/
	glEnableVertexAttribArray(VDG_ATTRIBUTE_POSITION);

	//Unbind VBO bound above
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//VBO2
	glGenBuffers(1, &gVbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_color);

	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidColor), pyramidColor, GL_STATIC_DRAW);
	glVertexAttribPointer(VDG_ATTRIBUTE_COLOR,
		3,	// R,G,B
		GL_FLOAT,
		GL_FALSE,	//non-normalised
		0,			//stride=0, or 0 offset
		NULL);
	glEnableVertexAttribArray(VDG_ATTRIBUTE_COLOR);

	//Unbind VBO2
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Unbind VAO bound above
	glBindVertexArray(0);

	//VAO2:Quad
	const float cubeVertices[] = {
		/*front*/
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

		/*right*/
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,

		/*back*/
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,

		/*left*/
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,

		/*top*/
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		/*bottom*/
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

	};

	//per vertex
	const float cubeColor[] = {
		/*front*/1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		/*right*/0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
		/*back*/0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		/*left*/ 1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,
		/*top*/  0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f,
		/*botm*/1.0f, 0.0f, 1.0f,   1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f,
	};

	glGenVertexArrays(1, &gVao_Cube);
	glBindVertexArray(gVao_Cube);

	//VBO1
	glGenBuffers(1, &gVbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_position);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(VDG_ATTRIBUTE_POSITION, // mapped to vPosition, so above vertices data goes to vPosition
		3, //x,y,z
		GL_FLOAT,
		GL_FALSE,	//non-normalised
		0,			//no stride,
		NULL);
	glEnableVertexAttribArray(VDG_ATTRIBUTE_POSITION);

	//Cornflower blue color: rgb : 0.392157 0.584314 0.929412
	//glVertexAttrib3f(VDG_ATTRIBUTE_COLOR, 0.392157f, 0.584314f, 0.929412f);
	//VBO2
	glGenBuffers(1, &gVbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, gVbo_color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColor), cubeColor, GL_STATIC_DRAW);
	glVertexAttribPointer(VDG_ATTRIBUTE_COLOR,
		3,	//r,g,b
		GL_FLOAT,	//of type float
		GL_FALSE,	//non-normalise
		0,			//no stride
		NULL);
	glEnableVertexAttribArray(VDG_ATTRIBUTE_COLOR);

	//Unbind vao2
	glBindVertexArray(0);


	//Other OpenGL settings
	glClearDepth(1.0f);		// 3D change 1b.1(M): Full depth(far plane), added for 3D drawing 
	glEnable(GL_DEPTH_TEST);// 3D change 1b.2(M): Enable depth function
	glDepthFunc(GL_LEQUAL); // 3D change 1b.3(M): draw objects from far plane, less than or equal distance from far to near

	glShadeModel(GL_SMOOTH);// 3D change 1b.4(O): to avoid aliasing, to avoid jaggery effect  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// 3D change 1b.5(O): to avoid distortion
													  //Comment following as we are doing rotation, so that back side will be rendored
													  //glEnable(GL_CULL_FACE);	// We will always cull back faces for better performance

													  //First OpenGL call, set backgroud clearing color to blue
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//black


											//Set Orthographic Projection matrix to Identity matrix
	gPerspectiveProjectionMatrix = mat4::identity();
	resize(WIN_WIDTH, WIN_HEIGHT);
}/*void initialize(void)*/

void resize(int width, int height)
{
	if (height == 0)
		height = 1;
	if (width == 0)
		width = 0;

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);	//Window to viewport mapping

														//Parallel FFP --> glOrtho(left,right,bottom,top,near,far)
	if (width <= height)
		gPerspectiveProjectionMatrix = perspective(45.0f, ((float)height / (float)width), 0.1f, 1000.0f);
	else
		gPerspectiveProjectionMatrix = perspective(45.0f, ((float)width / (float)height), 0.1f, 1000.0f);
}/*void resize(int,int)*/

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 3D change 2(M) : added GL_DEPTH_BUFFER_BIT,	to clear depth matrix

														//Start using OpenGL program object: void glUseProgram(GLuint program);
														//Installs a program object as part of current state of rendering state
	glUseProgram(gShaderProgramObject);

	/*OpenGL Drawing*/
	//01-Set ModelVeiw and ModelViewProjection matrices to identity
	mat4 modelViewMatrix = mat4::identity();
	mat4 modelViewProjectionMatrix = mat4::identity();
	mat4 rotationMatrix = mat4::identity();

	//02_a: Translate MV matrix to deep inside along z axix as we are in Perspective projection
	modelViewMatrix = translate(-1.5f, 0.0f, -6.0f);
	//02_b: rotate 
	rotationMatrix = rotate(g_anglePyramid, 0.0f, 1.0f, 0.0f);
	//02_c: Mutliply MV*RotateMAT
	modelViewMatrix = modelViewMatrix * rotationMatrix;

	//02-Multiply MV and Ortho matrix to get MVP(ModelViewProjection) matrix: Multiply ORDER IS IMP
	modelViewProjectionMatrix = gPerspectiveProjectionMatrix * modelViewMatrix;

	//03-Pass above MVP matrix to vertex shader in 'u_mvp_matrix' shader variable whose
	// position value is already calculated in initWithFrame() by using glGetUniformLocation();
	glUniformMatrix4fv(gMVPUniform, 1, GL_FALSE, modelViewProjectionMatrix);

	//04- Bind Vao
	glBindVertexArray(gVao_Pyramid);

	//05- Draw either by glDrawTriagnles(), glDrawArrays(), glDrawElements()
	//0: Starting index of enabled array, 12:no. of indices to be rendered vertices in Vertices array
	glDrawArrays(GL_TRIANGLE_FAN, 0, 12);	// 4*3 = 4 triangles drawn 

											//06-Unbind vao
	glBindVertexArray(0);

	//VAO2 drawing: CUBE
	modelViewMatrix = mat4::identity();
	modelViewProjectionMatrix = mat4::identity();
	rotationMatrix = mat4::identity();

	//translate MV cube right by 1.5f and deep inside -6.0f
	modelViewMatrix = translate(+1.5f, 0.0f, -6.0f);

	//scale MV
	modelViewMatrix = modelViewMatrix * scale(0.7f, 0.7f, 0.7f);

	//all axix rotate MV quad
	rotationMatrix = rotate(g_angleCube, 1.0f, 0.0f, 0.0f);
	rotationMatrix = rotationMatrix * rotate(g_angleCube, 0.0f, 1.0f, 0.0f);
	rotationMatrix = rotationMatrix * rotate(g_angleCube, 0.0f, 0.0f, 1.0f);
	//Multiply MV = MV*RotateMat
	modelViewMatrix = modelViewMatrix * rotationMatrix;

	//MVP = P*MV  --> Multiplication ORDER is important
	modelViewProjectionMatrix = gPerspectiveProjectionMatrix * modelViewMatrix;
	//pass MVP matrix to shader variable 'u_mvp_matrix'
	glUniformMatrix4fv(gMVPUniform, 1, GL_FALSE, modelViewProjectionMatrix);

	//Bind vao2
	glBindVertexArray(gVao_Cube);

	//Draw
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);	//4: two triangles from T1(1,2,3) and T2(2,3,4) vertices
	glDrawArrays(GL_TRIANGLE_FAN, 4, 4);	//4: two triangles from T1(1,2,3) and T2(2,3,4) vertices
	glDrawArrays(GL_TRIANGLE_FAN, 8, 4);	//4: two triangles from T1(1,2,3) and T2(2,3,4) vertices
	glDrawArrays(GL_TRIANGLE_FAN, 12, 4);	//4: two triangles from T1(1,2,3) and T2(2,3,4) vertices
	glDrawArrays(GL_TRIANGLE_FAN, 16, 4);	//4: two triangles from T1(1,2,3) and T2(2,3,4) vertices
	glDrawArrays(GL_TRIANGLE_FAN, 20, 4);	//4: two triangles from T1(1,2,3) and T2(2,3,4) vertices

											//unbind VAO2
	glBindVertexArray(0);
	//Stop using OpenGL program object: void glUseProgram(GLuint program);
	glUseProgram(0);

	SwapBuffers(ghdc);
}/*void display(void)*/

void spin(void)
{
	g_anglePyramid = g_anglePyramid + 0.1f;
	if (g_anglePyramid >= 360.0f)
		g_anglePyramid = 0.0f;

	g_angleCube = g_angleCube + 0.1f;
	if (g_angleCube >= 360.0f)
		g_angleCube = 0.0f;
}/*spin*/

void uninitialize(void)
{
	if (gbFullscreen == true)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);
		ShowCursor(TRUE);
	}

	//Release/destroy vao
	if (gVao_Pyramid)
		glDeleteVertexArrays(1, &gVao_Pyramid);

	if (gVao_Cube)
		glDeleteVertexArrays(1, &gVao_Cube);

	//Release vbo
	if (gVbo_position)
		glDeleteBuffers(1, &gVbo_position);

	if (gVbo_color)
		glDeleteBuffers(1, &gVbo_color);

	//void glDetachShader(GLuint program, GLuint shader);
	//Detach vertex shader from shader program object
	glDetachShader(gShaderProgramObject, gVertexShaderObject);

	//Detach fragment shader from shader program object
	glDetachShader(gShaderProgramObject, gFragmentShaderObject);

	//Delete vertex shader object and make it zero
	glDeleteShader(gVertexShaderObject);
	gVertexShaderObject = 0;

	//Delete fragment shader object
	glDeleteShader(gFragmentShaderObject);
	gFragmentShaderObject = 0;

	//Delete shader program object: void glDeleteProgram(GLuint program);
	glDeleteProgram(gShaderProgramObject);
	gShaderProgramObject = 0;

	//Unlink shader program
	glUseProgram(0);


	//Deselect rendering context
	wglMakeCurrent(ghdc, ghrc);

	//Delete Rendoring Context
	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	//Delete device context
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (gpLogFile)
	{
		fprintf(gpLogFile, "Log File is successfully closed\n");
		fclose(gpLogFile);
		gpLogFile = NULL;
	}
}/*void uninitialize(void)*/
#endif 