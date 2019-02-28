#ifndef __TCP_I_SETTINGS_BUILDER_H_INCLUDED__
#define __TCP_I_SETTINGS_BUILDER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class ISettingsBuilder {
      public:
         virtual ISettingsBuilder& __stdcall setPort( const std::string& port ) = 0;
         virtual ISettingsBuilder& __stdcall setHost( const std::string& host ) = 0;

         virtual std::string getPort() const = 0;
         virtual std::string getHost() const = 0;

         virtual boost::shared_ptr< ISettings > build() const = 0;

         virtual ~ISettingsBuilder() = default;
      };
   }
}

#pragma pack( pop )

#endif //__TCP_I_SETTINGS_BUILDER_H_INCLUDED__

