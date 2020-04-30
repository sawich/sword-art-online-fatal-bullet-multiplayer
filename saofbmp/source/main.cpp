#include "../header/framework.hpp"
#include "../header/hentai/process.hpp"
#include "../header/hentai/injector.hpp"

int main(int argc, char* argv[]) noexcept
{
	const auto process{ hentai::process::open_shared(TEXT("SAOFB-Win64-Shipping.exe")) };
	hentai::injector::use(process, TEXT("saofbmp_client.dll"));

	return EXIT_SUCCESS;
}