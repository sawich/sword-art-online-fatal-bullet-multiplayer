#pragma once

#include "character.hpp"

namespace saofb
{
	class world
	{
	public:
		char pad_0000[360]; //0x0000
		class character* character; //0x0168
		char pad_0170[16]; //0x0170
	}; //Size: 0x0180
	static_assert(sizeof(world) == 0x180);
}