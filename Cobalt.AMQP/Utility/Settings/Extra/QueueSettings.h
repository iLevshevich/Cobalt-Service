#ifndef __AMQP_QUEUE_SETTINGS_H_INCLUDED__
#define __AMQP_QUEUE_SETTINGS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class QueueSettings :
         public IQueueSettings,
         private boost::noncopyable {
      public:
         static boost::shared_ptr< IQueueSettings > __stdcall getInstance( const std::string& name, FlagsType type = FlagsType::durable ) {
            return make_shared_pool_enable< IQueueSettings, QueueSettings, boost::default_user_allocator_malloc_free >( name, type );
         }

         std::string getName() const override {
            return name_;
         }

         FlagsType getType() const override {
            return type_;
         }

         virtual ~QueueSettings() = default;

      protected:
         QueueSettings( const std::string& name, FlagsType type = FlagsType::durable ) :
            name_( name ),
            type_( type ) {
         }

      private:
         std::string name_;
         FlagsType type_;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_QUEUE_SETTINGS_H_INCLUDED__
