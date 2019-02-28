#ifndef __AMQP_PUBLISH_H_INCLUDED__
#define __AMQP_PUBLISH_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace EntryPoint
   {
      class Publish :
         public IPublish,
         private boost::noncopyable {
      public:
         static boost::shared_ptr< IPublish > getInstance( const boost::shared_ptr< Utility::ISettings >& settings );

         virtual void publishNoAck( std::function< std::vector< std::string >() > executor, const std::string& routingKey = std::string() ) override;
         virtual void publishAck( std::function< std::vector< std::string >() > executor, const std::string& routingKey = std::string() ) override;
         virtual void publishNoAck( std::function< std::string() > executor, const std::string& routingKey = std::string() ) override;
         virtual void publishAck( std::function< std::string() > executor, const std::string& routingKey = std::string() ) override;
         virtual void quit() override;
         virtual bool tryQuit() override;
         virtual bool isQuited() override;

         virtual ~Publish() = default;
      protected:
         explicit Publish( const boost::shared_ptr< Utility::ISettings >& settings );

         enum { TRY_QUIT_TIMEOUT = 10 };
         void __fastcall wait( size_t ) const;
      private:
         boost::shared_ptr< Utility::ISettings > settings_;
         boost::shared_ptr< Poco::PocoHandler > handler_;
         boost::shared_ptr< Utility::Transaction > transaction_;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_PUBLISH_H_INCLUDED__
