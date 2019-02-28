#ifndef __MANAGER_I_SETTINGS_H_INCLUDED__
#define __MANAGER_I_SETTINGS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Import
   {
      namespace Utility
      {
         template< ImportType _Type >
         class ISettings;

         template<>
         class ISettings< Import::ImportType::Amqp > {
         public:
            virtual boost::shared_ptr< IHostSettings > getHost() const = 0;
            virtual boost::shared_ptr< IChannelSettings > getChannel() const = 0;
            virtual boost::shared_ptr< IExchangeSettings > getExchange() const = 0;
            virtual boost::shared_ptr< IQueueSettings > getQueue() const = 0;
            virtual boost::shared_ptr< ILoginSettings > getLogin() const = 0;
            virtual boost::shared_ptr< IConnectionSettings > getConnection() const = 0;

            virtual ~ISettings() = default;
         };

         template<>
         class ISettings< Import::ImportType::Tcp > {
         public:
            virtual std::string getPort() const = 0;
            virtual std::string getHost() const = 0;

            virtual ~ISettings() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_SETTINGS_H_INCLUDED__
