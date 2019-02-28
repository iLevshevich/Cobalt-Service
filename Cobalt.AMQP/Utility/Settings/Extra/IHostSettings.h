#ifndef __AMQP_I_HOST_SETTINGS_H_INCLUDED__
#define __AMQP_I_HOST_SETTINGS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class IHostSettings {
      public:
         virtual std::string getHost() const = 0;
         virtual uint16_t getPort() const = 0;

         virtual ~IHostSettings() = default;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_I_HOST_SETTINGS_H_INCLUDED__
