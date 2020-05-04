#pragma once

namespace saofb::core
{
	enum class static_address : size_t
	{
		test = 0xDEADC0DE,
		gworld = 0x144C93C98,
		gobject_count = 0x144B7ED7C,
		gnames =  0x144B763F8,  // 0x4B763F8
		gobject = 0x144B7ED70, // 0x4B7ED70
	};
}