#ifndef __MANAGER_I_QUEUE_HANDLER_H_INCLUDED__
#define __MANAGER_I_QUEUE_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Queue
      {
         template< class T, class U >
         class IQueueHandler:
            public State::IStateHandler,
            public Meta::IMetaHandler< U > {
         public:
            typedef typename Utility::Traits< T >::const_rvalue_reference_t push_arg_type;
            typedef typename Utility::Traits< std::function< void( typename Utility::Traits< T >::const_rvalue_reference_t, typename Utility::Traits< T >::const_reference_t ) > >::const_reference_t pop_arg_type;
            typedef typename State::IStateHandler::property_tree_base_type property_tree_base_type;

            virtual void __fastcall push( push_arg_type ) = 0;
            virtual void pop( pop_arg_type ) = 0;

            virtual bool isEmpty() const = 0;
            virtual size_t size() const = 0;

            virtual property_tree_base_type getQueueSize() = 0;

            virtual ~IQueueHandler() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_QUEUE_HANDLER_H_INCLUDED__
