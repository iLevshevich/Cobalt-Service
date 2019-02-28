#ifndef __AMQP_I_CHANNEL_SETTINGS_H_INCLUDED__
#define __AMQP_I_CHANNEL_SETTINGS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class IChannelSettings {
      public:
         virtual uint16_t getPrefetchCountQos() const = 0;
         virtual bool getGlobalQos_() const = 0;

         virtual ~IChannelSettings() = default;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_I_CHANNEL_SETTINGS_H_INCLUDED__
