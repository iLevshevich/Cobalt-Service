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

#include "../Poco/PocoHandler.h"

#include "IConsume.h"
#include "Consume.h"

namespace Cobalt
{
   namespace EntryPoint
   {
      void Consume::consumeNoAck( std::function< void( const std::string&& ) > executor, const std::string& routingKey ) {
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
                      /**
                      *  Declare a queue
                      *
                      *  The flags can be a combination of the following values:
                      *
                      *      -   durable     queue survives a broker restart
                      *      -   autodelete  queue is automatically removed when all connected consumers are gone
                      *      -   passive     only check if the queue exist
                      *      -   exclusive   the queue only exists for this connection, and is automatically removed when connection is gone
                      */
                      channel.declareQueue( settings_->getQueue()->getName(), settings_->getQueue()->getType() )
                             .onSuccess( [&](const std::string& name, int msgcount, int consumercount) {
                                   channel.bindQueue( settings_->getExchange()->getName(), settings_->getQueue()->getName(), routingKey );
                                   /**
                                   *  Tell the RabbitMQ server that we're ready to consume messages
                                   *
                                   *  The following flags are supported:
                                   *
                                   *      -   nolocal             if set, messages published on this channel are not also consumed
                                   *      -   noack               if set, consumed messages do not have to be acked, this happens automatically
                                   *      -   exclusive           request exclusive access, only this consumer can access the queue
                                   */
                                   channel.consume( settings_->getQueue()->getName(), Utility::FlagsType::noack )
                                          .onReceived( [&](const AMQP::Message& message, uint64_t deliveryTag, bool redelivered) {
#pragma warning(disable:4244) //C4244 преобразование "uint64_t" в "unsigned int", возможна потеря данных
                                                executor( std::move( std::string( message.body(), message.bodySize() ) ) );
#pragma warning(default:4244)
                                             } );
                                } );
                   } );

         handler_->loop();
      }

      void Consume::consumeAck( std::function< void( const std::string&& ) > executor, const std::string& routingKey ) {
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
                      /**
                      *  Declare a queue
                      *
                      *  The flags can be a combination of the following values:
                      *
                      *      -   durable     queue survives a broker restart
                      *      -   autodelete  queue is automatically removed when all connected consumers are gone
                      *      -   passive     only check if the queue exist
                      *      -   exclusive   the queue only exists for this connection, and is automatically removed when connection is gone
                      */
                      channel.declareQueue( settings_->getQueue()->getName(), settings_->getQueue()->getType() )
                             .onSuccess( [&](const std::string& name, int msgcount, int consumercount) {
                                   channel.bindQueue( settings_->getExchange()->getName(), settings_->getQueue()->getName(), routingKey );
                                   /**
                                   *  Tell the RabbitMQ server that we're ready to consume messages
                                   *
                                   *  The following flags are supported:
                                   *
                                   *      -   nolocal             if set, messages published on this channel are not also consumed
                                   *      -   noack               if set, consumed messages do not have to be acked, this happens automatically
                                   *      -   exclusive           request exclusive access, only this consumer can access the queue
                                   */
                                   channel.consume( settings_->getQueue()->getName() )
                                          .onReceived( [&](const AMQP::Message& message, uint64_t deliveryTag, bool redelivered) {
#pragma warning(disable:4244) //C4244 преобразование "uint64_t" в "unsigned int", возможна потеря данных
                                                executor( std::move( std::string( message.body(), message.bodySize() ) ) );
#pragma warning(default:4244)
                                                channel.ack( deliveryTag );
                                             } );
                                } );
                   } );

         handler_->loop();
      }

      void Consume::quit() {
         handler_->quit();
      }

      bool Consume::tryQuit() {
         return handler_->tryQuit();
      }

      bool Consume::isQuited() {
         return handler_->isQuited();
      }

      Consume::Consume( const boost::shared_ptr< Utility::ISettings >& settings ):
         settings_( settings ),
         handler_( Utility::make_shared_pool< Poco::PocoHandler, boost::default_user_allocator_malloc_free >( settings->getHost() ) ) {
      }

      boost::shared_ptr< IConsume > Consume::getInstance( const boost::shared_ptr< Utility::ISettings >& settings ) {
         return Utility::make_shared_pool_enable< IConsume, Consume, boost::default_user_allocator_malloc_free >( settings );
      }
   }
}
