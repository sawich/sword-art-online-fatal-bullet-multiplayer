#pragma once

#include "../framework.hpp"
#include "virtual_alloc_ex.hpp"
#include "process.hpp"

namespace hentai
{
	class injector
	{
	public:
		static void use(_In_ const shared_process_t& process, _In_ const std::tstring_view path) noexcept
		{
			const auto absolute_path{ std::filesystem::absolute(path).wstring() };

			virtual_alloc_ex memory{ process, absolute_path };
			memory.write(
				reinterpret_cast<LPVOID>(const_cast<std::tstring_view::value_type*>(std::data(absolute_path))),
				std::size(absolute_path) * sizeof(std::tstring_view::value_type));

			const auto LoadLibraryPtr{ GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryW") };
			const auto thread{ CreateRemoteThread(
				*process, nullptr, 0, 
				reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryPtr), 
				memory, NULL, nullptr) };

			WaitForSingleObject(thread, INFINITE);
		}

	private:
		injector(void) noexcept = delete;
		~injector(void) noexcept = delete;
	};
}