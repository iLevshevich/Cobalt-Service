#ifndef __MANAGER_AMQP_TO_AMQP_CONFIG_CHAIN_H_INCLUDED__
#define __MANAGER_AMQP_TO_AMQP_CONFIG_CHAIN_H_INCLUDED__

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
         class AmqpToAmqpConfigChain:
            public IConfigChain {
         public:
            typedef typename IConfigChain::config_type config_type;
            typedef typename IConfigChain::return_type return_type;

            typedef typename Utility::Traits< boost::shared_ptr< IConfigChain > >::const_reference_t chain_type;
            typedef typename Utility::Traits< boost::shared_ptr< IConfigChain > >::base_t chain_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Factory::IImportFactory< Import::ImportType::Amqp > > >::base_t factory_base_type;
            typedef typename Utility::Traits< boost::shared_ptr< Import::Utility::ISettingsBuilder< Import::ImportType::Amqp > > >::base_t builder_base_type;
            typedef typename Utility::Traits< boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Amqp > > >::base_t settings_base_type;

            static chain_base_type getInstance() {
               return Utility::make_shared_pool_enable< IConfigChain, AmqpToAmqpConfigChain, boost::default_user_allocator_malloc_free >();
            }

            static chain_base_type getInstance( chain_type next ) {
               return Utility::make_shared_pool_enable< IConfigChain, AmqpToAmqpConfigChain, boost::default_user_allocator_malloc_free >( next );
            }

            return_type __stdcall getDispatcher( config_type config ) override {
               const Handler::Dispatcher::Type::DispatcherHandlerType type( Handler::Dispatcher::Type::StringToDispatcherHandlerType( config->second.get< std::string >( "type" ) ) );
               if( type == Handler::Dispatcher::Type::DispatcherHandlerType::AmqpToAmqp ) {
                  ///
                  const factory_base_type factory( getFactory< Import::ImportType::Amqp >() );
                  const settings_base_type input_settings( getSettings< Handler::Property::input >( config ) );
                  const settings_base_type output_settings( getSettings< Handler::Property::output >( config ) );
                  const std::string input_routing_key( config->second.get< std::string >( "input.routing_key" ) );
                  const std::string output_routing_key( config->second.get< std::string >( "output.routing_key" ) );

                  const std::string id( config->second.get< std::string >( "id" ) );
                  const std::string description( config->second.get< std::string >( "description" ) );

                  return Factory::ObjectFactory< std::string >::getAmqpToAmqpDispatcherHandler(
                     Factory::_inputFactory = factory,
                     Factory::_inputSettings = input_settings,
                     Factory::_inputRoutingKey = input_routing_key,
                     Factory::_outputFactory = factory,
                     Factory::_outputSettings = output_settings,
                     Factory::_outputRoutingKey = output_routing_key,
                     Factory::_id = id,
                     Factory::_description = description
                  );
               }
               else {
                  if( next_.get() ) {
                     return next_->getDispatcher( config );
                  }
               }

               return return_type();
            }

            virtual ~AmqpToAmqpConfigChain() = default;

         protected:
            AmqpToAmqpConfigChain() :
               next_( nullptr ) {
            }

            explicit AmqpToAmqpConfigChain( chain_type next ):
               next_( next ) {
            }

         private:
            template< Handler::Property::PropertyHandlerType _En, typename std::enable_if< _En == Handler::Property::PropertyHandlerType::input >::type * = nullptr >
            settings_base_type __fastcall getSettings( config_type config ) const {
               const factory_base_type factory( getFactory< Import::ImportType::Amqp >() );
               const builder_base_type builder( factory->getSettingsBuilder() );
               ///
               builder->setHost( config->second.get< std::string >( "input.host" ), boost::lexical_cast< uint16_t >( config->second.get< std::string >( "input.port" ) ) );
               builder->setLogin( config->second.get< std::string >( "input.user" ), config->second.get< std::string >( "input.password" ) );
               builder->setConnection( config->second.get< std::string >( "input.vhost" ) );
               builder->setChannel( boost::lexical_cast< uint16_t >( config->second.get< std::string >( "input.prefetch" ) ) );
               builder->setExchange( config->second.get< std::string >( "input.exchange" ), Import::Utility::ExchangeType::direct );
               builder->setQueue( config->second.get< std::string >( "input.queue" ), Import::Utility::FlagsType::durable );
               ///
               return builder->build();
            }

            template< Handler::Property::PropertyHandlerType _En, typename std::enable_if< _En == Handler::Property::PropertyHandlerType::output >::type * = nullptr >
            settings_base_type __fastcall getSettings( config_type config ) const {
               const factory_base_type factory( getFactory< Import::ImportType::Amqp >() );
               const builder_base_type builder( factory->getSettingsBuilder() );
               ///
               builder->setHost( config->second.get< std::string >( "output.host" ), boost::lexical_cast< uint16_t >( config->second.get< std::string >( "output.port" ) ) );
               builder->setLogin( config->second.get< std::string >( "output.user" ), config->second.get< std::string >( "output.password" ) );
               builder->setConnection( config->second.get< std::string >( "output.vhost" ) );
               builder->setChannel( boost::lexical_cast< uint16_t >( config->second.get< std::string >( "output.prefetch" ) ) );
               builder->setExchange( config->second.get< std::string >( "output.exchange" ), Import::Utility::ExchangeType::direct );
               builder->setQueue( config->second.get< std::string >( "output.queue" ), Import::Utility::FlagsType::durable );
               ///
               return builder->build();
            }

            chain_base_type next_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_AMQP_TO_AMQP_CONFIG_CHAIN_H_INCLUDED__
