#ifndef __AMQP_I_EXCHANGE_SETTINGS_H_INCLUDED__
#define __AMQP_I_EXCHANGE_SETTINGS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class IExchangeSettings {
      public:
         virtual std::string getName() const = 0;
         virtual ExchangeType getType() const = 0;

         virtual ~IExchangeSettings() = default;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_I_EXCHANGE_SETTINGS_H_INCLUDED__
