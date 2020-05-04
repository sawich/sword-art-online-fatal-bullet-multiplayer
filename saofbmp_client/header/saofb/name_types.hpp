#pragma once

#include "../hentai/utility/tentacle.hpp"

class f_string
{

};

class name_types
{
	void to_string(f_string& out) noexcept { 
		hentai::utility::tentacle::call<0x1410716A0, void, hentai::utility::calling_convention::ths> (out);
	}
private:
	name_types()
	{
	}

	~name_types()
	{
	}
};
