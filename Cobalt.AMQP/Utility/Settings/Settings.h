#ifndef __AMQP_SETTINGS_H_INCLUDED__
#define __AMQP_SETTINGS_H_INCLUDED__

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
         virtual boost::shared_ptr< IHostSettings > getHost() const override;
         virtual boost::shared_ptr< IChannelSettings > getChannel() const override;
         virtual boost::shared_ptr< IExchangeSettings > getExchange() const override;
         virtual boost::shared_ptr< IQueueSettings > getQueue() const override;
         virtual boost::shared_ptr< ILoginSettings > getLogin() const override;
         virtual boost::shared_ptr< IConnectionSettings > getConnection() const override;

         virtual ~Settings() = default;

      protected:
         explicit Settings( const SettingsBuilder& builder );

      private:
         boost::shared_ptr< IHostSettings > host_;
         boost::shared_ptr< IChannelSettings > channel_;
         boost::shared_ptr< IExchangeSettings > exchange_;
         boost::shared_ptr< IQueueSettings > queue_;
         boost::shared_ptr< ILoginSettings > login_;
         boost::shared_ptr< IConnectionSettings > connection_;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_SETTINGS_H_INCLUDED__
