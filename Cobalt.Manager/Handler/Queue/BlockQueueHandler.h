#ifndef __MANAGER_BLOCK_QUEUE_HANDLER_H_INCLUDED__
#define __MANAGER_BLOCK_QUEUE_HANDLER_H_INCLUDED__

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
         /**
         * Requirements:
         *  - _Elem must have a default constructor
         *  - _Elem must be copyable
         */
#pragma warning(disable:4348) //C4348 переопределение параметра по умолчанию
         template< class _Elem, class _Meta = std::string >
         class BlockQueueHandler :
            public IQueueHandler< _Elem, _Meta > {
         public:
            typedef typename IQueueHandler< _Elem, _Meta >::push_arg_type push_arg_type;
            typedef typename IQueueHandler< _Elem, _Meta >::pop_arg_type pop_arg_type;
            typedef typename IQueueHandler< _Elem, _Meta >::property_tree_base_type property_tree_base_type;

            virtual void __fastcall push( push_arg_type t ) override {
               COBALT_HANDLER_STATE_GUARD( isStopped() )
               ///
               container_->push( std::move( t ) );
            }

            virtual void pop( pop_arg_type f ) override {
               COBALT_HANDLER_STATE_GUARD( isStopped() )
               ///
               operation_ = Utility::make_async( [=]() {
                     doPop( f );
                     completePop( f );
                  } );
            }

            virtual bool isEmpty() const override {
               return container_->isEmpty();
            }

            virtual std::size_t size() const override {
               return container_->size();
            }

            virtual property_tree_base_type getQueueSize() override {
               boost::property_tree::ptree result;
               ///
               result.put("queue.size", size());
               ///
               return Utility::make_shared_pool< boost::property_tree::ptree >(result);
            }

            virtual property_tree_base_type getState() const override {
               return state_->getState();
            }

            virtual void start() override {
               state_->start();
            }

            virtual void stop() override {
			   state_->stop();
			   ///
               wait( WAIT_STOP_TIMEOUT );
            }

            virtual void abort() override {
               state_->abort();
            }

            virtual std::string getId() override {
               return meta_->getId();
            }

            virtual std::string getDescription() override {
               return meta_->getDescription();
            }

            virtual bool isRunning() const override {
               return state_->isRunning();
            }

            virtual bool isStopped() const override {
               return state_->isStopped();
            }

            virtual bool isAborted() const override {
               return state_->isAborted();
            }

            virtual ~BlockQueueHandler() = default;

         protected:
            explicit BlockQueueHandler( const IBlockQueueHandlerBuilder< _Elem, _Meta >& builder ) :
               state_( builder.getState() ),
               container_( builder.getContainer() ),
               meta_( builder.getMeta() ) {
            }

            void doPop( pop_arg_type f ) {
               while( !isStopped() ) {
                  f( std::forward< _Elem >(container_->pop()), meta_->getId() );
               }
            }

            void completePop( pop_arg_type f ) {
               while( !isEmpty() ) {
                  f( std::forward< _Elem >(container_->pop()), meta_->getId() );
               }
            }

            enum { WAIT_STOP_TIMEOUT = 100 }; //milliseconds
            void __fastcall wait( size_t timeout ) const {
               while( !isEmpty() ) {
                  std::this_thread::sleep_for( std::chrono::milliseconds( timeout ) );
               }
            }

         private:
            boost::shared_ptr< Utility::Async1st< > > operation_;

            boost::shared_ptr< State::IStateHandler > state_;
            boost::shared_ptr< BlockQueue< _Elem > > container_;
            boost::shared_ptr< Meta::IMetaHandler< std::string > > meta_;
         };
#pragma warning(default:4348)
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_BLOCK_QUEUE_HANDLER_H_INCLUDED__
