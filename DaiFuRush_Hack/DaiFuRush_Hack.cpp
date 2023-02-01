// DaiFuRush_Hack.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "lib.h"
#include <string>
int main()
{
	std::string func_list[6] = {
		"无限子弹","RPG","无敌","踏空跳","超级穿透","秒杀"
	};
	std::string on_list[6] = {
		"关闭","关闭","关闭","关闭","关闭","关闭"
	};
	int length = sizeof(func_list) / sizeof(func_list[0]);
	std::wstring game_name = L"DaifuRushByMutangM.exe";
	DWORD game_id = FindProcessId(game_name);
	HANDLE game_handle= getProcessHandle(game_id);
	uintptr_t modBaseAddres = GetModuleBaseAddress(game_id, L"mono-2.0-bdwgc.dll");
	exit(0);
	Gui(func_list, on_list, length);


	RegisterHotKey(GetActiveWindow(), 0, 0, VK_F1); //无限子弹
	RegisterHotKey(GetActiveWindow(), 1, 0, VK_F2); //RPG
	RegisterHotKey(GetActiveWindow(), 2, 0, VK_F3); //无敌
	RegisterHotKey(GetActiveWindow(), 3, 0, VK_F4); //踏空
	RegisterHotKey(GetActiveWindow(), 4, 0, VK_F5); //超级穿透
	RegisterHotKey(GetActiveWindow(), 5, 0, VK_F6); //秒杀
	RegisterHotKey(GetActiveWindow(), 6, 0, VK_F7); //退出
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0)) {
		switch (msg.message)
		{
		case WM_HOTKEY:
		{
			if (msg.wParam == 0)
			{
				// "mono-2.0-bdwgc.dll"+007C2C08 198 4c0 38 20 9c
			}
			//198 4c0 39 20 7c
			//198 4c0 30 20 110 55
			//198 4c0 30 20 168
			//198 4c0 38 20 8c
			//198 4c0 38 20 84

			if (msg.wParam == 6)
			{
				UnregisterHotKey(GetActiveWindow(), 0);
				UnregisterHotKey(GetActiveWindow(), 1);
				UnregisterHotKey(GetActiveWindow(), 2);
				UnregisterHotKey(GetActiveWindow(), 3);
				UnregisterHotKey(GetActiveWindow(), 4);
				UnregisterHotKey(GetActiveWindow(), 5);
				UnregisterHotKey(GetActiveWindow(), 6);
				exit(0);
			}
		}
		default:
			break;
		}
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
