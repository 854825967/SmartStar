#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);// ³õÊ¼»¯Windows Socket 2.2

    HANDLE hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
    COORD size = {120, 50};
    SetConsoleScreenBufferSize(hConsole, size);
    SMALL_RECT rc = {0, 0, 119, 49};
    SetConsoleWindowInfo(hConsole, true, &rc);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
