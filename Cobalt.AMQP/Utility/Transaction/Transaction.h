#ifndef __AMQP_TRANSACTION_H_INCLUDED__
#define __AMQP_TRANSACTION_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class Transaction:
         private boost::noncopyable {
      public:
         void __stdcall transaction( const std::function< void() >& executor,
                                     const std::function< void() >& success,
                                     AMQP::Channel& channel );
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_TRANSACTION_H_INCLUDED__
