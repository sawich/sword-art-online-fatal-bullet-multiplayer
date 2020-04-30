#pragma once

#include "../framework.hpp"
#include "snapshot.hpp"

namespace hentai
{
	class process;
	using shared_process_t = std::shared_ptr<process>;

	class process
	{
	public:
		operator bool(void) const noexcept{ return INVALID_HANDLE_VALUE != m_value; }
		operator HANDLE(void) const noexcept { return m_value; }

		static process open(_In_ const std::wstring_view name) noexcept 
		{
			return{ snapshot::find_process_id_by_name(name) };
		}

		static shared_process_t open_shared(_In_ const std::wstring_view name) noexcept
		{
			return std::make_shared<process>(std::forward<process>(open(name)));
		}

		~process(void) noexcept 
		{ 
			if (INVALID_HANDLE_VALUE != m_value) { CloseHandle(m_value); }
		}

		process(process&& o) noexcept : m_value{ std::exchange(o.m_value, INVALID_HANDLE_VALUE) } {}
		process& operator=(process&& o) noexcept
		{
			m_value = std::exchange(o.m_value, INVALID_HANDLE_VALUE);
			return *this;
		}

	private:
		HANDLE m_value{ INVALID_HANDLE_VALUE };

		process(const DWORD value) noexcept 
			: m_value{ OpenProcess(CREATE_THREAD_ACCESS, FALSE, value) } 
		{}

		process(const process&) = delete;
		process& operator=(process&) = delete;
	};
}