#include <Windows.h>
#include <iostream>
using namespace std;

HHOOK keyboardHook = 0;



LRESULT CALLBACK HookCallback(int code, WPARAM wParam, LPARAM lParam)
{

    return 1;
}


int main()
{
    keyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, HookCallback, GetModuleHandleA(0), 0);

    cout << "程序正常运行" << endl;
    cout << "关闭程序以恢复键盘" << endl;

    //不可漏掉消息处理，不然程序会卡死
    MSG msg;
    while (1)
    {
        if (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
        {

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        } 
        else
            Sleep(1);   //避免CPU全负载运行
    }
    UnhookWindowsHookEx(keyboardHook);
    cout << "程序正常退出" << endl;

    return 0;
}

