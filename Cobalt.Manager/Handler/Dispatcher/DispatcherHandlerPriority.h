#ifndef __MANAGER_DISPATCHER_HANDLER_PRIORITY_H_INCLUDED__
#define __MANAGER_DISPATCHER_HANDLER_PRIORITY_H_INCLUDED__

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
         namespace Priority
         {
            enum DispatcherHandlerPriority {
               AmqpToTcp,
               TcpToTcp,
               AmqpToAmqp,
               TcpToAmqp
            };
         }
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_DISPATCHER_HANDLER_PRIORITY_H_INCLUDED__
