#ifndef __AMQP_EXCHANGE_TYPE_H_INCLUDED__
#define __AMQP_EXCHANGE_TYPE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      enum ExchangeType {
         fanout = 0,
         direct = 1,
         topic = 2,
         headers = 3,
         consistent_hash = 4
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_EXCHANGE_TYPE_H_INCLUDED__

