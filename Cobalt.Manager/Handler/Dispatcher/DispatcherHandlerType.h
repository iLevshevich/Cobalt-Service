#ifndef __MANAGER_DISPATCHER_HANDLER_TYPE_H_INCLUDED__
#define __MANAGER_DISPATCHER_HANDLER_TYPE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Dispatcher
      {
         namespace Type
         {
            /**
             * enum DispatcherHandlerType {
             *    AmqpToAmqp,
             *    AmqpToTcp,
             *    TcpToAmqp,
             *    TcpToTcp
             * };
             */

            DEFINE_ENUM_WITH_STRING_CONVERSIONS(DispatcherHandlerType, (AmqpToAmqp)(AmqpToTcp)(TcpToAmqp)(TcpToTcp));
         }
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_DISPATCHER_HANDLER_TYPE_H_INCLUDED__
