#ifndef __AMQP_CONNECTION_H_INCLUDED__
#define __AMQP_CONNECTION_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Poco
   {
      namespace Connection
      {
         class Connection:
            public Cobalt::Poco::Connection::IConnection,
            private boost::noncopyable {
         public:
            Connection();

            virtual size_t __stdcall parseDate( const char* buffer, const size_t size ) override;

            virtual void __stdcall setConnection( AMQP::Connection* const connection ) override;
            virtual void __stdcall setConnected( const bool connected = true ) override;
			virtual bool closeConnection() override;

            virtual bool isAvailable() const override;
            virtual bool isConnected() const override;

            virtual ~Connection() = default;

         private:
            bool connected_;
            AMQP::Connection* connection_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__AMQP_CONNECTION_H_INCLUDED__
