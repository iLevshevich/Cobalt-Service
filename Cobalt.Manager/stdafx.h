#ifndef __MANAGER_STD_AFX_H_INCLUDED__
#define __MANAGER_STD_AFX_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#if !defined(__cplusplus)
#	error C++ compiler required.
#endif

#define __INTERNAL_VERSION__ "1.0.0.1"
#define __INTERNAL_GUID__ "740263D1-8148-4B6D-9D0E-F42BB6D44A45"

#if defined(_DEBUG)
#	if !defined(__MANAGER_TRACE__)
#		define __MANAGER_TRACE__
#	endif

#  if !defined(__MANAGER_JSON_PRETTY__)
#     define __MANAGER_JSON_PRETTY__
#  endif
#endif

#if !defined(NOMINMAX)
#  define NOMINMAX
#endif

#if defined(BOOST_PARAMETER_MAX_ARITY)
#  undef BOOST_PARAMETER_MAX_ARITY
#endif

#define BOOST_PARAMETER_MAX_ARITY 12

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#  include "targetver.h"

#  if !defined(WIN32_LEAN_AND_MEAN)
#     define WIN32_LEAN_AND_MEAN             
#  endif

#  include <windows.h>
#endif

#include <conio.h>
#include <stdio.h>
#include <tchar.h>
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <map>
#include <list>
#include <thread>
#include <chrono>
#include <cstring>
#include <cassert>
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>
#include <functional>
#include <algorithm>
#include <queue>
#include <mutex>
#include <condition_variable>

#include <boost/noncopyable.hpp>
#include <boost/type_traits.hpp>
#include <boost/dll.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/shared_array.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/dll.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <boost/lockfree/spsc_queue.hpp>
#include <boost/atomic.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/parameter/name.hpp>
#include <boost/parameter/preprocessor.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/unordered_map.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/open_mode.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/program_options.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/preprocessor.hpp>
#include <boost/asio.hpp>

#include <boost/version.hpp>
#	if BOOST_VERSION >= 106600
#		include <boost/uuid/detail/sha1.hpp>
#	else
#		include <boost/uuid/sha1.hpp>
#endif

#include "macroses.h"

#endif //__MANAGER_STD_AFX_H_INCLUDED__
