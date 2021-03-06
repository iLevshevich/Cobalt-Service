#ifndef __AMQP_STD_AFX_H_INCLUDED__
#define __AMQP_STD_AFX_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#if !defined(__cplusplus)
#	error C++ compiler required.
#endif

#define __INTERNAL_VERSION__ "1.0.0.1"
#define __INTERNAL_GUID__ "8F9CADF6-A281-4FCC-94FC-D6DA8777EF0D"

#if !defined(BOOST_DLL_FORCE_ALIAS_INSTANTIATION)
#	define BOOST_DLL_FORCE_ALIAS_INSTANTIATION
#endif

#if !defined(NOMINMAX)
#	define NOMINMAX
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#  include "targetver.h"

#  if !defined(WIN32_LEAN_AND_MEAN)
#     define WIN32_LEAN_AND_MEAN             
#  endif

#  include <windows.h>
#endif

#include <cstddef>
#include <stdexcept>
#include <vector>
#include <thread>
#include <chrono>
#include <cstring>
#include <cassert>
#include <iostream>
#include <memory>

#include <boost/noncopyable.hpp>
#include <boost/type_traits.hpp>
#include <boost/dll.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/atomic.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/static_assert.hpp>

#include <Poco/Net/StreamSocket.h>

#include <amqpcpp.h>

#pragma comment( lib, "amqpcpp.lib" )

#endif //__AMQP_STD_AFX_H_INCLUDED__
