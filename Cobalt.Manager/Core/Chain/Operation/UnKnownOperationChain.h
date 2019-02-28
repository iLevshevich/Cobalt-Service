#ifndef __MANAGER_UNKNOWN_OPERATION_CHAIN_H_INCLUDED__
#define __MANAGER_UNKNOWN_OPERATION_CHAIN_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Core
   {
      namespace Chain
      {
         class UnKnownOperationChain :
            public IOperationChain {
         public:
            typedef typename IOperationChain::request_type request_type;
            typedef typename IOperationChain::responce_type responce_type;

            typedef typename Utility::Traits< boost::shared_ptr< IOperationChain > >::const_reference_t chain_type;
            typedef typename Utility::Traits< boost::shared_ptr< IOperationChain > >::base_t chain_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Repository > >::const_reference_t repository_type;
            typedef typename Utility::Traits< boost::shared_ptr< Repository > >::base_t repository_base_type;

            typedef typename Utility::Traits< std::string >::const_reference_t message_type;
            typedef typename Utility::Traits< boost::property_tree::ptree >::base_t property_base_type;
            typedef typename Utility::Traits< boost::property_tree::ptree >::const_reference_t property_source_type;
            typedef typename Utility::Traits< boost::property_tree::ptree >::reference_t property_destination_type;
            typedef typename Utility::Traits< boost::property_tree::ptree::value_type >::const_reference_t property_value_type;

            static chain_base_type getInstance() {
               return Utility::make_shared_pool_enable< IOperationChain, UnKnownOperationChain, boost::default_user_allocator_malloc_free >();
            }

            responce_type __stdcall execute( request_type request ) override {
               return failed( "unknown operation" );
            }

            virtual ~UnKnownOperationChain() = default;

         private:
            std::tuple< bool, std::string > __stdcall failed( message_type t ) const {
               property_base_type status;
               status.put( "status", "failed" );

               property_base_type reason;
               reason.put( "reason", t );

               property_base_type failed;
               merge( status, failed );
               merge( reason, failed );

               return std::make_tuple( false, boost::lexical_cast< std::string >( failed ) );
            }

            void __stdcall merge( property_source_type source, property_destination_type dest ) const {
               for( property_value_type item : source ) {
                  dest.put_child( item.first, item.second );
               }
            }
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_UNKNOWN_OPERATION_CHAIN_H_INCLUDED__
