#pragma once

#include "../framework.hpp"
#include "../saofb/application.hpp"
#include "../saofb/game.hpp"
#include "utility/to_hex.hpp"
#include "net.hpp"

namespace hentai
{
	class client
	{
	public:
		client(void) noexcept //: m_net{ "127.0.0.1", 5123 }
		{
			const auto base{ reinterpret_cast<uintptr_t>(GetModuleHandle(NULL)) };
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

			MessageBox(0, std::data(msg), 0, 0);
		}

		~client(void) noexcept {}

		static void attach(void) noexcept 
		{
			assert(!instance);
			instance = std::make_unique<hentai::client>();
		}

		static void detach(void) noexcept 
		{
			assert(instance);
			instance.reset();
		}

	private:
		using client_t = std::unique_ptr <client>;
		static client_t instance;

		//net m_net;
	};

	client::client_t client::instance;
}