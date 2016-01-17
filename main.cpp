
#include <iostream>
#include <windows.h>
#include "public\common\sys.h"
#include "OtherTask\OtherTask.h"
#include "Gui\EditorMain.h"
using namespace std;

#define DEBUG   1
#define EDITOR  1


int main(int argc, char *argv[])
{
	SetProgramName(argv[0]);

#ifdef DEBUG
	AllocConsole();    //为进程创造一个新的控制台
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

#if(EDITOR == 1)
	RunEditor(argc, argv);
#else
	RunTask();
#endif

#ifdef DEBUG
	FreeConsole();
#endif
	return 0;
}

