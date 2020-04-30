#pragma once

#include "world.hpp"

namespace saofb
{
	class game
	{
	public:
		char pad_0000[88]; //0x0000
		class world* world; //0x0058
		char pad_0060[32]; //0x0060
	}; //Size: 0x0080
	static_assert(sizeof(game) == 0x80);
}