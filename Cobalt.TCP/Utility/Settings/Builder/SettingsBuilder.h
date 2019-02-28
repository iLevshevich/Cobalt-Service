#ifndef __TCP_SETTINGS_BUILDER_H_INCLUDED__
#define __TCP_SETTINGS_BUILDER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class SettingsBuilder :
         public ISettingsBuilder,
         private boost::noncopyable {
      public:
         static boost::shared_ptr< ISettingsBuilder > getInstance();

         virtual ISettingsBuilder& __stdcall setPort( const std::string& port ) override;
         virtual ISettingsBuilder& __stdcall setHost( const std::string& host ) override;

         virtual std::string getPort() const override;
         virtual std::string getHost() const override;

         virtual boost::shared_ptr< ISettings > build() const override;

         virtual ~SettingsBuilder() = default;

      protected:
         SettingsBuilder() = default;
      private:
         std::string port_;
         std::string host_;
      };
   }
}

#pragma pack( pop )

#endif //__TCP_SETTINGS_BUILDER_H_INCLUDED__
