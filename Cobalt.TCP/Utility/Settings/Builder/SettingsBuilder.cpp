#include "../../../stdafx.h"

#include "../../EnableMake.h"
#include "../../MakeObject.h"

#include "../../Settings/ISettings.h"
#include "../../Settings/Settings.h"

#include "ISettingsBuilder.h"
#include "SettingsBuilder.h"

namespace Cobalt
{
   namespace Utility
   {
      boost::shared_ptr< ISettingsBuilder > SettingsBuilder::getInstance() {
         return make_shared_pool_enable< ISettingsBuilder, SettingsBuilder, boost::default_user_allocator_malloc_free >();
      }

      ISettingsBuilder& SettingsBuilder::setPort( const std::string& port ) {
         port_ = port;
         return *this;
      }

      ISettingsBuilder& SettingsBuilder::setHost( const std::string& host ) {
         host_ = host;
         return *this;
      }

      std::string SettingsBuilder::getPort() const {
         return port_;
      }

      std::string SettingsBuilder::getHost() const {
         return host_;
      }

      boost::shared_ptr< ISettings > SettingsBuilder::build() const {
         return make_shared_pool_enable< ISettings, Settings, boost::default_user_allocator_malloc_free >( *this );
      }
   }
}
