#ifndef __MANAGER_I_MONITOR_HANDLER_H_INCLUDED__
#define __MANAGER_I_MONITOR_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Monitor
      {
         template< class T >
         class IMonitorHandle;

         template< class T >
         class IMonitorHandler {
         public:
            typedef typename Utility::Traits< T >::const_reference_t monitor_arg_type;

            virtual void __fastcall onStart( monitor_arg_type ) = 0;
            virtual void __fastcall onStop( monitor_arg_type ) = 0;
            virtual void __fastcall onError( monitor_arg_type, monitor_arg_type ) = 0;

            virtual ~IMonitorHandler() = default;
         };

         template<>
         class IMonitorHandler< void > {
         public:
            virtual void __fastcall onStart() = 0;
            virtual void __fastcall onStop() = 0;
            virtual void __fastcall onError() = 0;

            virtual ~IMonitorHandler() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_MONITOR_HANDLER_H_INCLUDED__
