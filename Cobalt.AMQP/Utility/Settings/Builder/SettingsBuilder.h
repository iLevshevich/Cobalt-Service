#ifndef __AMQP_SETTINGS_BUILDER_H_INCLUDED__
#define __AMQP_SETTINGS_BUILDER_H_INCLUDED__

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

         virtual ISettingsBuilder& __stdcall setHost( const std::string& host, const uint16_t port ) override;
         virtual ISettingsBuilder& __stdcall setChannel( uint16_t prefetchCountQos, bool globalQos = false ) override;
         virtual ISettingsBuilder& __stdcall setExchange( const std::string& name, ExchangeType type ) override;
         virtual ISettingsBuilder& __stdcall setExchange( const std::string& name ) override;
         virtual ISettingsBuilder& __stdcall setQueue( const std::string& name, FlagsType type ) override;
         virtual ISettingsBuilder& __stdcall setQueue( const std::string& name ) override;
         virtual ISettingsBuilder& __stdcall setLogin( const std::string& user, const std::string& password ) override;
         virtual ISettingsBuilder& __stdcall setConnection( const std::string& vhost ) override;

         virtual boost::shared_ptr< IHostSettings > getHost() const override;
         virtual boost::shared_ptr< IChannelSettings > getChannel() const override;
         virtual boost::shared_ptr< IExchangeSettings > getExchange() const override;
         virtual boost::shared_ptr< IQueueSettings > getQueue() const override;
         virtual boost::shared_ptr< ILoginSettings > getLogin() const override;
         virtual boost::shared_ptr< IConnectionSettings > getConnection() const override;

         virtual boost::shared_ptr< ISettings > build() const override;

         virtual ~SettingsBuilder() = default;

      protected:
         SettingsBuilder() = default;
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

#endif //__AMQP_SETTINGS_BUILDER_H_INCLUDED__
