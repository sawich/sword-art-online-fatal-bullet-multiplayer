#pragma once

#include "../../framework.hpp"

namespace hentai::utility
{
	template <typename T>
	std::tstring to_hex(T&& arg) noexcept
	{
		std::tstringstream stream;
		stream << TEXT("0x")
			<< std::setfill(TEXT('0')) 
			<< std::setw(sizeof(T) * 2)
			<< std::hex 
			<< arg;
		return stream.str();
	}
}