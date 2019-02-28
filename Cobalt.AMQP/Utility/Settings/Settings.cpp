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
         host_( builder.getHost() ),
         channel_( builder.getChannel() ),
         exchange_( builder.getExchange() ),
         queue_( builder.getQueue() ),
         login_( builder.getLogin() ),
         connection_( builder.getConnection() ) {
      }

      boost::shared_ptr< IHostSettings > Settings::getHost() const {
         return host_;
      }

      boost::shared_ptr< IChannelSettings > Settings::getChannel() const {
         return channel_;
      }

      boost::shared_ptr< IExchangeSettings > Settings::getExchange() const {
         return exchange_;
      }

      boost::shared_ptr< IQueueSettings > Settings::getQueue() const {
         return queue_;
      }

      boost::shared_ptr< ILoginSettings > Settings::getLogin() const {
         return login_;
      }

      boost::shared_ptr< IConnectionSettings > Settings::getConnection() const {
         return connection_;
      }
   }
}
