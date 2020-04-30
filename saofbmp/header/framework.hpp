#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tlhelp32.h>

#include <memory>
#include <filesystem>

namespace std
{
#ifdef _UNICODE
	using tstring_view = wstring_view;
#else
	using tstring_view = string_view;
#endif
}

#define CREATE_THREAD_ACCESS (PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ)