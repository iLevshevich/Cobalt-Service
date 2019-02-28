#ifndef __MANAGER_OPERATION_TYPE_H_INCLUDED__
#define __MANAGER_OPERATION_TYPE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Core
   {
      namespace Chain
      {
         /**
         * enum OperationType {
         *   GetStatuses,
         *   SaveConfiguration,
         *   StartDispatchers,
         *   StopDispatchers,
         *   AbortDispatchers,
         *   ResetDispatchers,
         *   CleanLastErrors,
         *   StartDispatcher,
         *   StopDispatcher,
         *   AbortDispatcher,
         *   ResetDispatcher,
         *   AddDispatcher,   
         *   RemoveDispatcher,
         *   CleanLastError,
         *   GetDispatcherTypes
         * };
         */

         DEFINE_ENUM_WITH_STRING_CONVERSIONS(OperationType, (GetStatuses)(SaveConfiguration)(StartDispatchers)(StopDispatchers)(AbortDispatchers)(ResetDispatchers)(CleanLastErrors)(StartDispatcher)(StopDispatcher)(AbortDispatcher)(ResetDispatcher)(AddDispatcher)(RemoveDispatcher)(CleanLastError)(GetDispatcherTypes));
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_OPERATION_TYPE_H_INCLUDED__
