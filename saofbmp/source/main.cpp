#include "../header/framework.hpp"
#include "../header/hentai/process.hpp"
#include "../header/hentai/injector.hpp"

int main(int argc, char* argv[]) noexcept
{
	const auto process{ hentai::process::open_shared(TEXT("SAOFB-Win64-Shipping.exe")) };
	//const auto process{ hentai::process::open_shared(TEXT("notepad.exe")) };
	hentai::injector::use(process, TEXT("saofbmp_client.dll"));
	//hentai::injector::use(process, TEXT("saofb.dll"));

	return EXIT_SUCCESS;
}