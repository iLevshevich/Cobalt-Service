#ifndef __MANAGER_I_LOGIN_SETTINGS_H_INCLUDED__
#define __MANAGER_I_LOGIN_SETTINGS_H_INCLUDED__

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
         class ILoginSettings {
         public:
            virtual std::string getUser() const = 0;
            virtual std::string getPassword() const = 0;

            virtual ~ILoginSettings() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_LOGIN_SETTINGS_H_INCLUDED__
