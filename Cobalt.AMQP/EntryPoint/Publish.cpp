#include "../stdafx.h"

#include "../Utility/EnableMake.h"
#include "../Utility/FlagsType.h"
#include "../Utility/ExchangeType.h"
#include "../Utility/MakeObject.h"

#include "../Utility/Settings/Extra/IChannelSettings.h"
#include "../Utility/Settings/Extra/IConnectionSettings.h"
#include "../Utility/Settings/Extra/IExchangeSettings.h"
#include "../Utility/Settings/Extra/IHostSettings.h"
#include "../Utility/Settings/Extra/ILoginSettings.h"
#include "../Utility/Settings/Extra/IQueueSettings.h"

#include "../Utility/Settings/Extra/HostSettings.h"
#include "../Utility/Settings/Extra/ChannelSettings.h"
#include "../Utility/Settings/Extra/ExchangeSettings.h"
#include "../Utility/Settings/Extra/LoginSettings.h"
#include "../Utility/Settings/Extra/QueueSettings.h"
#include "../Utility/Settings/Extra/ConnectionSettings.h"

#include "../Utility/Settings/ISettings.h"
#include "../Utility/Settings/Settings.h"

#include "../Utility/Transaction/Transaction.h"

#include "../Poco/PocoHandler.h"

#include "IPublish.h"
#include "Publish.h"

namespace Cobalt
{
   namespace EntryPoint
   {
      void Publish::publishNoAck( std::function< std::string() > executor, const std::string& routingKey ) {
         AMQP::Login login( settings_->getLogin()->getUser(), settings_->getLogin()->getPassword() );
         AMQP::Connection connection( handler_.get(), login, settings_->getConnection()->getVirtualHost() );
         AMQP::Channel channel( &connection );

         channel.setQos( settings_->getChannel()->getPrefetchCountQos(), settings_->getChannel()->getGlobalQos_() );
         /**
         *  Declare an exchange
         *
         *  The following flags can be used for the exchange:
         *
         *      -   durable     exchange survives a broker restart
         *      -   autodelete  exchange is automatically removed when all connected queues are removed
         *      -   passive     only check if the exchange exist
         *      -   internal    create an internal exchange
         */
         channel.declareExchange( settings_->getExchange()->getName(), static_cast< AMQP::ExchangeType >(settings_->getExchange()->getType()) )
                .onSuccess( [&]() {
                      transaction_->transaction( [&]() {
                                                    const std::string data( executor() );
                                                    AMQP::Envelope env( data.c_str(), data.size() );
                                                    /**
                                                    *  Publish a message to an exchange
                                                    *
                                                    *  The following flags can be supplied:
                                                    *
                                                    *      -   mandatory   If set, server returns messages that are not sent to a queue
                                                    *      -   immediate   If set, server returns messages that can not immediately be forwarded to a consumer.
                                                    */
                                                    channel.publish( settings_->getExchange()->getName(), routingKey, env );
                                                 },
                                                 [&]() {
                                                    wait( TRY_QUIT_TIMEOUT );
                                                    quit();
                                                 }, channel );
                   } );

         handler_->loop();
      }

      void Publish::publishAck( std::function< std::string() > executor, const std::string& routingKey ) {
         AMQP::Login login( settings_->getLogin()->getUser(), settings_->getLogin()->getPassword() );
         AMQP::Connection connection( handler_.get(), login, settings_->getConnection()->getVirtualHost() );
         AMQP::Channel channel( &connection );

         channel.setQos( settings_->getChannel()->getPrefetchCountQos(), settings_->getChannel()->getGlobalQos_() );
         /**
         *  Declare an exchange
         *
         *  The following flags can be used for the exchange:
         *
         *      -   durable     exchange survives a broker restart
         *      -   autodelete  exchange is automatically removed when all connected queues are removed
         *      -   passive     only check if the exchange exist
         *      -   internal    create an internal exchange
         */
         channel.declareExchange( settings_->getExchange()->getName(), static_cast< AMQP::ExchangeType >(settings_->getExchange()->getType()) )
                .onSuccess( [&]() {
                      transaction_->transaction( [&]() {
                                                    const std::string data( executor() );
                                                    AMQP::Envelope env( data.c_str(), data.size() );
                                                    env.setPersistent();
                                                    /**
                                                    *  Publish a message to an exchange
                                                    *
                                                    *  The following flags can be supplied:
                                                    *
                                                    *      -   mandatory   If set, server returns messages that are not sent to a queue
                                                    *      -   immediate   If set, server returns messages that can not immediately be forwarded to a consumer.
                                                    */
                                                    channel.publish( settings_->getExchange()->getName(), routingKey, env );
                                                 },
                                                 [&]() {
                                                    wait( TRY_QUIT_TIMEOUT );
                                                    quit();
                                                 }, channel );
                   } );

         handler_->loop();
      }

      void Publish::publishNoAck( std::function< std::vector< std::string >() > executor, const std::string& routingKey ) {
         AMQP::Login login( settings_->getLogin()->getUser(), settings_->getLogin()->getPassword() );
         AMQP::Connection connection( handler_.get(), login, settings_->getConnection()->getVirtualHost() );
         AMQP::Channel channel( &connection );

         channel.setQos( settings_->getChannel()->getPrefetchCountQos(), settings_->getChannel()->getGlobalQos_() );
         /**
         *  Declare an exchange
         *
         *  The following flags can be used for the exchange:
         *
         *      -   durable     exchange survives a broker restart
         *      -   autodelete  exchange is automatically removed when all connected queues are removed
         *      -   passive     only check if the exchange exist
         *      -   internal    create an internal exchange
         */
         channel.declareExchange( settings_->getExchange()->getName(), static_cast< AMQP::ExchangeType >(settings_->getExchange()->getType()) )
                .onSuccess( [&]() {
                      transaction_->transaction( [&]() {
                                                    const std::vector< std::string > data( executor() );
                                                    for( std::vector< std::string >::const_iterator iter = data.begin(); iter != data.end(); ++iter ) {
                                                       AMQP::Envelope env( iter->c_str(), iter->size() );
                                                       /**
                                                       *  Publish a message to an exchange
                                                       *
                                                       *  The following flags can be supplied:
                                                       *
                                                       *      -   mandatory   If set, server returns messages that are not sent to a queue
                                                       *      -   immediate   If set, server returns messages that can not immediately be forwarded to a consumer.
                                                       */
                                                       channel.publish( settings_->getExchange()->getName(), routingKey, env );
                                                    }
                                                 },
                                                 [&]() {
                                                    wait( TRY_QUIT_TIMEOUT );
                                                    quit();
                                                 }, channel );
                   } );

         handler_->loop();
      }

      void Publish::publishAck( std::function< std::vector< std::string >() > executor, const std::string& routingKey ) {
         AMQP::Login login( settings_->getLogin()->getUser(), settings_->getLogin()->getPassword() );
         AMQP::Connection connection( handler_.get(), login, settings_->getConnection()->getVirtualHost() );
         AMQP::Channel channel( &connection );

         channel.setQos( settings_->getChannel()->getPrefetchCountQos(), settings_->getChannel()->getGlobalQos_() );
         /**
         *  Declare an exchange
         *
         *  The following flags can be used for the exchange:
         *
         *      -   durable     exchange survives a broker restart
         *      -   autodelete  exchange is automatically removed when all connected queues are removed
         *      -   passive     only check if the exchange exist
         *      -   internal    create an internal exchange
         */
         channel.declareExchange( settings_->getExchange()->getName(), static_cast< AMQP::ExchangeType >(settings_->getExchange()->getType()) )
                .onSuccess( [&]() {
                      transaction_->transaction( [&]() {
                                                    const std::vector< std::string > data( executor() );
                                                    for( std::vector< std::string >::const_iterator iter = data.begin(); iter != data.end(); ++iter ) {
                                                       AMQP::Envelope env( iter->c_str(), iter->size() );
                                                       env.setPersistent();
                                                       /**
                                                       *  Publish a message to an exchange
                                                       *
                                                       *  The following flags can be supplied:
                                                       *
                                                       *      -   mandatory   If set, server returns messages that are not sent to a queue
                                                       *      -   immediate   If set, server returns messages that can not immediately be forwarded to a consumer.
                                                       */
                                                       channel.publish( settings_->getExchange()->getName(), routingKey, env );
                                                    }
                                                 },
                                                 [&]() {
                                                    wait( TRY_QUIT_TIMEOUT );
                                                    quit();
                                                 }, channel );
                   } );

         handler_->loop();
      }

      void Publish::quit() {
         handler_->quit();
      }

      bool Publish::tryQuit() {
         return handler_->tryQuit();
      }

      bool Publish::isQuited() {
         return handler_->isQuited();
      }

      void __fastcall Publish::wait( size_t timeout ) const {
         while( handler_ && handler_.get() && handler_->tryQuit() ) {
            std::this_thread::sleep_for( std::chrono::milliseconds( timeout ) );
         }
      }

      Publish::Publish( const boost::shared_ptr< Utility::ISettings >& settings ) :
         settings_( settings ),
         handler_( Utility::make_shared_pool< Poco::PocoHandler, boost::default_user_allocator_malloc_free >( settings->getHost() ) ),
         transaction_( Utility::make_shared_pool< Utility::Transaction, boost::default_user_allocator_malloc_free >() ) {
      }

      boost::shared_ptr< IPublish > Publish::getInstance( const boost::shared_ptr< Utility::ISettings >& settings ) {
         return Utility::make_shared_pool_enable< IPublish, Publish, boost::default_user_allocator_malloc_free, boost::details::pool::default_mutex >( settings );
      }
   }
}
