#include "../header/hentai/client.hpp"
#include "../header/euf/u_object.hpp"
#include "../header/ue.hpp"

namespace lists
{
  void print_names(void) noexcept
  {
    const auto names{ ue::get_instance()->get_names() };
    for (int32_t i{ 0 }; i < names->num(); ++i)
    {
      const auto item{ names->get_by_id(i) };
      if (!item) { continue; }

      std::cout
        << "Name["
        << std::setw(6)
        << std::setfill('0')
        << i
        << "] "
        << item->get_ansi_name()
        << '\n';
    }
  }

  void print_objects(void) noexcept
  {
    const auto get_name{ [](const uef::u_object* object) noexcept
    {
      auto comparison_index{ object->get_f_name().comparison_index };
      if (!ue::get_instance()->get_names()->is_valid_index(comparison_index)) {
        return "invalid name index";
      }

      return ue::get_instance()->get_names()->get_by_id(comparison_index)->get_ansi_name();
    }};

    auto objects{ ue::get_instance()->get_objects()->m_objects };
    const auto digits{ static_cast<int32_t>(std::log10(objects.num())) };

    for (int32_t i{ 0 }; i < objects.num(); ++i)
    {
      auto object{ objects.get_object_ptr(i)->m_object };
      if (!object) { continue; }

      std::cout
        << "UObject["
        << std::setw(digits)
        << std::setfill('0')
        << std::dec
        << i
        << "][0x"
        << std::setw(std::numeric_limits<uintptr_t>::digits10)
        << std::setfill('0')
        << std::hex
        << reinterpret_cast<uintptr_t>(object)
        << "] "
        << get_name(object)
        << '\n';
    }
  }
}

DWORD onAttach(const LPVOID lpThreadParameter) noexcept
{
  const HMODULE module{ *static_cast<const HMODULE*>(lpThreadParameter) };
  hentai::client::attach(module);

  //lists::print_names();
  //lists::print_objects();

  return EXIT_SUCCESS;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) noexcept
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
      DisableThreadLibraryCalls(hModule);
      CreateThread(NULL, 0, onAttach, hModule, 0, NULL);
      break;
    case DLL_PROCESS_DETACH:
      hentai::client::detach();
      break;
    }
    return TRUE;
}