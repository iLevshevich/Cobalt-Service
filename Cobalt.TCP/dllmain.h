#ifndef __TCP_DLL_MAIN_H_INCLUDED__
#define __TCP_DLL_MAIN_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "fwdheaders.h"

namespace EntryPoint
{
   const char* __stdcall internal_version();
   const char* __stdcall internal_guid();
}

#endif //__TCP_DLL_MAIN_H_INCLUDED__
