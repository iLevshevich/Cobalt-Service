#ifndef __MANAGER_STATE_HANDLER_TYPE_H_INCLUDED__
#define __MANAGER_STATE_HANDLER_TYPE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace State
      {
         enum StateHandlerType {
            base,
            input,
            intermediate,
            output,
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_STATE_HANDLER_TYPE_H_INCLUDED__
