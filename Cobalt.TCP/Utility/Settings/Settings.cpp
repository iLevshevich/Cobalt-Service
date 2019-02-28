#include "../../stdafx.h"

#include "Builder/ISettingsBuilder.h"
#include "Builder/SettingsBuilder.h"

#include "ISettings.h"
#include "Settings.h"

namespace Cobalt
{
   namespace Utility
   {
      Settings::Settings( const SettingsBuilder& builder ) :
         port_( builder.getPort() ),
         host_( builder.getHost() ) {
      }

      std::string Settings::getPort() const {
         return port_;
      }

      std::string Settings::getHost() const {
         return host_;
      }
   }
}
