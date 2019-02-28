#ifndef __MANAGER_PERFORMANCE_HANDLER_TYPE_H_INCLUDED__
#define __MANAGER_PERFORMANCE_HANDLER_TYPE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Performance
      {
         /**
         * enum PerformanceHandlerType {
         *   seconds,
         *   milliseconds,
         *   microseconds
         * };
         */

         DEFINE_ENUM_WITH_STRING_CONVERSIONS(PerformanceHandlerType, (seconds)(milliseconds)(microseconds));
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_PERFORMANCE_HANDLER_TYPE_H_INCLUDED__
