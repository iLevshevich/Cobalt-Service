#ifndef __AMQP_I_PUBLISH_H_INCLUDED__
#define __AMQP_I_PUBLISH_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace EntryPoint
   {
      class IPublish {
      public:
         virtual void publishNoAck( std::function< std::vector< std::string >() > executor, const std::string& routingKey = std::string() ) = 0;
         virtual void publishAck( std::function< std::vector< std::string >() > executor, const std::string& routingKey = std::string() ) = 0;
         virtual void publishNoAck( std::function< std::string() > executor, const std::string& routingKey = std::string() ) = 0;
         virtual void publishAck( std::function< std::string() > executor, const std::string& routingKey = std::string() ) = 0;
         virtual void quit() = 0;
         virtual bool tryQuit() = 0;
         virtual bool isQuited() = 0;

         virtual ~IPublish() = default;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_I_PUBLISH_H_INCLUDED__
