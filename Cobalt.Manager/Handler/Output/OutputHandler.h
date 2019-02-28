#ifndef __MANAGER_OUTPUT_HANDLER_H_INCLUDED__
#define __MANAGER_OUTPUT_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Output
      {
         template< Import::ImportType _Type >
         class OutputHandler;

         template<>
         class OutputHandler< Import::ImportType::Amqp > :
            public IOutputHandler< std::string > {
         public:
            typedef typename IStateHandler::property_tree_base_type property_tree_base_type;
            typedef typename IOutputHandler< std::string >::base_type base_type;
            typedef typename IOutputHandler< std::string >::handler_arg_1_type handler_arg_1_type;
            typedef typename IOutputHandler< std::string >::handler_arg_2_type handler_arg_2_type;

            virtual property_tree_base_type getState() const override {
               return state_->getState();
            }

            virtual void start() override {
               COBALT_HANDLER_ERROR_GUARD_
                  COBALT_HANDLER_STATE_GUARD(isRunning())
                  ///
                  state_->start();
                  monitor_->onStart( meta_->getId() );
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
            }

            virtual void stop() override {
               COBALT_HANDLER_ERROR_GUARD_
                  COBALT_HANDLER_STATE_GUARD(isStopped())
                  ///
                  if( publisher_ && publisher_.get() && !publisher_->isClosed() ) {
                     publisher_->close();

                     wait( WAIT_STOP_TIMEOUT );
                  }
                  publisher_.reset();
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

            virtual void __fastcall produce( handler_arg_1_type message ) override {
               COBALT_HANDLER_ERROR_GUARD_
                  COBALT_HANDLER_STATE_GUARD(isStopped())
                  ///
                  const boost::shared_ptr< Import::IPublish< Import::ImportType::Amqp > > publisher = factory_->getPublisher( settings_ );
                  publisher_ = Utility::make_async( publisher,
                                                    [&, async_message_ = std::move(message)](const boost::shared_ptr< Import::IPublish< Import::ImportType::Amqp > >& publisher_) mutable -> void {
                                                       COBALT_HANDLER_ERROR_GUARD_
                                                          ///
														  boost::this_thread::disable_interruption di;
                                                          ///
                                                          acknowledge_->publish( publisher_,
                                                                                 [&, acknowledge_message_ = std::move(async_message_)]() mutable -> handler_arg_1_type {
																				    ///
																				    boost::this_thread::disable_interruption di;
																				    ///
                                                                                    return publish( std::move(acknowledge_message_) );
                                                                                 },
                                                                                 key_ );
                                                       COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
                                                    }, publisher );
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
            }

            virtual void __fastcall produce( handler_arg_2_type messages ) override {
               COBALT_HANDLER_ERROR_GUARD_
                  COBALT_HANDLER_STATE_GUARD(isStopped())
                  ///
                  const boost::shared_ptr< Import::IPublish< Import::ImportType::Amqp > > publisher = factory_->getPublisher( settings_ );
                  publisher_ = Utility::make_async( publisher,
                                                    [&, async_messages_ = std::move(messages)](const boost::shared_ptr< Import::IPublish< Import::ImportType::Amqp > >& publisher_) {
                                                       COBALT_HANDLER_ERROR_GUARD_
														  ///
														  boost::this_thread::disable_interruption di;
														  ///
                                                          acknowledge_->publish( publisher_,
                                                                                 [&, acknowledge_messages_ = std::move(async_messages_)]() -> handler_arg_2_type {
																				    ///
																				    boost::this_thread::disable_interruption di;
																				    ///
                                                                                    return publish( std::move(acknowledge_messages_) );
                                                                                 },
                                                                                 key_ );
                                                       COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
                                                    }, publisher );
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
            }

            virtual void wait() const override {
               wait( WAIT_PRODUCE_TIMEOUT );
            }

            virtual ~OutputHandler() = default;

         protected:
            explicit OutputHandler( const IOutputHandlerBuilder< std::string, OutputHandler< Import::ImportType::Amqp >, Import::ImportType::Amqp >& builder ) :
               key_( builder.getKey() ),
               publisher_( nullptr ),
               acknowledge_( builder.getAcknowledge() ),
               monitor_( builder.getMonitor() ),
               state_( builder.getState() ),
               factory_( builder.getFactory() ),
               meta_( builder.getMeta() ),
               settings_( builder.getSettings() ) {
            }

            virtual handler_arg_1_type __fastcall publish( handler_arg_1_type message ) override {
               COBALT_HANDLER_ERROR_GUARD_
                  ///
                  boost::this_thread::interruption_point();
                  ///
                  {
                     boost::this_thread::disable_interruption di;
                     ///
                     monitor_->onBeforePop( message, meta_->getId() );
                     monitor_->onPop( message, meta_->getId() );
                     monitor_->onAfterPop( handler_arg_1_type( message ), meta_->getId() );
                     ///
                  }
                  ///
                  boost::this_thread::interruption_point();
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
               ///
               return std::move( message );
            }

            virtual handler_arg_2_type __fastcall publish( handler_arg_2_type messages ) override {
               COBALT_HANDLER_ERROR_GUARD_
                  ///
                  boost::this_thread::interruption_point();
                  ///
                  {
                     boost::this_thread::disable_interruption di;
                     ///
                     for( const base_type& message : messages ) {
                        publish( std::move( message ) );
                     }
                     ///
                  }
                  ///
                  boost::this_thread::interruption_point();
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
               ///
               return std::move( messages );
            }

         private:
            enum { WAIT_PRODUCE_TIMEOUT = 10 }; //milliseconds
            enum { WAIT_STOP_TIMEOUT = 100 }; //milliseconds
            void __fastcall wait( size_t timeout ) const {
               while( publisher_ && publisher_.get() && !publisher_->isClosed() ) {
                  std::this_thread::sleep_for( std::chrono::milliseconds( timeout ) );
               }
            }

            std::string key_;
            boost::shared_ptr< Utility::Async< Import::IPublish< Import::ImportType::Amqp > > > publisher_;
            boost::shared_ptr< IOutputHandlerAcknowledge< Import::ImportType::Amqp > > acknowledge_;
            boost::shared_ptr< Monitor::IOutputMonitorHandler< std::string > > monitor_;
            boost::shared_ptr< State::IStateHandler > state_;
            boost::shared_ptr< Factory::IImportFactory< Import::ImportType::Amqp > > factory_;
            boost::shared_ptr< Meta::IMetaHandler< std::string > > meta_;
            boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Amqp > > settings_;
         };

         template<>
         class OutputHandler< Import::ImportType::Tcp > :
            public IOutputHandler< std::string > {
         public:
            typedef typename IStateHandler::property_tree_base_type property_tree_base_type;
            typedef typename IOutputHandler< std::string >::base_type base_type;
            typedef typename IOutputHandler< std::string >::handler_arg_1_type handler_arg_1_type;
            typedef typename IOutputHandler< std::string >::handler_arg_2_type handler_arg_2_type;

            virtual property_tree_base_type getState() const override {
               return state_->getState();
            }

            virtual void start() override {
               COBALT_HANDLER_ERROR_GUARD_
                  COBALT_HANDLER_STATE_GUARD(isRunning())
                  ///
                  state_->start();
                  monitor_->onStart( meta_->getId() );
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
            }

            virtual void stop() override {
               COBALT_HANDLER_ERROR_GUARD_
                  COBALT_HANDLER_STATE_GUARD(isStopped())
                  ///
                  if( publisher_ && publisher_.get() && !publisher_->isClosed() ) {
                     publisher_->close();

                     wait( WAIT_STOP_TIMEOUT );
                  }

                  if( publisher_ && publisher_.get() && !publisher_->completeClose() ) {
                     throw std::logic_error( "Invalid operation" );
                  }
                  publisher_.reset();
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

            virtual void __fastcall produce( handler_arg_1_type message ) override {
               COBALT_HANDLER_ERROR_GUARD_
                  COBALT_HANDLER_STATE_GUARD(isStopped())
                  ///
                  const boost::shared_ptr< Import::IPublish< Import::ImportType::Tcp > > publisher = factory_->getPublisher( settings_ );
                  publisher_ = Utility::make_async( publisher,
                                                    [&, async_message_ = std::move(message)](const boost::shared_ptr< Import::IPublish< Import::ImportType::Tcp > >& publisher_) mutable -> void {
                                                       COBALT_HANDLER_ERROR_GUARD_
                                                          ///
                                                          boost::this_thread::disable_interruption di;
                                                          ///
														  publisher_->publish([&, acknowledge_message_ = std::move(async_message_)]() mutable -> handler_arg_1_type {
															  ///
															  boost::this_thread::disable_interruption di;
															  ///
															return publish(std::move(acknowledge_message_));
														  });
                                                       COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
                                                    }, publisher );
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
            }

            virtual void __fastcall produce( handler_arg_2_type messages ) override {
               COBALT_HANDLER_ERROR_GUARD_
                  COBALT_HANDLER_STATE_GUARD(isStopped())
                  ///
                  throw std::logic_error( "Unsupported operation" );
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
            }

            virtual void wait() const override {
               wait( WAIT_PRODUCE_TIMEOUT );
            }

            virtual ~OutputHandler() = default;

         protected:
            explicit OutputHandler( const IOutputHandlerBuilder< std::string, OutputHandler< Import::ImportType::Tcp >, Import::ImportType::Tcp >& builder ) :
               publisher_( nullptr ),
               monitor_( builder.getMonitor() ),
               state_( builder.getState() ),
               factory_( builder.getFactory() ),
               meta_( builder.getMeta() ),
               settings_( builder.getSettings() ) {
            }

            virtual handler_arg_1_type __fastcall publish( handler_arg_1_type message ) override {
               COBALT_HANDLER_ERROR_GUARD_
                  ///
                  boost::this_thread::interruption_point();
                  ///
                  {
                     boost::this_thread::disable_interruption di;
                     ///
                     monitor_->onBeforePop( message, meta_->getId() );
                     monitor_->onPop( message, meta_->getId() );
                     monitor_->onAfterPop( handler_arg_1_type( message ), meta_->getId() );
                     ///
                  }
                  ///
                  boost::this_thread::interruption_point();
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
               ///
               return std::move( message );
            }

            virtual handler_arg_2_type __fastcall publish( handler_arg_2_type messages ) override {
               COBALT_HANDLER_ERROR_GUARD_
                  ///
                  throw std::logic_error( "Unsupported operation" );
                  ///
               COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
               ///
               return std::move( messages );
            }

         private:
            enum { WAIT_PRODUCE_TIMEOUT = 10 }; //milliseconds
            enum { WAIT_STOP_TIMEOUT = 100 }; //milliseconds
            void __fastcall wait( size_t timeout ) const {
               while( publisher_ && publisher_.get() && !publisher_->isClosed() ) {
                  std::this_thread::sleep_for( std::chrono::milliseconds( timeout ) );
               }
            }

            boost::shared_ptr< Utility::Async< Import::IPublish< Import::ImportType::Tcp > > > publisher_;
            boost::shared_ptr< Monitor::IOutputMonitorHandler< std::string > > monitor_;
            boost::shared_ptr< State::IStateHandler > state_;
            boost::shared_ptr< Factory::IImportFactory< Import::ImportType::Tcp > > factory_;
            boost::shared_ptr< Meta::IMetaHandler< std::string > > meta_;
            boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Tcp > > settings_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_OUTPUT_HANDLER_H_INCLUDED__
