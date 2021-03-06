﻿#ifndef __MANAGER_I_QUEUE_HANDLER_BUILDER_H_INCLUDED__
#define __MANAGER_I_QUEUE_HANDLER_BUILDER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Queue
      {
#pragma warning(disable:4348) //C4348 переопределение параметра по умолчанию
         template< class _Elem, std::size_t _Capacity = 4096, class _Meta = std::string >
         class IQueueHandlerBuilder {
         public:
            typedef typename Utility::Traits< boost::shared_ptr< State::IStateHandler > >::const_reference_t state_type;
            typedef typename Utility::Traits< State::IStateHandler >::base_t state_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< boost::lockfree::spsc_queue< _Elem, boost::lockfree::capacity< _Capacity > > > >::const_reference_t container_type;
            typedef typename Utility::Traits< boost::lockfree::spsc_queue< _Elem, boost::lockfree::capacity< _Capacity > > >::base_t container_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Meta::IMetaHandler< _Meta > > >::const_reference_t meta_type;
            typedef typename Utility::Traits< Meta::IMetaHandler< _Meta > >::base_t meta_base_type;

            virtual IQueueHandlerBuilder< _Elem, _Capacity, _Meta >& __fastcall setState( state_type f ) = 0;
            virtual IQueueHandlerBuilder< _Elem, _Capacity, _Meta >& __fastcall setContainer( container_type f ) = 0;
            virtual IQueueHandlerBuilder< _Elem, _Capacity, _Meta >& __fastcall setMeta( meta_type f ) = 0;

            virtual boost::shared_ptr< state_base_type > getState() const = 0;
            virtual boost::shared_ptr< container_base_type > getContainer() const = 0;
            virtual boost::shared_ptr< meta_base_type > getMeta() const = 0;

            virtual boost::shared_ptr< IQueueHandler< _Elem, _Meta > > build() const = 0;

            virtual ~IQueueHandlerBuilder() = default;
         };
#pragma warning(default:4348)
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_QUEUE_HANDLER_BUILDER_H_INCLUDED__
