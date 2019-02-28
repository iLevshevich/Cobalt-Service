#ifndef __AMQP_EXCHANGE_SETTINGS_H_INCLUDED__
#define __AMQP_EXCHANGE_SETTINGS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class ExchangeSettings :
         public IExchangeSettings,
         private boost::noncopyable {
      public:
         static boost::shared_ptr< IExchangeSettings > __stdcall getInstance( const std::string& name, ExchangeType type = ExchangeType::direct ) {
            return make_shared_pool_enable< IExchangeSettings, ExchangeSettings, boost::default_user_allocator_malloc_free >( name, type );
         }

         virtual std::string getName() const override {
            return name_;
         }

         virtual ExchangeType getType() const override {
            return type_;
         }

         virtual ~ExchangeSettings() = default;

      protected:
         ExchangeSettings( const std::string& name, ExchangeType type = ExchangeType::direct ) :
            name_( name ),
            type_( type ) {
         }

      private:
         std::string name_;
         ExchangeType type_;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_EXCHANGE_SETTINGS_H_INCLUDED__
