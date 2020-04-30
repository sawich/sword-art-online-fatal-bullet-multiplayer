#include "../header/hentai/client.hpp"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) noexcept
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
      hentai::client::attach();
      break;
    case DLL_PROCESS_DETACH:
      hentai::client::detach();
      break;
    return TRUE;
    }
}

