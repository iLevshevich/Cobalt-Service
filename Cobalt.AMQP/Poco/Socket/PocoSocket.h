#ifndef __AMQP_POCO_SOCKET_H_INCLUDED__
#define __AMQP_POCO_SOCKET_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Poco
   {
      namespace Socket
      {
         class PocoSocket :
            public IPocoSocket,
            private boost::noncopyable {
         public:
            PocoSocket();

            virtual void __stdcall connect(const std::string& host, const uint16_t port) override;
            virtual void close() override;

            virtual int getAvailable() const override;
            virtual bool isAvailable() const override;

            virtual bool isValid() const override;
            virtual bool isInvalid() const override;

            virtual int __stdcall receiveBytes(void* buffer, int length, int flags = 0) override;
            virtual int __stdcall sendBytes(const void* buffer, int length, int flags = 0) override;

            virtual void __stdcall setLinger(bool on, int seconds) override;
            virtual void __stdcall setNoDelay(bool flag = true) override;
            virtual void __stdcall setKeepAlive(bool flag = true) override;
            virtual void __stdcall setReuseAddress(bool flag = true) override;
            virtual void __stdcall setReusePort(bool flag = true) override;
            virtual void __stdcall setOOBInline(bool flag = true) override;
            virtual void __stdcall setBlocking(bool flag = true) override;

            virtual ~PocoSocket() override = default;
         private:
            boost::shared_ptr< ::Poco::Net::StreamSocket > socket_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__AMQP_POCO_SOCKET_H_INCLUDED__
