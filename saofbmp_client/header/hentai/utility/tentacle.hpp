#pragma once

#include "../../framework.hpp"
#include "../../saofb/core/static_address.hpp"

#ifdef cdecl
#undef cdecl
#endif

namespace hentai::utility
{
	enum class calling_convention 
	{
		/** __cdecl **/
		cde,

		/** __stdcall **/
		std,

		/** __thiscall **/
		ths 
	};

	class tentacle
	{
	public:
		template <
			uintptr_t Address, 
			typename ReturnType, 
			calling_convention CallingConvension, 
			typename ...Args
		>
		static ReturnType call(Args&&... args) noexcept 
		{
			if constexpr (calling_convention::cl == CallingConvension) {
				return reinterpret_cast<ReturnType(__cdecl*)(Args...)>(Address)(args...);
			} else if constexpr (calling_convention::std == CallingConvension) {
				return reinterpret_cast<ReturnType(__stdcall*)(Args...)>(Address)(args...);
			} else if constexpr (calling_convention::ths == CallingConvension) {
				return reinterpret_cast<ReturnType(__thiscall*)(Args...)>(Address)(args...);
			} else {
				static_assert(false, "watafuk");
			}
		}

	private:
		tentacle(void) noexcept = delete;
		~tentacle(void) noexcept = delete;
	};
}