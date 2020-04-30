#pragma once

#include "../framework.hpp"
#include "process.hpp"
#include <iostream>

namespace hentai
{
	class snapshot
	{
	public:
		operator bool(void) const noexcept { return INVALID_HANDLE_VALUE != m_value; }
		operator HANDLE(void) const noexcept { return m_value; }

		snapshot(const DWORD flags = TH32CS_SNAPPROCESS) noexcept
			: m_value{ CreateToolhelp32Snapshot(flags, 0)}
		{}

		~snapshot(void) noexcept 
		{
			if (INVALID_HANDLE_VALUE != m_value && NULL != m_value) { CloseHandle(m_value); }
		}

		static DWORD find_process_id_by_name(_In_ const std::wstring_view name) noexcept
		{
			const snapshot snap;
			PROCESSENTRY32 pe{ .dwSize = sizeof(PROCESSENTRY32) };
			Process32First(snap, &pe);
			do {
				if (name == pe.szExeFile) {
					std::wcout << pe.szExeFile << '\n';
					return pe.th32ProcessID;
				}
			} while (Process32Next(snap, &pe));
			return 0;
		}

		snapshot(snapshot&& o) noexcept : m_value{ std::exchange(o.m_value, INVALID_HANDLE_VALUE) } {}
		snapshot& operator=(snapshot&& o) noexcept
		{
			m_value = std::exchange(o.m_value, INVALID_HANDLE_VALUE);
			return *this;
		}
	private:
		HANDLE m_value{ INVALID_HANDLE_VALUE };

		snapshot(const snapshot&) = delete;
		snapshot& operator=(snapshot&) = delete;
	};
}