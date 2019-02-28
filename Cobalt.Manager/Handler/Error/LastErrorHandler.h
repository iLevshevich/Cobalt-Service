#ifndef __MANAGER_LAST_ERROR_HANDLER_H_INCLUDED__
#define __MANAGER_LAST_ERROR_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Error
      {
         template< class T >
         class LastErrorHandler:
            public ILastErrorHandler< T > {
         public:
            typedef typename ILastErrorHandler< T >::base_type base_type;
            typedef typename ILastErrorHandler< T >::message_type message_type;
            typedef typename ILastErrorHandler< T >::property_tree_base_type property_tree_base_type;

            typedef typename Utility::Traits< boost::mutex >::base_t mutex_base_type;

            static boost::shared_ptr< ILastErrorHandler< T > > __stdcall getInstance() {
               return Utility::make_shared_pool_enable< ILastErrorHandler< T >, LastErrorHandler< T >, boost::default_user_allocator_malloc_free >();
            }

            virtual void __stdcall setLastError( message_type message ) override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               message_ = message;
            }

            virtual property_tree_base_type getLastError() override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               boost::property_tree::ptree result;
               ///
               result.put( "error.message", message_ );
               ///
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

            virtual void cleanLastError() override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               message_ = base_type();
            }

            virtual typename std::enable_if< std::is_same< std::string, base_type >::value, bool >::type isLastErrorEmpty() override {
               return message_.empty();
            }

            virtual ~LastErrorHandler() = default;
         protected:
            LastErrorHandler() :
               mutex_(),
               message_() {
            }

         private:
            mutex_base_type mutex_;
            base_type message_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_LAST_ERROR_HANDLER_H_INCLUDED__
