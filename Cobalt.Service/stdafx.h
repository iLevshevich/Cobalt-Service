#ifndef __SERVICE_STD_AFX_H_INCLUDED__
#define __SERVICE_STD_AFX_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#if !defined(__cplusplus)
#	error C++ compiler required.
#endif

#define __INTERNAL_VERSION__ "1.0.0.1"
#define __INTERNAL_GUID__ "AAE780DF-F480-4E3E-8978-2057A6BDED22"

#ifndef __MODULE_NAME__
#	define __MODULE_NAME__ L"Cobalt.Service"
#endif

#if !defined(BOOST_DLL_FORCE_ALIAS_INSTANTIATION)
#  define BOOST_DLL_FORCE_ALIAS_INSTANTIATION
#endif

#if !defined(NOMINMAX)
#  define NOMINMAX
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#  include "targetver.h"

#  if !defined(WIN32_LEAN_AND_MEAN)
#     define WIN32_LEAN_AND_MEAN             
#  endif

#  include <windows.h>
#endif

#ifndef WINVER				
#  define WINVER NTDDI_WIN7		
#endif		

#ifndef _WIN32_WINNT	
#  define _WIN32_WINNT NTDDI_WIN7
#endif	

#include <stdio.h>
#include <tchar.h>
#include <cstring>

#include <boost/noncopyable.hpp>
#include <boost/type_traits.hpp>
#include <boost/dll.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/format.hpp>
#include <boost/system/system_error.hpp> 
#include <boost/thread.hpp>
#include <boost/thread/scoped_thread.hpp>

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      
#define _ATL_ALL_WARNINGS
#define _ATL_NO_COM_SUPPORT

#include "resource.h"
#include <atlbase.h>
#include <atlstr.h>
#include <atlcom.h>
#include <comutil.h>
#include <shellapi.h>

#pragma comment( lib, "comsuppw" )
#pragma comment( lib, "advapi32" )

#endif //__SERVICE_STD_AFX_H_INCLUDED__
