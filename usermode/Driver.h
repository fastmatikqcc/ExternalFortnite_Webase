#pragma once
#include <Windows.h>
#include <iostream>
#include <random>
#include <dwmapi.h>
#include <TlHelp32.h>

#define dtbfix_code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x12AC, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define rw_code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x13AC, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define base_code CTL_CODE(FILE_DEVICE_UNKNOWN, 0x14AC, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_move_mouse CTL_CODE(FILE_DEVICE_UNKNOWN, 0x15AC, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)
#define code_hide_process CTL_CODE(FILE_DEVICE_UNKNOWN, 0x16AC, METHOD_BUFFERED, FILE_SPECIAL_ACCESS)

typedef struct _rw {
	INT32 process_id;
	ULONGLONG address;
	ULONGLONG buffer;
	ULONGLONG size;
	BOOLEAN write;
} rw, * prw;

typedef struct _ba {
	INT32 process_id;
	ULONGLONG* address;
} ba, * pba;
typedef struct _dtb {
	INT32 process_id;
	bool* operation;
} dtb, * dtbl;
typedef struct _ga {
	ULONGLONG* address;
} ga, * pga;

struct _alloc_mem {
	ULONGLONG* address;
	SIZE_T size;
	DWORD process_id;
};

typedef struct _NF_MOUSE_REQUEST
{
	long x;
	long y;
	unsigned short button_flags;
}NF_MOUSE_REQUEST, * PNF_MOUSE_REQUEST;

typedef struct SMoveMouse
{
	long X;
	long Y;
	unsigned short ButtonFlags;
} MoveMouse, * PMoveMouse;

typedef struct _hf {
	INT32 process_id;
} hidefile, * HideFileStruct;

inline HANDLE driver_handle;
inline INT32 process_id;

struct MyStr32
{
	char readstr[32];
};
struct MyStr64
{
	char readstr[64];
};

namespace kraft {
	bool GET_DRIVER();
	void read_physical(PVOID address, PVOID buffer, DWORD size);
	void write_physical(PVOID address, PVOID buffer, DWORD size);
	uintptr_t GET_BASE_ADDRESS();
	INT32 GET_PROCESS(LPCTSTR process_name);
	bool GET_CR3();
	void HideProcess(int PID);
	void mouse_event(long x, long y);
	bool is_valid(const uint64_t adress);
	void ReadString64(uintptr_t address, char* buffer, size_t size);
	std::string ReadString32(uint64_t address);
}

template <typename T>
T write(uint64_t address, T buffer) {

	kraft::write_physical((PVOID)address, &buffer, sizeof(T));
	return buffer;
}

template <typename T>
T read(uint64_t address) {
	T buffer{ };
	kraft::read_physical((PVOID)address, &buffer, sizeof(T));
	return buffer;
}

template <typename T>
bool ReadMemory(uint64_t address, T* buffer, size_t size) {
	if (!address || !buffer || size == 0) {
		return false;  // Validate inputs
	}

	kraft::read_physical((PVOID)address, buffer, size);
	return true;  // Return true if read is successful
}

template <typename T>
std::vector<T> batch_read(const std::vector<uint64_t>& addresses) {
	size_t num_addresses = addresses.size();
	std::vector<T> results(num_addresses);
	std::vector<uint8_t> buffer(num_addresses * sizeof(T));

	for (size_t i = 0; i < num_addresses; ++i) {
		kraft::read_physical((PVOID)addresses[i], buffer.data() + i * sizeof(T), sizeof(T));
	}

	for (size_t i = 0; i < num_addresses; ++i) {
		results[i] = *reinterpret_cast<T*>(buffer.data() + i * sizeof(T));
	}

	return results;
}