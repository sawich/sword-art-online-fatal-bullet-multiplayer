#pragma once

#include "../framework.hpp"
#include "process.hpp"

namespace hentai
{
	class virtual_alloc_ex
	{
	public:
		operator bool(void) const noexcept { return nullptr != m_value; }
		operator LPVOID(void) const noexcept { return m_value; }

		bool write(LPCVOID buffer, SIZE_T size) const noexcept
		{
			return WriteProcessMemory(*m_process, m_value, buffer, size, NULL);
		}

		virtual_alloc_ex(const shared_process_t process, const std::tstring_view path) noexcept
			: m_process{ process }
			, m_value{
				VirtualAllocEx(
					*process, nullptr, 
					std::size(path) * sizeof(std::tstring_view::value_type), 
					MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE) }
		{}

		~virtual_alloc_ex(void) noexcept 
		{
			if (nullptr != m_value) { VirtualFreeEx(*m_process, m_value, 0, MEM_RELEASE); }
		}

		virtual_alloc_ex(virtual_alloc_ex&& o) noexcept : m_value{ std::exchange(o.m_value, nullptr) } {}
		virtual_alloc_ex& operator=(virtual_alloc_ex&& o) noexcept
		{
			m_value = std::exchange(o.m_value, nullptr);
			return *this;
		}
	private:
		shared_process_t m_process;
		LPVOID m_value{ nullptr };

		virtual_alloc_ex(const virtual_alloc_ex&) = delete;
		virtual_alloc_ex& operator=(virtual_alloc_ex&) = delete;
	};
}