#include "../../../stdafx.h"

#include "../../EnableMake.h"
#include "../../FlagsType.h"
#include "../../ExchangeType.h"
#include "../../MakeObject.h"

#include "../../Settings/Extra/IChannelSettings.h"
#include "../../Settings/Extra/IConnectionSettings.h"
#include "../../Settings/Extra/IExchangeSettings.h"
#include "../../Settings/Extra/IHostSettings.h"
#include "../../Settings/Extra/ILoginSettings.h"
#include "../../Settings/Extra/IQueueSettings.h"

#include "../../Settings/Extra/HostSettings.h"
#include "../../Settings/Extra/ChannelSettings.h"
#include "../../Settings/Extra/ExchangeSettings.h"
#include "../../Settings/Extra/LoginSettings.h"
#include "../../Settings/Extra/QueueSettings.h"
#include "../../Settings/Extra/ConnectionSettings.h"

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

      ISettingsBuilder& SettingsBuilder::setHost( const std::string& host, const uint16_t port ) {
         host_ = HostSettings::getInstance( host, port );
         return *this;
      }

      ISettingsBuilder& SettingsBuilder::setChannel( uint16_t prefetchCountQos, bool globalQos ) {
         channel_ = ChannelSettings::getInstance( prefetchCountQos, globalQos );
         return *this;
      }

      ISettingsBuilder& SettingsBuilder::setExchange( const std::string& name, ExchangeType type ) {
         exchange_ = ExchangeSettings::getInstance( name, type );
         return *this;
      }

      ISettingsBuilder& SettingsBuilder::setExchange( const std::string& name ) {
         exchange_ = ExchangeSettings::getInstance( name );
         return *this;
      }

      ISettingsBuilder& SettingsBuilder::setQueue( const std::string& name, FlagsType type ) {
         queue_ = QueueSettings::getInstance( name, type );
         return *this;
      }

      ISettingsBuilder& SettingsBuilder::setQueue( const std::string& name ) {
         queue_ = QueueSettings::getInstance( name );
         return *this;
      }

      ISettingsBuilder& SettingsBuilder::setLogin( const std::string& user, const std::string& password ) {
         login_ = LoginSettings::getInstance( user, password );
         return *this;
      }

      ISettingsBuilder& SettingsBuilder::setConnection( const std::string& vhost ) {
         connection_ = ConnectionSettings::getInstance( vhost );
         return *this;
      }

      boost::shared_ptr< IHostSettings > SettingsBuilder::getHost() const {
         return host_;
      }

      boost::shared_ptr< IChannelSettings > SettingsBuilder::getChannel() const {
         return channel_;
      }

      boost::shared_ptr< IExchangeSettings > SettingsBuilder::getExchange() const {
         return exchange_;
      }

      boost::shared_ptr< IQueueSettings > SettingsBuilder::getQueue() const {
         return queue_;
      }

      boost::shared_ptr< ILoginSettings > SettingsBuilder::getLogin() const {
         return login_;
      }

      boost::shared_ptr< IConnectionSettings > SettingsBuilder::getConnection() const {
         return connection_;
      }

      boost::shared_ptr< ISettings > SettingsBuilder::build() const {
         return make_shared_pool_enable< ISettings, Settings, boost::default_user_allocator_malloc_free >( *this );
      }
   }
}
