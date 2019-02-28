#ifndef __MANAGER_I_RESET_HANDLER_H_INCLUDED__
#define __MANAGER_I_RESET_HANDLER_H_INCLUDED__

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
         class IResetHandler {
         public:
            virtual void reset() = 0;

            virtual ~IResetHandler() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_RESET_HANDLER_H_INCLUDED__
