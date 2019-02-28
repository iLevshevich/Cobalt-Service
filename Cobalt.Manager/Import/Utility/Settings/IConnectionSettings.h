﻿#ifndef __MANAGER_I_CONNECTION_SETTINGS_H_INCLUDED__
#define __MANAGER_I_CONNECTION_SETTINGS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Import
   {
      namespace Utility
      {
         class IConnectionSettings {
         public:
            virtual std::string getVirtualHost() const = 0;

            virtual ~IConnectionSettings() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_CONNECTION_SETTINGS_H_INCLUDED__
