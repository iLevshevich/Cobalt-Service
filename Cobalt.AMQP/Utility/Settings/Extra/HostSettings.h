#ifndef __AMQP_HOST_SETTINGS_H_INCLUDED__
#define __AMQP_HOST_SETTINGS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class HostSettings :
         public IHostSettings,
         private boost::noncopyable {
      public:
         static boost::shared_ptr< IHostSettings > __stdcall getInstance( const std::string& host, const uint16_t port ) {
            return make_shared_pool_enable< IHostSettings, HostSettings, boost::default_user_allocator_malloc_free >( host, port );
         }

         virtual std::string getHost() const override {
            return host_;
         }

         virtual uint16_t getPort() const override {
            return port_;
         }

         virtual ~HostSettings() = default;

      protected:
         HostSettings( const std::string& host, const uint16_t port ) :
            host_( host ),
            port_( port ) {
         }

      private:
         std::string host_;
         uint16_t port_;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_HOST_SETTINGS_H_INCLUDED__
