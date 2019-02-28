#ifndef __AMQP_FLAGS_TYPE_H_INCLUDED__
#define __AMQP_FLAGS_TYPE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      enum FlagsType {
         durable = 1,
         autodelete = 2,
         active = 4,
         passive = 8,
         ifunused = 16,
         ifempty = 32,
         global = 64,
         nolocal = 128,
         noack = 256,
         exclusive = 512,
         nowait = 1024,
         mandatory = 2048,
         immediate = 4096,
         redelivered = 8192,
         multiple = 16384,
         requeue = 32768,
         readable = 1,
         writable = 2,
         internal = 65536
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_FLAGS_TYPE_H_INCLUDED__
