#ifndef __MANAGER_I_SETTINGS_BUILDER_H_INCLUDED__
#define __MANAGER_I_SETTINGS_BUILDER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Import
   {
      namespace Utility
      {
         template< ImportType _Type >
         class ISettingsBuilder;

         template<>
         class ISettingsBuilder< Import::ImportType::Amqp > {
         public:
            virtual ISettingsBuilder& __stdcall setHost( const std::string& host, const uint16_t port ) = 0;
            virtual ISettingsBuilder& __stdcall setChannel( uint16_t prefetchCountQos, bool globalQos = false ) = 0;
            virtual ISettingsBuilder& __stdcall setExchange( const std::string& name, ExchangeType type ) = 0;
            virtual ISettingsBuilder& __stdcall setExchange( const std::string& name ) = 0;
            virtual ISettingsBuilder& __stdcall setQueue( const std::string& name, FlagsType type ) = 0;
            virtual ISettingsBuilder& __stdcall setQueue( const std::string& name ) = 0;
            virtual ISettingsBuilder& __stdcall setLogin( const std::string& user, const std::string& password ) = 0;
            virtual ISettingsBuilder& __stdcall setConnection( const std::string& vhost ) = 0;

            virtual boost::shared_ptr< IHostSettings > getHost() const = 0;
            virtual boost::shared_ptr< IChannelSettings > getChannel() const = 0;
            virtual boost::shared_ptr< IExchangeSettings > getExchange() const = 0;
            virtual boost::shared_ptr< IQueueSettings > getQueue() const = 0;
            virtual boost::shared_ptr< ILoginSettings > getLogin() const = 0;
            virtual boost::shared_ptr< IConnectionSettings > getConnection() const = 0;

            virtual boost::shared_ptr< ISettings< Import::ImportType::Amqp > > build() const = 0;

            virtual ~ISettingsBuilder() = default;
         };

         template<>
         class ISettingsBuilder< Import::ImportType::Tcp > {
         public:
            virtual ISettingsBuilder& __stdcall setPort( const std::string& port ) = 0;
            virtual ISettingsBuilder& __stdcall setHost( const std::string& host ) = 0;

            virtual std::string getPort() const = 0;
            virtual std::string getHost() const = 0;

            virtual boost::shared_ptr< ISettings< Import::ImportType::Tcp > > build() const = 0;

            virtual ~ISettingsBuilder() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_SETTINGS_BUILDER_H_INCLUDED__
