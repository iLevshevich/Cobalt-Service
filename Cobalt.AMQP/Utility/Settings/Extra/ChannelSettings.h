#ifndef __AMQP_CHANNEL_SETTINGS_H_INCLUDED__
#define __AMQP_CHANNEL_SETTINGS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class ChannelSettings :
         public IChannelSettings,
         private boost::noncopyable {
      public:
         static boost::shared_ptr< IChannelSettings > __stdcall getInstance( uint16_t prefetchCountQos, bool globalQos = false ) {
            return make_shared_pool_enable< IChannelSettings, ChannelSettings, boost::default_user_allocator_malloc_free >( prefetchCountQos, globalQos );
         }

         virtual uint16_t getPrefetchCountQos() const override {
            return prefetchCountQos_;
         }

         virtual bool getGlobalQos_() const override {
            return globalQos_;
         }

         virtual ~ChannelSettings() = default;

      protected:
         explicit ChannelSettings( uint16_t prefetchCountQos, bool globalQos = false ) :
            prefetchCountQos_( prefetchCountQos ),
            globalQos_( globalQos ) {
         }

      private:
         uint16_t prefetchCountQos_;
         bool globalQos_;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_CHANNEL_SETTINGS_H_INCLUDED__
