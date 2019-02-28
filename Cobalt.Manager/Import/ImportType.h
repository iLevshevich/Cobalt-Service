#ifndef __MANAGER_IMPORT_TYPE_H_INCLUDED__
#define __MANAGER_IMPORT_TYPE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Import
   {
      enum ImportType {
         Amqp,
         Tcp
      };
   }
}

#pragma pack( pop )

#endif //__MANAGER_IMPORT_TYPE_H_INCLUDED__
