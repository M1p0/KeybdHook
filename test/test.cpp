#include <Windows.h>
#include <iostream>
using namespace std;

HHOOK keyboardHook = 0;

LRESULT CALLBACK HookCallback(int code, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT *ks = (KBDLLHOOKSTRUCT*)lParam;

    if (wParam == WM_KEYDOWN && ks->vkCode == 'G')   //G�������� �������޸�
    {
        cout << "������G��" << endl;
        keybd_event(67, 0, 0, 0);
        keybd_event(VK_SPACE, 0, 0, 0);
        keybd_event(67, 0, KEYEVENTF_KEYUP, 0);
        keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
        return 1;
    }
    return CallNextHookEx(0, code, wParam, lParam);
}


//LRESULT CALLBACK HookCallback(int code, WPARAM wParam, LPARAM lParam)
//{
//
//    return 1;
//}


int main()
{
    keyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, HookCallback, GetModuleHandleA(0), 0);

    cout << "������������" << endl;
    cout << "�رճ����Իָ�����" << endl;

    //����©����Ϣ������Ȼ����Ῠ��
    MSG msg;
    while (1)
    {
        if (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE))
        {

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        } 
        else
            Sleep(1);    //避免CPU全负载运�?
    }
    UnhookWindowsHookEx(keyboardHook);
    cout << "���������˳�" << endl;

    return 0;
}

