#ifndef __MANAGER_INPUT_HANDLER_H_INCLUDED__
#define __MANAGER_INPUT_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Input
      {
         template< Import::ImportType _Type >
         class InputHandler;

         template<>
         class InputHandler< Import::ImportType::Amqp > :
            public IInputHandler< std::string > {
         public:
            typedef typename IStateHandler::property_tree_base_type property_tree_base_type;
            typedef typename IInputHandler< std::string >::base_type base_type;
            typedef typename IInputHandler< std::string >::handler_arg_type handler_arg_type;

            virtual property_tree_base_type getState() const override {
               return state_->getState();
            }

            virtual void start() override {
               COBALT_HANDLER_ERROR_GUARD_
                  COBALT_HANDLER_STATE_GUARD(isRunning())
                  ///
                  const boost::shared_ptr< Import::IConsume< Import::ImportType::Amqp > > consumer = factory_->getConsumer( settings_ );
                  consumer_ = Utility::make_async( consumer,
                                                   [&](const boost::shared_ptr< Import::IConsume< Import::ImportType::Amqp > >& consumer_) {
                                                      COBALT_HANDLER_ERROR_GUARD_
                                                         ///
                                                         boost::this_thread::interruption_point();
                                                         ///
                                                         acknowledge_->consume( consumer_, std::bind( &InputHandler::consume, this, std::placeholders::_1 ), key_ );
                                                         ///
                                                         boost::this_thread::interruption_point();
                                                         ///
                                                      COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
                                                   }, consumer );
                  state_->start();
                  monitor_->onStart( meta_->getId() );
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
            }

            virtual void stop() override {
               COBALT_HANDLER_ERROR_GUARD_
                  COBALT_HANDLER_STATE_GUARD(isStopped())
                  ///
                  if( consumer_ && consumer_.get() && !consumer_->isClosed() ) {
                     consumer_->close();

                     wait( WAIT_STOP_TIMEOUT );
                  }
                  consumer_.reset();
                  ///
                  state_->stop();
                  monitor_->onStop( meta_->getId() );
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
            }

            virtual void abort() override {
               state_->abort();
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

            virtual base_type getId() override {
               return meta_->getId();
            }

            virtual base_type getDescription() override {
               return meta_->getDescription();
            }

            virtual ~InputHandler() = default;

         protected:
            explicit InputHandler( const IInputHandlerBuilder< std::string, InputHandler< Import::ImportType::Amqp >, Import::ImportType::Amqp >& builder ) :
               key_( builder.getKey() ),
               consumer_( nullptr ),
               acknowledge_( builder.getAcknowledge() ),
               monitor_( builder.getMonitor() ),
               state_( builder.getState() ),
               factory_( builder.getFactory() ),
               meta_( builder.getMeta() ),
               settings_( builder.getSettings() ) {
            }

            virtual void __fastcall consume( handler_arg_type message ) override {
               COBALT_HANDLER_ERROR_GUARD_
                  ///
                  boost::this_thread::interruption_point();
                  ///
                  {
                     boost::this_thread::disable_interruption di;
                     ///
                     monitor_->onBeforePush( message, meta_->getId() );
                     monitor_->onPush( message, meta_->getId() );
                     monitor_->onAfterPush( message, meta_->getId() );
                     ///
                  }
                  ///
                  boost::this_thread::interruption_point();
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
            }

         private:
            enum { WAIT_STOP_TIMEOUT = 10 }; //milliseconds
            void __fastcall wait( size_t timeout ) const {
               while( consumer_ && consumer_.get() && !consumer_->isClosed() ) {
                  std::this_thread::sleep_for( std::chrono::milliseconds( timeout ) );
               }
            }

            std::string key_;
            boost::shared_ptr< Utility::Async< Import::IConsume< Import::ImportType::Amqp > > > consumer_;
            boost::shared_ptr< IInputHandlerAcknowledge< Import::ImportType::Amqp > > acknowledge_;
            boost::shared_ptr< Monitor::IInputMonitorHandler< std::string > > monitor_;
            boost::shared_ptr< State::IStateHandler > state_;
            boost::shared_ptr< Factory::IImportFactory< Import::ImportType::Amqp > > factory_;
            boost::shared_ptr< Meta::IMetaHandler< std::string > > meta_;
            boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Amqp > > settings_;
         };

         template<>
         class InputHandler< Import::ImportType::Tcp > :
            public IInputHandler< std::string > {
         public:
            typedef typename IStateHandler::property_tree_base_type property_tree_base_type;
            typedef typename IInputHandler< std::string >::base_type base_type;
            typedef typename IInputHandler< std::string >::handler_arg_type handler_arg_type;

            virtual property_tree_base_type getState() const override {
               return state_->getState();
            }

            virtual void start() override {
               COBALT_HANDLER_ERROR_GUARD_
                  COBALT_HANDLER_STATE_GUARD(isRunning())
                  ///
                  const boost::shared_ptr< Import::IConsume< Import::ImportType::Tcp > > consumer = factory_->getConsumer( settings_ );
                  consumer_ = Utility::make_async( consumer,
                                                   [&](const boost::shared_ptr< Import::IConsume< Import::ImportType::Tcp > >& consumer_) {
                                                      COBALT_HANDLER_ERROR_GUARD_
                                                         ///
                                                         boost::this_thread::interruption_point();
                                                         ///
                                                         consumer_->consume( std::bind( &InputHandler::consume, this, std::placeholders::_1 ) );
                                                         ///
                                                         boost::this_thread::interruption_point();
                                                         ///
                                                      COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
                                                   }, consumer );
                  state_->start();
                  monitor_->onStart( meta_->getId() );
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
            }

            virtual void stop() override {
               COBALT_HANDLER_ERROR_GUARD_
                  COBALT_HANDLER_STATE_GUARD(isStopped())
                  ///
                  if( consumer_ && consumer_.get() && !consumer_->isClosed() ) {
                     consumer_->close();

                     wait( WAIT_STOP_TIMEOUT );
                  }

                  if( consumer_ && consumer_.get() && !consumer_->completeClose() ) {
                     throw std::logic_error( "Invalid operation" );
                  }
                  consumer_.reset();
                  ///
                  state_->stop();
                  monitor_->onStop( meta_->getId() );
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
            }

            virtual void abort() override {
               state_->abort();
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

            virtual base_type getId() override {
               return meta_->getId();
            }

            virtual base_type getDescription() override {
               return meta_->getDescription();
            }

            virtual ~InputHandler() = default;

         protected:
            explicit InputHandler( const IInputHandlerBuilder< std::string, InputHandler< Import::ImportType::Tcp >, Import::ImportType::Tcp >& builder ) :
               consumer_( nullptr ),
               monitor_( builder.getMonitor() ),
               state_( builder.getState() ),
               factory_( builder.getFactory() ),
               meta_( builder.getMeta() ),
               settings_( builder.getSettings() ) {
            }

            virtual void __fastcall consume( handler_arg_type message ) override {
               COBALT_HANDLER_ERROR_GUARD_
                  ///
                  boost::this_thread::interruption_point();
                  ///
                  {
                     boost::this_thread::disable_interruption di;
                     ///
                     monitor_->onBeforePush( message, meta_->getId() );
                     monitor_->onPush( message, meta_->getId() );
                     monitor_->onAfterPush( message, meta_->getId() );
                     ///
                  }
                  ///
                  boost::this_thread::interruption_point();
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
            }

         private:
            enum { WAIT_STOP_TIMEOUT = 10 }; //milliseconds
            void __fastcall wait( size_t timeout ) const {
               while( consumer_ && consumer_.get() && !consumer_->isClosed() ) {
                  std::this_thread::sleep_for( std::chrono::milliseconds( timeout ) );
               }
            }

            boost::shared_ptr< Utility::Async< Import::IConsume< Import::ImportType::Tcp > > > consumer_;
            boost::shared_ptr< Monitor::IInputMonitorHandler< std::string > > monitor_;
            boost::shared_ptr< State::IStateHandler > state_;
            boost::shared_ptr< Factory::IImportFactory< Import::ImportType::Tcp > > factory_;
            boost::shared_ptr< Meta::IMetaHandler< std::string > > meta_;
            boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Tcp > > settings_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_INPUT_HANDLER_H_INCLUDED__
