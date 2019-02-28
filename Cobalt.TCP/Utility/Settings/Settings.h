#ifndef __TCP_SETTINGS_H_INCLUDED__
#define __TCP_SETTINGS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class Settings :
         public ISettings,
         private boost::noncopyable {
      public:
         virtual std::string getPort() const override;
         virtual std::string getHost() const override;

         virtual ~Settings() = default;

      protected:
         explicit Settings( const SettingsBuilder& builder );

      private:
         std::string port_;
         std::string host_;
      };
   }
}

#pragma pack( pop )

#endif //__TCP_SETTINGS_H_INCLUDED__
