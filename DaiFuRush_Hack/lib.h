#pragma once

#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <string>
#include <vector>
DWORD FindProcessId(const std::wstring& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}

HANDLE getProcessHandle(DWORD pid) {
	return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
}

template <typename var>
bool WriteMem(HANDLE processHandle,uintptr_t address,var value) {
	return WriteProcessMemory(processHandle, (LPVOID)address, &value, sizeof(var), NULL);
}

template <typename var>
var ReadMem(HANDLE processHandle,uintptr_t address,var defaultValue) {
	var value;
	ReadProcessMemory(processHandle, (LPCVOID)address, &value, sizeof(var), NULL);
	return value;
}

uintptr_t FindPointer(HANDLE processHandle,uintptr_t moduleBaseAddress, int offset_num, uintptr_t offsets[])
{
	if (offset_num <= 0) {
		return NULL;
	}

	int64_t Address = moduleBaseAddress + offsets[0];
	Address = ReadMem<int64_t>(processHandle,Address, 0);
	//ReadProcessMemory(processHandle, (LPCVOID)Address, &Address, sizeof(DWORD), NULL);

	if (Address == 0) {
		return NULL;
	}

	for (int i = 1; i < offset_num; i++) //Loop trough the offsets
	{
		Address += offsets[i];
		Address = ReadMem<int64_t>(processHandle,Address, 0);
		//ReadProcessMemory(processHandle, (LPCVOID)Address, &Address, sizeof(DWORD), NULL);
		if (Address == 0) {
			return NULL;
		}
	}
	return Address;
}


uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			//std::cout << std::hex << (uintptr_t)modEntry.modBaseAddr << std::endl;
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}

void Gui(std::string a[],std::string b[],int length) {
	system("cls");
	for (size_t i = 0; i < length; i++)
	{
		std::cout << "F" << i+1  << " " << a[i] << " " << b[i] << std::endl;
	}
	std::cout << "F7 退出" << std::endl;
}
