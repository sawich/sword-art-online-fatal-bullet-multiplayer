#pragma once

#include "../../framework.hpp"

namespace hentai::utility
{
	class console
	{
	public:
		console(void) noexcept
		{
			AllocConsole();
			m_conout = freopen("CONOUT$", "w", stdout);
		}

		~console(void) noexcept
		{
			fclose(m_conout);
			FreeConsole();
		}

	private:
		FILE* m_conout{ nullptr };
	};
}