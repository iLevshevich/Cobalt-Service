#ifndef __AMQP_I_POCO_SOCKET_H_INCLUDED__
#define __AMQP_I_POCO_SOCKET_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"
#include "ISocket.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Poco
   {
      namespace Socket
      {
         class IPocoSocket :
            public ISocket {
         public:
            virtual void __stdcall connect(const std::string& host, const uint16_t port) = 0;
            virtual void close() = 0;

            virtual int __stdcall receiveBytes(void* buffer, int length, int flags = 0) = 0;
            virtual int __stdcall sendBytes(const void* buffer, int length, int flags = 0) = 0;

            virtual int getAvailable() const = 0;
            virtual bool isAvailable() const = 0;

            virtual bool isValid() const = 0;
            virtual bool isInvalid() const = 0;

            virtual ~IPocoSocket() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__AMQP_I_POCO_SOCKET_H_INCLUDED__
