#ifndef __MANAGER_I_QUEUE_SETTINGS_H_INCLUDED__
#define __MANAGER_I_QUEUE_SETTINGS_H_INCLUDED__

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
         class IQueueSettings {
         public:
            virtual std::string getName() const = 0;
            virtual FlagsType getType() const = 0;

            virtual ~IQueueSettings() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_QUEUE_SETTINGS_H_INCLUDED__
