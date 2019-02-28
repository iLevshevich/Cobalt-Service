#ifndef __MANAGER_I_INPUT_MONITOR_HANDLER_H_INCLUDED__
#define __MANAGER_I_INPUT_MONITOR_HANDLER_H_INCLUDED__

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
         class IInputMonitorHandler;

         template< class T >
         class IInputMonitorHandler:
            public IMonitorHandler< T > {
         public:
            typedef typename Utility::Traits< T >::const_reference_t handle_arg_type;

            virtual void __fastcall onBeforePush( handle_arg_type, handle_arg_type ) = 0;
            virtual void __fastcall onPush( handle_arg_type, handle_arg_type ) = 0;
            virtual void __fastcall onAfterPush( handle_arg_type, handle_arg_type ) = 0;

            virtual ~IInputMonitorHandler() = default;
         };

         template<>
         class IInputMonitorHandler< void > :
            public IMonitorHandler< void > {
         public:
            virtual void __fastcall onBeforePush() = 0;
            virtual void __fastcall onPush() = 0;
            virtual void __fastcall onAfterPush() = 0;

            virtual ~IInputMonitorHandler() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_INPUT_MONITOR_HANDLER_H_INCLUDED__
