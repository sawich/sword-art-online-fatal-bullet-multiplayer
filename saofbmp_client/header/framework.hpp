#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <TlHelp32.h>
#include <psapi.h>

#include <iostream>
#include <future>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <memory>
#include <cassert>
#include <thread>
//
//#define BOOST_ASIO_STANDALONE
//#define DASIO_STANDALONE 
//#define ASIO_HAS_STD_ADDRESSOF
//#define ASIO_HAS_STD_ARRAY
//#define ASIO_HAS_CSTDINT
//#define ASIO_HAS_STD_SHARED_PTR
//#define ASIO_HAS_STD_TYPE_TRAITS
//#include <boost/asio.hpp>

namespace std
{
#ifdef _UNICODE
	using tstring = wstring;
	using tstringstream = wstringstream;

	template <class T>
	tstring to_tstring(T&& arg) { return to_wstring(arg); }
#else
	using tstring = string;
	using tstringstream = wstringstream;

	template <class T>
	tstring to_tstring(T&& arg) { return to_string(arg); }
#endif
}

// https://youtu.be/kkcq3tX2nOA