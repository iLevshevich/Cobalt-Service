#ifndef __TCP_I_SETTINGS_H_INCLUDED__
#define __TCP_I_SETTINGS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class ISettings {
      public:
         virtual std::string getPort() const = 0;
         virtual std::string getHost() const = 0;

         virtual ~ISettings() = default;
      };
   }
}

#pragma pack( pop )

#endif //__TCP_I_SETTINGS_H_INCLUDED__

