#ifndef __MANAGER_I_META_HANDLER_H_INCLUDED__
#define __MANAGER_I_META_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Meta
      {
         template< class T >
         class IMetaHandler {
         public:
            typedef T base_type;

            virtual base_type getId() = 0;
            virtual base_type getDescription() = 0;

            virtual ~IMetaHandler() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_META_HANDLER_H_INCLUDED__
