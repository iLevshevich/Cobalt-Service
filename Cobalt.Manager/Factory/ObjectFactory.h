#ifndef __MANAGER_I_OBJECT_FACTORY_H_INCLUDED__
#define __MANAGER_I_OBJECT_FACTORY_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Factory
   {
      BOOST_PARAMETER_NAME(onStart)
      BOOST_PARAMETER_NAME(onStop)
      BOOST_PARAMETER_NAME(onError)

      BOOST_PARAMETER_NAME(onBeforePush)
      BOOST_PARAMETER_NAME(onPush)
      BOOST_PARAMETER_NAME(onAfterPush)

      BOOST_PARAMETER_NAME(onBeforePop)
      BOOST_PARAMETER_NAME(onPop)
      BOOST_PARAMETER_NAME(onAfterPop)

      BOOST_PARAMETER_NAME(factory)
      BOOST_PARAMETER_NAME(settings)
      BOOST_PARAMETER_NAME(monitor)
      BOOST_PARAMETER_NAME(routingKey)
      BOOST_PARAMETER_NAME(id)
      BOOST_PARAMETER_NAME(description)
      BOOST_PARAMETER_NAME(acknowledge)
      BOOST_PARAMETER_NAME(container)

      BOOST_PARAMETER_NAME(handler)
      BOOST_PARAMETER_NAME(queue)

      BOOST_PARAMETER_NAME(inputFactory)
      BOOST_PARAMETER_NAME(inputSettings)
      BOOST_PARAMETER_NAME(inputRoutingKey)
      BOOST_PARAMETER_NAME(inputAcknowledge)
      BOOST_PARAMETER_NAME(outputFactory)
      BOOST_PARAMETER_NAME(outputSettings)
      BOOST_PARAMETER_NAME(outputRoutingKey)
      BOOST_PARAMETER_NAME(outputAcknowledge)

#pragma warning(disable:4348) //C4348 переопределение параметра по умолчанию
#pragma warning(disable:4003) // C4003 не хватает фактических параметров для макроопределения "BOOST_PP_SEQ_DETAIL_IS_NOT_EMPTY" "BOOST_PP_SEQ_DETAIL_EMPTY_SIZE"
      template< class _Elem, size_t _Capacity = 4096 >
      class ObjectFactory:
         private boost::noncopyable {
      public:
         typedef typename Utility::Traits< _Elem >::base_t base_type;
         typedef typename Utility::Traits< base_type >::const_reference_t arg_type;
         typedef typename Utility::Traits< std::function< void( arg_type ) > >::const_reference_t function_1_type;
         typedef typename Utility::Traits< std::function< void( arg_type, arg_type ) > >::const_reference_t function_2_type;
         typedef typename Utility::Traits< boost::shared_ptr< IImportFactory< Import::ImportType::Amqp > > >::const_reference_t amqp_factory_type;
         typedef typename Utility::Traits< boost::shared_ptr< IImportFactory< Import::ImportType::Tcp > > >::const_reference_t tcp_factory_type;
         typedef typename Utility::Traits< boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Amqp > > >::const_reference_t amqp_settings_type;
         typedef typename Utility::Traits< boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Tcp > > >::const_reference_t tcp_settings_type;
         typedef typename Utility::Traits< boost::shared_ptr< Handler::Input::IInputHandlerAcknowledge< Import::ImportType::Amqp > > >::const_reference_t input_acknowledge_type;
         typedef typename Utility::Traits< boost::shared_ptr< Handler::Output::IOutputHandlerAcknowledge< Import::ImportType::Amqp > > >::const_reference_t output_acknowledge_type;
         typedef typename Utility::Traits< boost::shared_ptr< Handler::Monitor::IInputMonitorHandler< base_type > > >::const_reference_t input_monitor_type;
         typedef typename Utility::Traits< boost::shared_ptr< Handler::Monitor::IOutputMonitorHandler< base_type > > >::const_reference_t output_monitor_type;
         typedef typename Utility::Traits< boost::shared_ptr< boost::lockfree::spsc_queue< _Elem, boost::lockfree::capacity< _Capacity > > > >::const_reference_t container_type;
         typedef typename Utility::Traits< boost::shared_ptr< Cobalt::Handler::Queue::BlockQueue< base_type > > >::const_reference_t block_container_type;
         typedef typename Utility::Traits< boost::shared_ptr< Handler::Input::IInputHandler< base_type > > >::const_reference_t input_handler_type;
         typedef typename Utility::Traits< boost::shared_ptr< Handler::Output::IOutputHandler< base_type > > >::const_reference_t output_handler_type;
         typedef typename Utility::Traits< boost::shared_ptr< Handler::Queue::IQueueHandler< base_type, base_type > > >::const_reference_t queue_type;

         BOOST_PARAMETER_MEMBER_FUNCTION(
            (boost::shared_ptr< Handler::Monitor::IMonitorHandler< base_type > >),
            static getMonitor,
            tag,
            (required
               (onError, (function_2_type)))
            (optional
               (onStart, (function_1_type), nullptr)
               (onStop, (function_1_type), nullptr))
         ) {
               const boost::shared_ptr< Handler::Monitor::IMonitorHandlerBuilder< base_type > > builder( Utility::make_shared_pool< Handler::Monitor::MonitorHandlerBuilder< base_type >, boost::default_user_allocator_malloc_free >() );
               ///
               COBALT_FACTORY_GUARD(onStart, builder->setOnStart(onStart);)
               COBALT_FACTORY_GUARD(onStop, builder->setOnStop(onStop);)
               COBALT_FACTORY_GUARD(onError, builder->setOnError(onError);)
               ///
               return builder->build();
         }

         BOOST_PARAMETER_MEMBER_FUNCTION(
            (boost::shared_ptr< Handler::Monitor::IInputMonitorHandler< base_type > >),
            static getInputMonitor,
            tag,
            (required
               (onPush, (function_2_type))
               (onError, (function_2_type)))
            (optional
               (onStart, (function_1_type), nullptr)
               (onStop, (function_1_type), nullptr)
               (onBeforePush, (function_2_type), nullptr)
               (onAfterPush, (function_2_type), nullptr))
         ) {
               const boost::shared_ptr< Handler::Monitor::InputMonitorHandlerBuilder< base_type > > builder( Utility::make_shared_pool< Handler::Monitor::InputMonitorHandlerBuilder< base_type >, boost::default_user_allocator_malloc_free >() );
               ///
               COBALT_FACTORY_GUARD(onStart, builder->setOnStart(onStart);)
               COBALT_FACTORY_GUARD(onStop, builder->setOnStop(onStop);)
               COBALT_FACTORY_GUARD(onBeforePush, builder->setOnBeforePush(onBeforePush);)
               COBALT_FACTORY_GUARD(onPush, builder->setOnPush(onPush);)
               COBALT_FACTORY_GUARD(onAfterPush, builder->setOnAfterPush(onAfterPush);)
               COBALT_FACTORY_GUARD(onError, builder->setOnError(onError);)
               ///
               return builder->build();
         }

         BOOST_PARAMETER_MEMBER_FUNCTION(
            (boost::shared_ptr< Handler::Monitor::IOutputMonitorHandler< base_type > >),
            static getOutputMonitor,
            tag,
            (required
               (onError, (function_2_type)))
            (optional
               (onStart, (function_1_type), nullptr)
               (onStop, (function_1_type), nullptr)
               (onBeforePop, (function_2_type), nullptr)
               (onPop, (function_2_type), nullptr)
               (onAfterPop, (function_2_type), nullptr))
         ) {
            const boost::shared_ptr< Handler::Monitor::OutputMonitorHandlerBuilder< base_type > > builder( Utility::make_shared_pool< Handler::Monitor::OutputMonitorHandlerBuilder< base_type >, boost::default_user_allocator_malloc_free >() );
            ///
            COBALT_FACTORY_GUARD(onStart, builder->setOnStart(onStart);)
            COBALT_FACTORY_GUARD(onStop, builder->setOnStop(onStop);)
            COBALT_FACTORY_GUARD(onBeforePop, builder->setOnBeforePop(onBeforePop);)
            COBALT_FACTORY_GUARD(onPop, builder->setOnPop(onPop);)
            COBALT_FACTORY_GUARD(onAfterPop, builder->setOnAfterPop(onAfterPop);)
            COBALT_FACTORY_GUARD(onError, builder->setOnError(onError);)
            ///
            return builder->build();
         }

         BOOST_PARAMETER_MEMBER_FUNCTION(
            (boost::shared_ptr< Cobalt::Handler::Input::IInputHandler< base_type > >),
            static getAmqpInputHandler,
            tag,
            (required
               (factory, (amqp_factory_type))
               (settings, (amqp_settings_type))
               (monitor, (input_monitor_type))
               (routingKey, (arg_type)))
            (optional
               (acknowledge, (input_acknowledge_type), (Utility::make_shared_pool< Handler::Input::InputHandlerAcknowledge< Import::ImportType::Amqp >, boost::default_user_allocator_malloc_free >()) )
               (id, (arg_type), boost::uuids::to_string( boost::uuids::random_generator()() ))
               (description, (arg_type), base_type()))
         ) {
            const boost::shared_ptr< Handler::Input::InputHandlerBuilder< base_type, Handler::Input::InputHandler< Import::ImportType::Amqp >, Import::ImportType::Amqp > > builder( Utility::make_shared_pool< Handler::Input::InputHandlerBuilder< base_type, Handler::Input::InputHandler< Import::ImportType::Amqp >, Import::ImportType::Amqp >, boost::default_user_allocator_malloc_free >() );
            ///
            builder->setFactory( factory );
            builder->setSettings( settings );
            builder->setMonitor( monitor );
            builder->setKey( routingKey );
            builder->setAcknowledge(acknowledge);
            builder->setMeta( Utility::make_shared_pool< Handler::Meta::MetaHandler, boost::default_user_allocator_malloc_free >(id, description) );
            builder->setState( Utility::make_shared_pool< Handler::State::StateHandler< Handler::State::StateHandlerType::input >, boost::default_user_allocator_malloc_free >() );
            ///
            return builder->build();
         }

         BOOST_PARAMETER_MEMBER_FUNCTION(
            (boost::shared_ptr< Cobalt::Handler::Output::IOutputHandler< base_type > >),
            static getAmqpOutputHandler,
            tag,
            (required
               (factory, (amqp_factory_type))
               (settings, (amqp_settings_type))
               (monitor, (output_monitor_type))
               (routingKey, (arg_type)))
            (optional
               (acknowledge, (output_acknowledge_type), (Utility::make_shared_pool< Handler::Output::OutputHandlerAcknowledge< Import::ImportType::Amqp >, boost::default_user_allocator_malloc_free >()) )
               (id, (arg_type), boost::uuids::to_string(boost::uuids::random_generator()()))
               (description, (arg_type), base_type()))
         ) {
            const boost::shared_ptr< Handler::Output::OutputHandlerBuilder< base_type, Handler::Output::OutputHandler< Import::ImportType::Amqp >, Import::ImportType::Amqp > > builder( Utility::make_shared_pool< Handler::Output::OutputHandlerBuilder< base_type, Handler::Output::OutputHandler< Import::ImportType::Amqp >, Import::ImportType::Amqp >, boost::default_user_allocator_malloc_free >());
            ///
            builder->setFactory( factory );
            builder->setSettings( settings );
            builder->setMonitor( monitor );
            builder->setKey( routingKey );
            builder->setAcknowledge( acknowledge );
            builder->setMeta( Utility::make_shared_pool< Handler::Meta::MetaHandler, boost::default_user_allocator_malloc_free >(id, description) );
            builder->setState( Utility::make_shared_pool< Handler::State::StateHandler< Handler::State::StateHandlerType::output >, boost::default_user_allocator_malloc_free >() );
            ///
            return builder->build();
         }

         BOOST_PARAMETER_MEMBER_FUNCTION(
            (boost::shared_ptr< Cobalt::Handler::Input::IInputHandler< base_type > >),
            static getTcpInputHandler,
            tag,
            (required
               (factory, (tcp_factory_type))
               (settings, (tcp_settings_type))
               (monitor, (input_monitor_type)))
            (optional
               (id, (arg_type), boost::uuids::to_string(boost::uuids::random_generator()()))
               (description, (arg_type), base_type()))
         ) {
            const boost::shared_ptr< Handler::Input::InputHandlerBuilder< base_type, Handler::Input::InputHandler< Import::ImportType::Tcp >, Import::ImportType::Tcp > > builder(Utility::make_shared_pool< Handler::Input::InputHandlerBuilder< base_type, Handler::Input::InputHandler< Import::ImportType::Tcp >, Import::ImportType::Tcp >, boost::default_user_allocator_malloc_free >());
            ///
            builder->setFactory(factory);
            builder->setSettings(settings);
            builder->setMonitor(monitor);
            builder->setMeta(Utility::make_shared_pool< Handler::Meta::MetaHandler, boost::default_user_allocator_malloc_free >(id, description));
            builder->setState(Utility::make_shared_pool< Handler::State::StateHandler< Handler::State::StateHandlerType::input >, boost::default_user_allocator_malloc_free >());
            ///
            return builder->build();
         }

         BOOST_PARAMETER_MEMBER_FUNCTION(
            (boost::shared_ptr< Cobalt::Handler::Output::IOutputHandler< base_type > >),
            static getTcpOutputHandler,
            tag,
            (required
               (factory, (tcp_factory_type))
               (settings, (tcp_settings_type))
               (monitor, (output_monitor_type)))
            (optional
               (id, (arg_type), boost::uuids::to_string(boost::uuids::random_generator()()))
               (description, (arg_type), base_type()))
         ) {
            const boost::shared_ptr< Handler::Output::OutputHandlerBuilder< base_type, Handler::Output::OutputHandler< Import::ImportType::Tcp >, Import::ImportType::Tcp > > builder(Utility::make_shared_pool< Handler::Output::OutputHandlerBuilder< base_type, Handler::Output::OutputHandler< Import::ImportType::Tcp >, Import::ImportType::Tcp >, boost::default_user_allocator_malloc_free >());
            ///
            builder->setFactory(factory);
            builder->setSettings(settings);
            builder->setMonitor(monitor);
            builder->setMeta(Utility::make_shared_pool< Handler::Meta::MetaHandler, boost::default_user_allocator_malloc_free >(id, description));
            builder->setState(Utility::make_shared_pool< Handler::State::StateHandler< Handler::State::StateHandlerType::output >, boost::default_user_allocator_malloc_free >());
            ///
            return builder->build();
         }

         BOOST_PARAMETER_MEMBER_FUNCTION(
            (boost::shared_ptr< Cobalt::Handler::Queue::IQueueHandler< base_type, base_type > >),
            static getQueueHandler,
            tag,
            (required
               (container, (container_type)))
            (optional
               (id, (arg_type), boost::uuids::to_string(boost::uuids::random_generator()()))
               (description, (arg_type), base_type()))
         ) {
            const boost::shared_ptr< Handler::Queue::IQueueHandlerBuilder< base_type, _Capacity > > builder( Utility::make_shared_pool< Handler::Queue::QueueHandlerBuilder< base_type, _Capacity >, boost::default_user_allocator_malloc_free >());
            ///
            builder->setContainer( container );
            builder->setMeta( Utility::make_shared_pool< Handler::Meta::MetaHandler, boost::default_user_allocator_malloc_free >(id, description) );
            builder->setState( Utility::make_shared_pool< Handler::State::StateHandler< Handler::State::StateHandlerType::intermediate >, boost::default_user_allocator_malloc_free >() );
            ///
            return builder->build();
         }

         static boost::shared_ptr< Handler::Queue::IQueueHandler< base_type, base_type > > getQueueHandler() {
            return getQueueHandler(
               _container = Utility::make_shared_pool< boost::lockfree::spsc_queue< base_type, boost::lockfree::capacity< _Capacity > >, boost::default_user_allocator_malloc_free >()
            );
         }

         BOOST_PARAMETER_MEMBER_FUNCTION(
            (boost::shared_ptr< Cobalt::Handler::Queue::IQueueHandler< base_type, base_type > >),
            static getBlockQueueHandler,
            tag,
            (required
               (container, (block_container_type)))
            (optional
               (id, (arg_type), boost::uuids::to_string(boost::uuids::random_generator()()))
               (description, (arg_type), base_type()))
         ) {
            const boost::shared_ptr< Handler::Queue::IBlockQueueHandlerBuilder< base_type > > builder(Utility::make_shared_pool< Handler::Queue::BlockQueueHandlerBuilder< base_type >, boost::default_user_allocator_malloc_free >());
            ///
            builder->setContainer(container);
            builder->setMeta(Utility::make_shared_pool< Handler::Meta::MetaHandler, boost::default_user_allocator_malloc_free >(id, description));
            builder->setState(Utility::make_shared_pool< Handler::State::StateHandler< Handler::State::StateHandlerType::intermediate >, boost::default_user_allocator_malloc_free >());
            ///
            return builder->build();
         }

         static boost::shared_ptr< Handler::Queue::IQueueHandler< base_type, base_type > > getBlockQueueHandler() {
            return getBlockQueueHandler(
               _container = Utility::make_shared_pool< Cobalt::Handler::Queue::BlockQueue< base_type >, boost::default_user_allocator_malloc_free >()
            );
         }

         BOOST_PARAMETER_MEMBER_FUNCTION(
            (boost::shared_ptr< Cobalt::Handler::Dispatcher::IDispatcherHandler< base_type > >),
            static getAmqpToAmqpDispatcherHandler,
            tag,
            (required
               (inputFactory, (amqp_factory_type))
               (inputSettings, (amqp_settings_type))
               (inputRoutingKey, (arg_type))
               (outputFactory, (amqp_factory_type))
               (outputSettings, (amqp_settings_type))
               (outputRoutingKey, (arg_type)))
            (optional 
               (inputAcknowledge, (input_acknowledge_type), (Utility::make_shared_pool< Handler::Input::InputHandlerAcknowledge< Import::ImportType::Amqp >, boost::default_user_allocator_malloc_free >()))
               (outputAcknowledge, (output_acknowledge_type), (Utility::make_shared_pool< Handler::Output::OutputHandlerAcknowledge< Import::ImportType::Amqp >, boost::default_user_allocator_malloc_free >()))
               (id, (arg_type), boost::uuids::to_string(boost::uuids::random_generator()()))
               (description, (arg_type), base_type()))
         ) {
            const boost::shared_ptr< Cobalt::Handler::Dispatcher::IAmqpToAmqpDispatcherHandlerBuilder< base_type > > builder( Utility::make_shared_pool< Handler::Dispatcher::AmqpToAmqpDispatcherHandlerBuilder< base_type, Handler::Dispatcher::AmqpToAmqpDispatcherHandler >, boost::default_user_allocator_malloc_free >() );
            ///
            builder->setMeta(Utility::make_shared_pool< Handler::Meta::MetaHandler, boost::default_user_allocator_malloc_free >(id, description));
            builder->setState(Utility::make_shared_pool< Handler::State::StateHandler< Handler::State::StateHandlerType::base >, boost::default_user_allocator_malloc_free >());

            builder->setInputFactory(inputFactory);
            builder->setInputSettings(inputSettings);
            builder->setInputKey(inputRoutingKey);
            builder->setInputAcknowledge(inputAcknowledge);

            builder->setOutputFactory(outputFactory);
            builder->setOutputSettings(outputSettings);
            builder->setOutputKey(outputRoutingKey);
            builder->setOutputAcknowledge(outputAcknowledge);
            ///
            return builder->build();
         }

         BOOST_PARAMETER_MEMBER_FUNCTION(
            (boost::shared_ptr< Cobalt::Handler::Dispatcher::IDispatcherHandler< base_type > >),
            static getAmqpToTcpDispatcherHandler,
            tag,
            (required
               (inputFactory, (amqp_factory_type))
               (inputSettings, (amqp_settings_type))
               (inputRoutingKey, (arg_type))
               (outputFactory, (tcp_factory_type))
               (outputSettings, (tcp_settings_type)))
            (optional
               (inputAcknowledge, (input_acknowledge_type), (Utility::make_shared_pool< Handler::Input::InputHandlerAcknowledge< Import::ImportType::Amqp >, boost::default_user_allocator_malloc_free >()))
               (id, (arg_type), boost::uuids::to_string(boost::uuids::random_generator()()))
               (description, (arg_type), base_type()))
         ) {
            const boost::shared_ptr< Cobalt::Handler::Dispatcher::IAmqpToTcpDispatcherHandlerBuilder< base_type > > builder(Utility::make_shared_pool< Handler::Dispatcher::AmqpToTcpDispatcherHandlerBuilder< base_type, Handler::Dispatcher::AmqpToTcpDispatcherHandler >, boost::default_user_allocator_malloc_free >());
            ///
            builder->setMeta(Utility::make_shared_pool< Handler::Meta::MetaHandler, boost::default_user_allocator_malloc_free >(id, description));
            builder->setState(Utility::make_shared_pool< Handler::State::StateHandler< Handler::State::StateHandlerType::base >, boost::default_user_allocator_malloc_free >());

            builder->setInputFactory(inputFactory);
            builder->setInputSettings(inputSettings);
            builder->setInputKey(inputRoutingKey);
            builder->setInputAcknowledge(inputAcknowledge);

            builder->setOutputFactory(outputFactory);
            builder->setOutputSettings(outputSettings);
            ///
            return builder->build();
         }

         BOOST_PARAMETER_MEMBER_FUNCTION(
            (boost::shared_ptr< Cobalt::Handler::Dispatcher::IDispatcherHandler< base_type > >),
            static getTcpToAmqpDispatcherHandler,
            tag,
            (required
               (inputFactory, (tcp_factory_type))
               (inputSettings, (tcp_settings_type))
               (outputFactory, (amqp_factory_type))
               (outputSettings, (amqp_settings_type))
               (outputRoutingKey, (arg_type)))
            (optional
               (outputAcknowledge, (output_acknowledge_type), (Utility::make_shared_pool< Handler::Output::OutputHandlerAcknowledge< Import::ImportType::Amqp >, boost::default_user_allocator_malloc_free >()))
               (id, (arg_type), boost::uuids::to_string(boost::uuids::random_generator()()))
               (description, (arg_type), base_type()))
         ) {
            const boost::shared_ptr< Cobalt::Handler::Dispatcher::ITcpToAmqpDispatcherHandlerBuilder< base_type > > builder(Utility::make_shared_pool< Handler::Dispatcher::TcpToAmqpDispatcherHandlerBuilder< base_type, Handler::Dispatcher::TcpToAmqpDispatcherHandler >, boost::default_user_allocator_malloc_free >());
            ///
            builder->setMeta(Utility::make_shared_pool< Handler::Meta::MetaHandler, boost::default_user_allocator_malloc_free >(id, description));
            builder->setState(Utility::make_shared_pool< Handler::State::StateHandler< Handler::State::StateHandlerType::base >, boost::default_user_allocator_malloc_free >());

            builder->setInputFactory(inputFactory);
            builder->setInputSettings(inputSettings);

            builder->setOutputFactory(outputFactory);
            builder->setOutputSettings(outputSettings);
            builder->setOutputKey(outputRoutingKey);
            builder->setOutputAcknowledge(outputAcknowledge);
            ///
            return builder->build();
         }

         BOOST_PARAMETER_MEMBER_FUNCTION(
            (boost::shared_ptr< Cobalt::Handler::Dispatcher::IDispatcherHandler< base_type > >),
            static getTcpToTcpDispatcherHandler,
            tag,
            (required
               (inputFactory, (tcp_factory_type))
               (inputSettings, (tcp_settings_type))
               (outputFactory, (tcp_factory_type))
               (outputSettings, (tcp_settings_type)))
            (optional
               (id, (arg_type), boost::uuids::to_string(boost::uuids::random_generator()()))
               (description, (arg_type), base_type()))
         ) {
            const boost::shared_ptr< Cobalt::Handler::Dispatcher::ITcpToTcpDispatcherHandlerBuilder< base_type > > builder(Utility::make_shared_pool< Handler::Dispatcher::TcpToTcpDispatcherHandlerBuilder< base_type, Handler::Dispatcher::TcpToTcpDispatcherHandler >, boost::default_user_allocator_malloc_free >());
            ///
            builder->setMeta(Utility::make_shared_pool< Handler::Meta::MetaHandler, boost::default_user_allocator_malloc_free >(id, description));
            builder->setState(Utility::make_shared_pool< Handler::State::StateHandler< Handler::State::StateHandlerType::base >, boost::default_user_allocator_malloc_free >());

            builder->setInputFactory(inputFactory);
            builder->setInputSettings(inputSettings);

            builder->setOutputFactory(outputFactory);
            builder->setOutputSettings(outputSettings);
            ///
            return builder->build();
         }
      };
#pragma warning(default:4003)
#pragma warning(default:4348)
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_OBJECT_FACTORY_H_INCLUDED__
