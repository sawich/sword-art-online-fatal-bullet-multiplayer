//#pragma once
//
//#include "../framework.hpp"
//
//namespace hentai
//{
//	class net
//	{
//	public:
//		net() noexcept {}
//		net(const std::string_view address, const uint16_t port) noexcept 
//		{
//			m_socket.connect({ boost::asio::ip::address::from_string(std::data(address)), port });
//		}
//		~net(void) noexcept {}
//
//	private:
//		boost::asio::io_service m_service;
//		boost::asio::ip::tcp::socket m_socket{ m_service };
//	};
//}