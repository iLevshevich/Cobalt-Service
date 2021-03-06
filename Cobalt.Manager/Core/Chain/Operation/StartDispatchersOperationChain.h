﻿#ifndef __MANAGER_START_DISPATCHERS_OPERATION_CHAIN_H_INCLUDED__
#define __MANAGER_START_DISPATCHERS_OPERATION_CHAIN_H_INCLUDED__

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
         class StartDispatchersOperationChain :
            public IOperationChain {
         public:
            typedef typename IOperationChain::request_type request_type;
            typedef typename IOperationChain::responce_type responce_type;

            typedef typename Utility::Traits< boost::shared_ptr< IOperationChain > >::const_reference_t chain_type;
            typedef typename Utility::Traits< boost::shared_ptr< IOperationChain > >::base_t chain_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Repository > >::const_reference_t repository_type;
            typedef typename Utility::Traits< boost::shared_ptr< Repository > >::base_t repository_base_type;

            static chain_base_type getInstance( repository_type repository ) {
               return Utility::make_shared_pool_enable< IOperationChain, StartDispatchersOperationChain, boost::default_user_allocator_malloc_free >( repository );
            }

            static chain_base_type getInstance( chain_type next, repository_type repository ) {
               return Utility::make_shared_pool_enable< IOperationChain, StartDispatchersOperationChain, boost::default_user_allocator_malloc_free >( next, repository );
            }

            responce_type __stdcall execute( request_type request ) override {
               const std::string operation( request.get< std::string >( "operation" ) );
               if( operation == OperationTypeToString( OperationType::StartDispatchers ) ) {
                  return repository_->start();
               }
               else {
                  if( next_.get() ) {
                     return next_->execute( request );
                  }
               }

               return responce_type();
            }

            virtual ~StartDispatchersOperationChain() = default;

         protected:
            explicit StartDispatchersOperationChain( repository_type repository ) :
               next_( nullptr ),
               repository_( repository ) {
            }

            explicit StartDispatchersOperationChain( chain_type next, repository_type repository ) :
               next_( next ),
               repository_( repository ) {
            }

         private:
            chain_base_type next_;
            repository_base_type repository_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_START_DISPATCHERS_OPERATION_CHAIN_H_INCLUDED__
