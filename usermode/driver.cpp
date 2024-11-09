#include <Windows.h>
#include <iostream>
#include <random>
#include <dwmapi.h>
#include <TlHelp32.h>
#include <intrin.h>
#include "driver.h"
#include "module_spoofing.h"

	bool kraft::GET_DRIVER() {

		int	id[4];
		__cpuid(id, 1);
		wchar_t buffer[1];

		wsprintfW(buffer, L"\\\\.\\\%08X", id[0]);

		driver_handle = CreateFileW(buffer, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

		if (!driver_handle || (driver_handle == INVALID_HANDLE_VALUE))
			return false;

		return true;
	}

	void kraft::read_physical(PVOID address, PVOID buffer, DWORD size) {
		_rw arguments = { 0 };

		//arguments.security = code_security;
		arguments.address = (ULONGLONG)address;
		arguments.buffer = (ULONGLONG)buffer;
		arguments.size = size;
		arguments.process_id = process_id;
		arguments.write = FALSE;

		Spoofed_DeviceIoControl(driver_handle, rw_code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

	inline bool read1(const std::uintptr_t address, void* buffer, const std::size_t size)
	{
		if (buffer == nullptr || size == 0) {
			return false;
		}
		kraft::read_physical(reinterpret_cast<PVOID>(address), buffer, static_cast<DWORD>(size));
	}

	void kraft::write_physical(PVOID address, PVOID buffer, DWORD size) {
		_rw arguments = { 0 };

		arguments.address = (ULONGLONG)address;
		arguments.buffer = (ULONGLONG)buffer;
		arguments.size = size;
		arguments.process_id = process_id;
		arguments.write = TRUE;

		Spoofed_DeviceIoControl(driver_handle, rw_code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);
	}

	uintptr_t kraft::GET_BASE_ADDRESS() {
		uintptr_t image_address = { NULL };
		_ba arguments = { NULL };

		arguments.process_id = process_id;
		arguments.address = (ULONGLONG*)&image_address;

		Spoofed_DeviceIoControl(driver_handle, base_code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);

		return image_address;
	}
	INT32 kraft::GET_PROCESS(LPCTSTR process_name) {
		PROCESSENTRY32 pt;
		HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		pt.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hsnap, &pt)) {
			do {
				if (!lstrcmpi(pt.szExeFile, process_name)) {
					CloseHandle(hsnap);
					process_id = pt.th32ProcessID;
					return pt.th32ProcessID;
				}
			} while (Process32Next(hsnap, &pt));
		}
		CloseHandle(hsnap);

		return { NULL };
	}

bool IsProcessRunning(LPCTSTR process_name) {
	PROCESSENTRY32 pt;
	HANDLE hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	pt.dwSize = sizeof(PROCESSENTRY32);


	if (Process32First(hsnap, &pt)) {
		do {
			if (lstrcmpi(pt.szExeFile, process_name) == 0) {
				CloseHandle(hsnap);
				return true;
			}
		} while (Process32Next(hsnap, &pt));
	}

	CloseHandle(hsnap);
	return false;
}

bool kraft::GET_CR3() {
	bool ret = false;
	_dtb arguments = { 0 };
	arguments.process_id = process_id;
	arguments.operation = (bool*)&ret;
	Spoofed_DeviceIoControl(driver_handle, dtbfix_code, &arguments, sizeof(arguments), nullptr, NULL, NULL, NULL);

	return ret;
}

std::string kraft::ReadString32(uint64_t address)
{
	std::string str = read<MyStr32>(address).readstr;
	return str;
}

void kraft::ReadString64(uintptr_t address, char* buffer, size_t size) {
	MyStr64 data = read<MyStr64>(address);

	// Copy the readstr content into the provided buffer
	strncpy(buffer, data.readstr, size);
	buffer[size - 1] = '\0';  // Null-terminate the string
}

bool kraft::is_valid(const uint64_t adress)
{
	if (adress <= 0x400000 || adress == 0xCCCCCCCCCCCCCCCC || reinterpret_cast<void*>(adress) == nullptr || adress >
		0x7FFFFFFFFFFFFFFF) {
		return false;
	}
	return true;
}

void kraft::mouse_event(long x, long y)
{
	ULONG bytes;
	NF_MOUSE_REQUEST mouse_request = { 0 };
	mouse_request.x = x;
	mouse_request.y = y;
	//mouse_request.button_flags = button_flags;
	DeviceIoControl(driver_handle, code_move_mouse, &mouse_request, sizeof(mouse_request), &mouse_request, sizeof(mouse_request), &bytes, 0);
}

void kraft::HideProcess(int PID)
{
	hidefile Arguments{ NULL };
	Arguments.process_id = PID;
	DeviceIoControl(driver_handle, code_hide_process, &Arguments, sizeof(Arguments), nullptr, NULL, NULL, NULL);
}