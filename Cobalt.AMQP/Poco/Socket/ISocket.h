#ifndef __AMQP_I_SOCKET_H_INCLUDED__
#define __AMQP_I_SOCKET_H_INCLUDED__

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
         class ISocket {
         public:
            virtual void __stdcall setLinger(bool on, int seconds) = 0;
            virtual void __stdcall setNoDelay(bool flag = true) = 0;
            virtual void __stdcall setKeepAlive(bool flag = true) = 0;
            virtual void __stdcall setReuseAddress(bool flag = true) = 0;
            virtual void __stdcall setReusePort(bool flag = true) = 0;
            virtual void __stdcall setOOBInline(bool flag = true) = 0;
            virtual void __stdcall setBlocking(bool flag = true) = 0;

            virtual ~ISocket() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__AMQP_I_SOCKET_H_INCLUDED__
