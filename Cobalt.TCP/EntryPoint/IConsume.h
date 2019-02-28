#ifndef __TCP_I_CONSUME_H_INCLUDED__
#define __TCP_I_CONSUME_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace EntryPoint
   {
      class IConsume {
      public:
         typedef typename Utility::Traits< std::function< void( const std::string&& ) > >::const_rvalue_reference_t executor_type;

         virtual void consume( executor_type executor ) = 0;
         virtual void quit() = 0;
         virtual bool tryQuit() = 0;
         virtual bool isQuited() = 0;

         virtual ~IConsume() = default;
      };
   }
}

#pragma pack( pop )

#endif //__TCP_I_CONSUME_H_INCLUDED__
