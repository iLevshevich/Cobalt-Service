#ifndef __MANAGER_I_CONSUME_H_INCLUDED__
#define __MANAGER_I_CONSUME_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Import
   {
      template< ImportType _Type >
      class IConsume;

      template<>
      class IConsume< Import::ImportType::Amqp > {
      public:
         virtual void consumeNoAck( std::function< void( const std::string&& ) > executor, const std::string& routingKey = std::string() ) = 0;
         virtual void consumeAck( std::function< void( const std::string&& ) > executor, const std::string& routingKey = std::string() ) = 0;
         virtual void quit() = 0;
         virtual bool tryQuit() = 0;
         virtual bool isQuited() = 0;

         virtual ~IConsume() = default;
      };

      template<>
      class IConsume< Import::ImportType::Tcp > {
      public:
         typedef typename Cobalt::Utility::Traits< std::function< void( const std::string&& ) > >::const_rvalue_reference_t executor_type;

         virtual void consume( executor_type executor ) = 0;
         virtual void quit() = 0;
         virtual bool tryQuit() = 0;
         virtual bool isQuited() = 0;

         virtual ~IConsume() = default;
      };
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_CONSUME_H_INCLUDED__
