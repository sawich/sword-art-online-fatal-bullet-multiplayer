#pragma once

#include "core/math/vector3.hpp"

namespace saofb
{
	class character
	{
	public:
		char pad_0000[640]; //0x0000
		core::math::vec3 position; //0x0280
		char pad_028C[256]; //0x028C
	}; //Size: 0x038C
	static_assert(sizeof(character) == 0x38C);
}