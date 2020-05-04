#pragma once

#include "../framework.hpp"
#include "../saofb/application.hpp"
#include "../saofb/game.hpp"
#include "../ue.hpp"
#include "utility/console.hpp"

namespace hentai
{
	class client
	{
	public:
		static auto get_instance(void) noexcept { return m_instance.get(); }

		static void attach(HMODULE module) noexcept
		{
			assert(!m_instance);
			m_instance = std::make_unique<hentai::client>(module);
		}

		static void detach(void) noexcept 
		{
			assert(m_instance);
			m_instance.reset();
		}

		client(const HMODULE module) noexcept : m_module{ module }
		{
			ue::attach();

			/*const auto base{ reinterpret_cast<uintptr_t>(GetModuleHandle(NULL)) };
			std::tstring msg;
			msg += TEXT("base: ");
			msg += hentai::utility::to_hex(base);

			saofb::application* a = reinterpret_cast<saofb::application*>(reinterpret_cast<uintptr_t*>(*(reinterpret_cast<uintptr_t*>(base + 0x04C100D8))));
			saofb::game* c = a->game;
			msg += TEXT(" / position: [x:");
			msg += std::to_tstring(c->world->character->position.x);
			msg += TEXT("/");
			msg += std::to_tstring(c->world->character->position.y);
			msg += TEXT("/");
			msg += std::to_tstring(c->world->character->position.z);
			msg += TEXT("]");

			MessageBox(0, std::data(msg), 0, 0);*/
		}

		~client(void) noexcept
		{
			ue::detach();
		}

	private:
		using client_t = std::unique_ptr<client>;
		static client_t m_instance;

		utility::console m_console;
		HMODULE m_module;
	};

	client::client_t client::m_instance;
}