#ifndef __AMQP_CONNECTION_SETTINGS_H_INCLUDED__
#define __AMQP_CONNECTION_SETTINGS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class ConnectionSettings :
         public IConnectionSettings,
         private boost::noncopyable {
      public:
         static boost::shared_ptr< IConnectionSettings > __stdcall getInstance( const std::string& vhost ) {
            return make_shared_pool_enable< IConnectionSettings, ConnectionSettings, boost::default_user_allocator_malloc_free >( vhost );
         }

         virtual std::string getVirtualHost() const override {
            return vhost_;
         }

         virtual ~ConnectionSettings() = default;

      protected:
         ConnectionSettings( const std::string& vhost ) :
            vhost_( vhost ) {
         }

      private:
         std::string vhost_;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_CONNECTION_SETTINGS_H_INCLUDED__
