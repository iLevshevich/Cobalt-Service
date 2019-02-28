#include "../../stdafx.h"

#include "../../Import/ImportType.h"
#include "../../Utility/Traits.h"
#include "../../Utility/Singleton.h"
#include "../../Utility/EnableMake.h"
#include "../../Utility/MakeObject.h"
#include "../../Utility/MakeAsync.h"
#include "../../Utility/Options.h"
#include "../../Utility/Logger.h"

#include "../../Import/Utility/ExchangeType.h"
#include "../../Import/Utility/FlagsType.h"
#include "../../Import/Utility/Settings/IChannelSettings.h"
#include "../../Import/Utility/Settings/IConnectionSettings.h"
#include "../../Import/Utility/Settings/IExchangeSettings.h"
#include "../../Import/Utility/Settings/IHostSettings.h"
#include "../../Import/Utility/Settings/ILoginSettings.h"
#include "../../Import/Utility/Settings/IQueueSettings.h"
#include "../../Import/Utility/Settings/ISettings.h"
#include "../../Import/Utility/Settings/ISettings.h"
#include "../../Import/Utility/Settings/Builder/ISettingsBuilder.h"
#include "../../Import/IConsume.h"
#include "../../Import/IPublish.h"

#include "../../Factory/IImportFactory.h"
#include "../../Factory/ImportFactory.h"

#include "../Performance/PerformanceHandlerType.h"
#include "../Performance/IPerformanceHandler.h"
#include "../Performance/PerformanceHandler.h"

#include "../Property/PropertyHandlerType.h"
#include "../Property/IPropertyHandler.h"
#include "../Property/PropertyHandler.h"

#include "../Error/ILastErrorHandler.h"
#include "../Error/LastErrorHandler.h"

#include "../State/StateHandlerType.h"
#include "../State/IResetHandler.h"
#include "../State/IStateHandler.h"
#include "../State/StateHandler.h"

#include "../Input/Acknowledge/IInputHandlerAcknowledge.h"
#include "../Input/Acknowledge/InputHandlerAcknowledge.h"
#include "../Input/Acknowledge/InputHandlerNoAcknowledge.h"

#include "../Output/Acknowledge/IOutputHandlerAcknowledge.h"
#include "../Output/Acknowledge/OutputHandlerAcknowledge.h"
#include "../Output/Acknowledge/OutputHandlerNoAcknowledge.h"

#include "../Meta/IMetaHandler.h"
#include "../Meta/MetaHandler.h"

#include "../Monitor/IMonitorHandler.h"
#include "../Monitor/Builder/IMonitorHandlerBuilder.h"
#include "../Monitor/MonitorHandler.h"
#include "../Monitor/Builder/MonitorHandlerBuilder.h"

#include "../Monitor/IInputMonitorHandler.h"
#include "../Monitor/Builder/IInputMonitorHandlerBuilder.h"

#include "../Monitor/InputMonitorHandler.h"
#include "../Monitor/Builder/InputMonitorHandlerBuilder.h"

#include "../Input/IInputHandler.h"
#include "../Input/Builder/IInputHandlerBuilder.h"
#include "../Input/Builder/InputHandlerBuilder.h"
#include "../Input/InputHandler.h"

#include "../Monitor/IOutputMonitorHandler.h"
#include "../Monitor/Builder/IOutputMonitorHandlerBuilder.h"

#include "../Monitor/OutputMonitorHandler.h"
#include "../Monitor/Builder/OutputMonitorHandlerBuilder.h"

#include "../Output/IOutputHandler.h"
#include "../Output/Builder/IOutputHandlerBuilder.h"
#include "../Output/Builder/OutputHandlerBuilder.h"
#include "../Output/OutputHandler.h"

#include "../Queue/IQueueHandler.h"
#include "../Queue/Builder/IQueueHandlerBuilder.h"
#include "../Queue/Builder/QueueHandlerBuilder.h"
#include "../Queue/QueueHandler.h"
#include "../Queue/BlockQueue.h"
#include "../Queue/Builder/IBlockQueueHandlerBuilder.h"
#include "../Queue/Builder/BlockQueueHandlerBuilder.h"
#include "../Queue/BlockQueueHandler.h"

#include "../../Factory/ObjectFactory.h"

#include "DispatcherHandlerType.h"
#include "DispatcherHandlerPriority.h"

#include "IDispatcherHandler.h"
#include "Builder/ITcpToTcpDispatcherHandlerBuilder.h"
#include "Builder/TcpToTcpDispatcherHandlerBuilder.h"

#include "TcpToTcpDispatcherHandler.h"

namespace Cobalt
{
   namespace Handler
   {
      namespace Dispatcher
      {
         TcpToTcpDispatcherHandler::property_tree_base_type TcpToTcpDispatcherHandler::getInputState() const {
            return input_handler_->getState();
         }

         TcpToTcpDispatcherHandler::property_tree_base_type TcpToTcpDispatcherHandler::getQueueState() const {
            return queue_handler_->getState();
         }

         TcpToTcpDispatcherHandler::property_tree_base_type TcpToTcpDispatcherHandler::getOutputState() const {
            return output_handler_->getState();
         }

         TcpToTcpDispatcherHandler::property_tree_base_type TcpToTcpDispatcherHandler::getState() const {
            return state_->getState();
         }

         TcpToTcpDispatcherHandler::property_tree_base_type TcpToTcpDispatcherHandler::getStatus() {
            boost::property_tree::ptree result;
            ///
            result.put( "id", getId() );
            result.put( "description", getDescription() );
            result.put( "type", Type::DispatcherHandlerTypeToString( getType() ) );
            result.put( "state.dispatcher", getState()->get_child( "state.base" ).get_value< std::string >() );
            result.put( "state.input", getInputState()->get_child( "state.input" ).get_value< std::string >() );
            result.put( "state.queue", getQueueState()->get_child( "state.intermediate" ).get_value< std::string >() );
            result.put( "state.output", getOutputState()->get_child( "state.output" ).get_value< std::string >() );
            ///
            merge( *getInputProperty(), result );
            merge( *getOutputProperty(), result );
            merge( *getQueueSize(), result );
            merge( *getLastPerform(), result );
            merge( *getLastError(), result );
            ///
            return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
         }

         TcpToTcpDispatcherHandler::property_tree_base_type TcpToTcpDispatcherHandler::getQueueSize() {
            return queue_handler_->getQueueSize();
         }

         TcpToTcpDispatcherHandler::property_tree_base_type TcpToTcpDispatcherHandler::getLastPerform() {
            return performance_->getLastPerform();
         }

         TcpToTcpDispatcherHandler::property_tree_base_type TcpToTcpDispatcherHandler::getLastError() {
            return last_error_->getLastError();
         }

         void TcpToTcpDispatcherHandler::cleanLastError() {
            last_error_->cleanLastError();
         }

         bool TcpToTcpDispatcherHandler::isLastErrorEmpty() {
            return last_error_->isLastErrorEmpty();
         }

         void __stdcall TcpToTcpDispatcherHandler::merge( property_source_type source, property_destination_type dest ) {
            for( property_value_type item : source ) {
               dest.put_child( item.first, item.second );
            }
         }

         TcpToTcpDispatcherHandler::property_tree_base_type TcpToTcpDispatcherHandler::getProperty() {
            boost::property_tree::ptree result;
            ///
            result.put( "id", getId() );
            result.put( "description", getDescription() );
            result.put( "type", Type::DispatcherHandlerTypeToString( getType() ) );
            ///
            merge( *getInputProperty(), result );
            merge( *getOutputProperty(), result );
            ///
            return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
         }

         TcpToTcpDispatcherHandler::property_tree_base_type TcpToTcpDispatcherHandler::getInputProperty() const {
            return input_property_->getProperty();
         }

         TcpToTcpDispatcherHandler::property_tree_base_type TcpToTcpDispatcherHandler::getOutputProperty() const {
            return output_property_->getProperty();
         }

         Type::DispatcherHandlerType TcpToTcpDispatcherHandler::getType() const {
            return Type::DispatcherHandlerType::TcpToTcp;
         }

         Priority::DispatcherHandlerPriority TcpToTcpDispatcherHandler::getPriority() const {
            return Priority::DispatcherHandlerPriority::TcpToTcp;
         }

         TcpToTcpDispatcherHandler::TcpToTcpDispatcherHandler( builder_type builder ) :
            monitor_( Factory::ObjectFactory< base_type >::getMonitor(
#if defined(__MANAGER_TRACE__)
               Factory::_onStart = [&](id_type id) {
                  Utility::Memmory::Singleton< Utility::Logger >::instance()
                     .info( (boost::format( "TcpToTcpDispatcherHandler::onStart() [DispatcherID: %s] [ObjectID: %s]" ) % getId() % id).str() );
               },
               Factory::_onStop = [&](id_type id) {
                  Utility::Memmory::Singleton< Utility::Logger >::instance()
                     .info( (boost::format( "TcpToTcpDispatcherHandler::onStop() [DispatcherID: %s] [ObjectID: %s]" ) % getId() % id).str() );
               },
#endif
               Factory::_onError = [&](message_type message, id_type id) {
                  Utility::Memmory::Singleton< Utility::Logger >::instance()
                     .error( (boost::format( "TcpToTcpDispatcherHandler::onError() [DispatcherID: %s] [ObjectID: %s] [Message: %s]" ) % getId() % id % message).str() );
                  ///
                  last_error_->setLastError( message );
               }
            ) ),
            state_( builder.getState() ),
            meta_( builder.getMeta() ),
            input_handler_( Factory::ObjectFactory< base_type >::getTcpInputHandler(
               Factory::_factory = builder.getInputFactory(),
               Factory::_settings = builder.getInputSettings(),
               Factory::_monitor = Factory::ObjectFactory< base_type >::getInputMonitor(
#if defined(__MANAGER_TRACE__)
                  Factory::_onStart = [&](id_type id) {
                     Utility::Memmory::Singleton< Utility::Logger >::instance()
                        .info( (boost::format( "TcpToTcpDispatcherHandler::TcpInputHandler::onStart() [DispatcherID: %s] [ObjectID: %s]" ) % getId() % id).str() );
                  },
                  Factory::_onStop = [&](id_type id) {
                     Utility::Memmory::Singleton< Utility::Logger >::instance()
                        .info( (boost::format( "TcpToTcpDispatcherHandler::TcpInputHandler::onStop() [DispatcherID: %s] [ObjectID: %s]" ) % getId() % id).str() );
                  },
#endif
                  Factory::_onBeforePush = [&](message_type message, id_type id) {
                     performance_->begin(message);
#if defined(__MANAGER_TRACE__)
					 Utility::Memmory::Singleton< Utility::Logger >::instance()
						 .trace((boost::format("TcpToTcpDispatcherHandler::TcpInputHandler::onBeforePush() [DispatcherID: %s] [ObjectID: %s] [Message: %s]") % getId() % id % message).str());
#endif
                  },
                  Factory::_onPush = [&](message_type message, id_type id) {
#if defined(__MANAGER_TRACE__)
					  Utility::Memmory::Singleton< Utility::Logger >::instance()
						  .trace((boost::format("TcpToTcpDispatcherHandler::TcpInputHandler::onPush() [DispatcherID: %s] [ObjectID: %s] [Message: %s]") % getId() % id % message).str());
#endif
                     queue_handler_->push( move( message ) );
                  },
#if defined(__MANAGER_TRACE__)
				  Factory::_onAfterPush = [&](message_type message, id_type id) {
					  Utility::Memmory::Singleton< Utility::Logger >::instance()
						  .trace((boost::format("TcpToTcpDispatcherHandler::TcpInputHandler::onAfterPush() [DispatcherID: %s] [ObjectID: %s] [Message: %s]") % getId() % id % message).str());
				  },
#endif
                  Factory::_onError = [&](message_type message, id_type id) {
                     Utility::Memmory::Singleton< Utility::Logger >::instance()
                        .error( (boost::format( "TcpToTcpDispatcherHandler::TcpInputHandler::onError() [DispatcherID: %s] [ObjectID: %s] [Message: %s]" ) % getId() % id % message).str() );
                     ///
                     last_error_->setLastError( message );
                     performance_->cleanLastPerform(message);
                  }
               ) ) ),
            queue_handler_( Factory::ObjectFactory< base_type >::getBlockQueueHandler() ),
            output_handler_( Factory::ObjectFactory< base_type >::getTcpOutputHandler(
               Factory::_factory = builder.getOutputFactory(),
               Factory::_settings = builder.getOutputSettings(),
               Factory::_monitor = Factory::ObjectFactory< base_type >::getOutputMonitor(
#if defined(__MANAGER_TRACE__)
                  Factory::_onStart = [&](id_type id) {
                     Utility::Memmory::Singleton< Utility::Logger >::instance()
                        .info( (boost::format( "TcpToTcpDispatcherHandler::TcpOutputHandler::onStart() [DispatcherID: %s] [ObjectID: %s]" ) % getId() % id).str() );
                  },
                  Factory::_onStop = [&](id_type id) {
                     Utility::Memmory::Singleton< Utility::Logger >::instance()
                        .info( (boost::format( "TcpToTcpDispatcherHandler::TcpOutputHandler::onStop() [DispatcherID: %s] [ObjectID: %s]" ) % getId() % id).str() );
                  },
#endif
#if defined(__MANAGER_TRACE__)
				  Factory::_onBeforePop = [&](message_type message, id_type id) {
					  Utility::Memmory::Singleton< Utility::Logger >::instance()
						  .trace((boost::format("TcpToTcpDispatcherHandler::TcpOutputHandler::onBeforePop() [DispatcherID: %s] [ObjectID: %s] [Message: %s]") % getId() % id % message).str());
				  },
				  Factory::_onPop = [&](message_type message, id_type id) {
					  Utility::Memmory::Singleton< Utility::Logger >::instance()
						  .trace((boost::format("TcpToTcpDispatcherHandler::TcpOutputHandler::onPop() [DispatcherID: %s] [ObjectID: %s] [Message: %s]") % getId() % id % message).str());
				  },
#endif
                  Factory::_onAfterPop = [&](message_type message, id_type id) {
                     performance_->end(message);
#if defined(__MANAGER_TRACE__)
					 Utility::Memmory::Singleton< Utility::Logger >::instance()
						 .trace((boost::format("TcpToTcpDispatcherHandler::TcpOutputHandler::onAfterPop() [DispatcherID: %s] [ObjectID: %s] [Message: %s]") % getId() % id % message).str());
#endif
                  },
                  Factory::_onError = [&](message_type message, id_type id) {
                     Utility::Memmory::Singleton< Utility::Logger >::instance()
                        .error( (boost::format( "TcpToTcpDispatcherHandler::TcpOutputHandler::onError() [DispatcherID: %s] [ObjectID: %s] [Message: %s]" ) % getId() % id % message).str() );
                     ///
                     last_error_->setLastError( message );
                     performance_->cleanLastPerform(message);
                  }
               ) ) ),
            input_property_( Property::PropertyHandler< Import::Utility::ISettings< Import::ImportType::Tcp > >::getInstance< Property::input >( builder.getInputSettings() ) ),
            output_property_( Property::PropertyHandler< Import::Utility::ISettings< Import::ImportType::Tcp > >::getInstance< Property::output >( builder.getOutputSettings() ) ),
            last_error_( Error::LastErrorHandler< base_type >::getInstance() ),
            performance_( Performance::PerformanceHandler< Performance::PerformanceHandlerType::microseconds >::getInstance() ) {
            queue_handler_->abort();
            queue_handler_->pop( [&](message_type message, id_type id) {
#if defined(__MANAGER_TRACE__)
				Utility::Memmory::Singleton< Utility::Logger >::instance()
					.trace((boost::format("TcpToAmqpDispatcherHandler::QueueHandler::pop() [DispatcherID: %s] [ObjectID: %s] [Message: %s]") % getId() % id % message).str());
#endif
                  output_handler_->produce( move( message ) );
               } );
         }

         TcpToTcpDispatcherHandler::base_type TcpToTcpDispatcherHandler::getId() {
            return meta_->getId();
         }

         TcpToTcpDispatcherHandler::base_type TcpToTcpDispatcherHandler::getDescription() {
            return meta_->getDescription();
         }

         void TcpToTcpDispatcherHandler::start() {
            COBALT_HANDLER_ERROR_GUARD_
               COBALT_HANDLER_STATE_GUARD(isRunning())
               ///
               queue_handler_->start();
               output_handler_->start();
               input_handler_->start();
               state_->start();
               monitor_->onStart( meta_->getId() );
               ///
            COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
         }

         void TcpToTcpDispatcherHandler::stop() {
            COBALT_HANDLER_ERROR_GUARD_
               COBALT_HANDLER_STATE_GUARD(isStopped())
               ///
               input_handler_->stop();
               queue_handler_->abort();
               queue_handler_->stop();
               output_handler_->stop();
               state_->stop();
               monitor_->onStop( meta_->getId() );
               ///
            COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
         }

         void TcpToTcpDispatcherHandler::abort() {
            COBALT_HANDLER_ERROR_GUARD_
               COBALT_HANDLER_STATE_GUARD(isAborted())
               ///
               input_handler_->stop();
               state_->abort();
               ///
            COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
         }

         void TcpToTcpDispatcherHandler::reset() {
            COBALT_HANDLER_ERROR_GUARD_
               COBALT_HANDLER_STATE_GUARD(!isAborted())
               ///
               input_handler_->start();
               state_->start();
               ///
            COBALT_HANDLER_ERROR_GUARD(monitor_, meta_->getId())
         }

         bool TcpToTcpDispatcherHandler::isAborted() const {
            return state_->isAborted();
         }

         bool TcpToTcpDispatcherHandler::isRunning() const {
            return state_->isRunning();
         }

         bool TcpToTcpDispatcherHandler::isStopped() const {
            return state_->isStopped();
         }
      }
   }
}
