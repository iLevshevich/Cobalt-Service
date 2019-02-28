#ifndef __AMQP_I_CONNECTION_H_INCLUDED__
#define __AMQP_I_CONNECTION_H_INCLUDED__

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
         class IConnection {
         public:
            virtual size_t __stdcall parseDate( const char* buffer, const size_t size ) = 0;

            virtual void __stdcall setConnection( AMQP::Connection* const connection ) = 0;
            virtual void __stdcall setConnected( const bool connected = true ) = 0;
			virtual bool closeConnection() = 0;

            virtual bool isAvailable() const = 0;
            virtual bool isConnected() const = 0;

            virtual ~IConnection() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__AMQP_I_CONNECTION_H_INCLUDED__
