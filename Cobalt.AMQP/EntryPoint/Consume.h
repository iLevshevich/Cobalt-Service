#ifndef __AMQP_CONSUME_H_INCLUDED__
#define __AMQP_CONSUME_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace EntryPoint
   {
      class Consume :
         public IConsume,
         private boost::noncopyable {
      public:
         static boost::shared_ptr< IConsume > getInstance( const boost::shared_ptr< Utility::ISettings >& settings );

         virtual void consumeNoAck( std::function< void( const std::string&& ) > executor, const std::string& routingKey = std::string() ) override;
         virtual void consumeAck( std::function< void( const std::string&& ) > executor, const std::string& routingKey = std::string() ) override;
         virtual void quit() override;
         virtual bool tryQuit() override;
         virtual bool isQuited() override;

         virtual ~Consume() = default;

      protected:
         explicit Consume( const boost::shared_ptr< Utility::ISettings >& settings );

      private:
         boost::shared_ptr< Utility::ISettings > settings_;
         boost::shared_ptr< Poco::PocoHandler > handler_;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_CONSUME_H_INCLUDED__
