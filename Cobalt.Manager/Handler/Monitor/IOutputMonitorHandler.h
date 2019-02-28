#ifndef __MANAGER_I_OUTPUT_MONITOR_HANDLER_H_INCLUDED__
#define __MANAGER_I_OUTPUT_MONITOR_HANDLER_H_INCLUDED__

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
         class IOutputMonitorHandler;

         template< class T >
         class IOutputMonitorHandler :
            public IMonitorHandler< T > {
         public:
            typedef typename Utility::Traits< T >::const_reference_t handle_arg_type;

            virtual void __fastcall onBeforePop( handle_arg_type, handle_arg_type ) = 0;
            virtual void __fastcall onPop( handle_arg_type, handle_arg_type ) = 0;
            virtual void __fastcall onAfterPop( handle_arg_type, handle_arg_type ) = 0;

            virtual ~IOutputMonitorHandler() = default;
         };

         template<>
         class IOutputMonitorHandler< void > :
            public IMonitorHandler< void > {
         public:
            virtual void __fastcall onBeforePop() = 0;
            virtual void __fastcall onPop() = 0;
            virtual void __fastcall onAfterPop() = 0;

            virtual ~IOutputMonitorHandler() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_OUTPUT_MONITOR_HANDLER_H_INCLUDED__
