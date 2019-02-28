#ifndef __MANAGER_BLOCK_QUEUE_HANDLER_BUILDER_H_INCLUDED__
#define __MANAGER_BLOCK_QUEUE_HANDLER_BUILDER_H_INCLUDED__

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
         template< class _Elem, class _Meta = std::string >
         class BlockQueueHandlerBuilder :
            public IBlockQueueHandlerBuilder< _Elem, _Meta > {
         public:
            typedef typename IBlockQueueHandlerBuilder< _Elem, _Meta >::state_type state_type;
            typedef typename IBlockQueueHandlerBuilder< _Elem, _Meta >::state_base_type state_base_type;

            typedef typename IBlockQueueHandlerBuilder< _Elem, _Meta >::container_type container_type;
            typedef typename IBlockQueueHandlerBuilder< _Elem, _Meta >::container_base_type container_base_type;

            typedef typename IBlockQueueHandlerBuilder< _Elem, _Meta >::meta_type meta_type;
            typedef typename IBlockQueueHandlerBuilder< _Elem, _Meta >::meta_base_type meta_base_type;

            BlockQueueHandlerBuilder() :
               state_(nullptr),
               container_(nullptr),
               meta_(nullptr) {
            }

            virtual IBlockQueueHandlerBuilder< _Elem, _Meta >& __fastcall setState(state_type f) override {
               state_ = f;
               return *this;
            }

            virtual IBlockQueueHandlerBuilder< _Elem, _Meta >& __fastcall setContainer(container_type f) override {
               container_ = f;
               return *this;
            }

            virtual IBlockQueueHandlerBuilder< _Elem, _Meta >& __fastcall setMeta(meta_type f) override {
               meta_ = f;
               return *this;
            }

            virtual boost::shared_ptr< state_base_type > getState() const override {
               return state_;
            }

            virtual boost::shared_ptr< container_base_type > getContainer() const override {
               return container_;
            }

            virtual boost::shared_ptr< meta_base_type > getMeta() const override {
               return meta_;
            }

            virtual boost::shared_ptr< IQueueHandler< _Elem, _Meta > > build() const override {
               return Utility::make_shared_pool_enable< IQueueHandler< _Elem, _Meta >, BlockQueueHandler< _Elem, _Meta >, boost::default_user_allocator_malloc_free >(*this);
            }

            virtual ~BlockQueueHandlerBuilder() = default;

         private:
            boost::shared_ptr< state_base_type > state_;
            boost::shared_ptr< container_base_type > container_;
            boost::shared_ptr< meta_base_type > meta_;
         };
#pragma warning(default:4348)
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_BLOCK_QUEUE_HANDLER_BUILDER_H_INCLUDED__
