#pragma once

#include "f_name_entry.hpp"
#include "t_static_indirect_array_thread_safe_read.hpp"

namespace uef
{
	using t_name_entry_array = t_static_indirect_array_thread_safe_read<
		f_name_entry,

		/** 2M unique FNames **/
		2 * 1024 * 1024,

		/** allocated in 64K/128K chunks **/
		16384>;
}