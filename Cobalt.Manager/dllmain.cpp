#include "stdafx.h"

#include "Import/ImportType.h"
#include "Utility/Traits.h"
#include "Utility/EnableMake.h"
#include "Utility/MakeAsync.h"
#include "Utility/Min.h"
#include "Utility/Singleton.h"
#include "Utility/MakeObject.h"
#include "Utility/Options.h"
#include "Utility/Logger.h"
#include "Utility/LexicalCast.h"
#include "Utility/Buffer.h"

#include "Import/Utility/ExchangeType.h"
#include "Import/Utility/FlagsType.h"
#include "Import/Utility/Settings/IChannelSettings.h"
#include "Import/Utility/Settings/IConnectionSettings.h"
#include "Import/Utility/Settings/IExchangeSettings.h"
#include "Import/Utility/Settings/IHostSettings.h"
#include "Import/Utility/Settings/ILoginSettings.h"
#include "Import/Utility/Settings/IQueueSettings.h"
#include "Import/Utility/Settings/ISettings.h"
#include "Import/Utility/Settings/ISettings.h"
#include "Import/Utility/Settings/Builder/ISettingsBuilder.h"
#include "Import/IConsume.h"
#include "Import/IPublish.h"

#include "Factory/IImportFactory.h"
#include "Factory/ImportFactory.h"

#include "Handler/Performance/PerformanceHandlerType.h"
#include "Handler/Performance/IPerformanceHandler.h"
#include "Handler/Performance/PerformanceHandler.h"

#include "Handler/Error/ILastErrorHandler.h"
#include "Handler/Error/LastErrorHandler.h"

#include "Handler/State/StateHandlerType.h"
#include "Handler/State/IResetHandler.h"
#include "Handler/State/IStateHandler.h"
#include "Handler/State/StateHandler.h"

#include "Handler/Input/Acknowledge/IInputHandlerAcknowledge.h"
#include "Handler/Input/Acknowledge/InputHandlerAcknowledge.h"
#include "Handler/Input/Acknowledge/InputHandlerNoAcknowledge.h"

#include "Handler/Output/Acknowledge/IOutputHandlerAcknowledge.h"
#include "Handler/Output/Acknowledge/OutputHandlerAcknowledge.h"
#include "Handler/Output/Acknowledge/OutputHandlerNoAcknowledge.h"

#include "Handler/Meta/IMetaHandler.h"
#include "Handler/Meta/MetaHandler.h"

#include "Handler/Monitor/IMonitorHandler.h"
#include "Handler/Monitor/Builder/IMonitorHandlerBuilder.h"
#include "Handler/Monitor/MonitorHandler.h"
#include "Handler/Monitor/Builder/MonitorHandlerBuilder.h"

#include "Handler/Monitor/IInputMonitorHandler.h"
#include "Handler/Monitor/Builder/IInputMonitorHandlerBuilder.h"
#include "Handler/Monitor/InputMonitorHandler.h"
#include "Handler/Monitor/Builder/InputMonitorHandlerBuilder.h"

#include "Handler/Input/IInputHandler.h"
#include "Handler/Input/Builder/IInputHandlerBuilder.h"
#include "Handler/Input/Builder/InputHandlerBuilder.h"
#include "Handler/Input/InputHandler.h"

#include "Handler/Monitor/IOutputMonitorHandler.h"
#include "Handler/Monitor/Builder/IOutputMonitorHandlerBuilder.h"

#include "Handler/Monitor/OutputMonitorHandler.h"
#include "Handler/Monitor/Builder/OutputMonitorHandlerBuilder.h"

#include "Handler/Output/IOutputHandler.h"
#include "Handler/Output/Builder/IOutputHandlerBuilder.h"
#include "Handler/Output/Builder/OutputHandlerBuilder.h"
#include "Handler/Output/OutputHandler.h"

#include "Handler/Queue/IQueueHandler.h"
#include "Handler/Queue/Builder/IQueueHandlerBuilder.h"
#include "Handler/Queue/Builder/QueueHandlerBuilder.h"
#include "Handler/Queue/QueueHandler.h"

#include "Handler/Queue/BlockQueue.h"
#include "Handler/Queue/Builder/IBlockQueueHandlerBuilder.h"
#include "Handler/Queue/Builder/BlockQueueHandlerBuilder.h"
#include "Handler/Queue/BlockQueueHandler.h"

#include "Handler/Property/PropertyHandlerType.h"
#include "Handler/Property/IPropertyHandler.h"
#include "Handler/Property/PropertyHandler.h"

#include "Handler/Dispatcher/DispatcherHandlerType.h"
#include "Handler/Dispatcher/DispatcherHandlerPriority.h"
#include "Handler/Dispatcher/IDispatcherHandler.h"

#include "Handler/Dispatcher/Builder/IAmqpToAmqpDispatcherHandlerBuilder.h"
#include "Handler/Dispatcher/Builder/AmqpToAmqpDispatcherHandlerBuilder.h"
#include "Handler/Dispatcher/AmqpToAmqpDispatcherHandler.h"

#include "Handler/Dispatcher/Builder/IAmqpToTcpDispatcherHandlerBuilder.h"
#include "Handler/Dispatcher/Builder/AmqpToTcpDispatcherHandlerBuilder.h"
#include "Handler/Dispatcher/AmqpToTcpDispatcherHandler.h"

#include "Handler/Dispatcher/Builder/ITcpToAmqpDispatcherHandlerBuilder.h"
#include "Handler/Dispatcher/Builder/TcpToAmqpDispatcherHandlerBuilder.h"
#include "Handler/Dispatcher/TcpToAmqpDispatcherHandler.h"

#include "Handler/Dispatcher/Builder/ITcpToTcpDispatcherHandlerBuilder.h"
#include "Handler/Dispatcher/Builder/TcpToTcpDispatcherHandlerBuilder.h"
#include "Handler/Dispatcher/TcpToTcpDispatcherHandler.h"

#include "Handler/Repository/IRepositoryHandler.h"
#include "Handler/Repository/RepositoryHandler.h"

#include "Factory/ObjectFactory.h"

#include "Core/Chain/Configuration/IConfigChain.h"
#include "Core/Chain/Configuration/AmqpToAmqpConfigChain.h"
#include "Core/Chain/Configuration/TcpToTcpConfigChain.h"
#include "Core/Chain/Configuration/AmqpToTcpConfigChain.h"
#include "Core/Chain/Configuration/TcpToAmqpConfigChain.h"
#include "Core/Repository.h"

#include "Core/Chain/Operation/OperationType.h"
#include "Core/Chain/Operation/IOperationChain.h"
#include "Core/Chain/Operation/SecurityClientOperationChain.h"
#include "Core/Chain/Operation/GetStatusesOperationChain.h"
#include "Core/Chain/Operation/SaveConfigurationOperationChain.h"
#include "Core/Chain/Operation/StartDispatchersOperationChain.h"
#include "Core/Chain/Operation/StopDispatchersOperationChain.h"
#include "Core/Chain/Operation/AbortDispatchersOperationChain.h"
#include "Core/Chain/Operation/ResetDispatchersOperationChain.h"
#include "Core/Chain/Operation/CleanLastErrorsOperationChain.h"
#include "Core/Chain/Operation/StartDispatcherOperationChain.h"
#include "Core/Chain/Operation/StopDispatcherOperationChain.h"
#include "Core/Chain/Operation/AbortDispatcherOperationChain.h"
#include "Core/Chain/Operation/ResetDispatcherOperationChain.h"
#include "Core/Chain/Operation/CleanLastErrorOperationChain.h"
#include "Core/Chain/Operation/AddDispatcherOperationChain.h"
#include "Core/Chain/Operation/RemoveDispatcherOperationChain.h"
#include "Core/Chain/Operation/GetDispatcherTypesOperationChain.h"
#include "Core/Chain/Operation/UnKnownOperationChain.h"
#include "Core/Server.h"
#include "Core/Core.h"

#include "dllmain.h"

namespace EntryPoint
{
   const char* __stdcall internal_version() {
      return __INTERNAL_VERSION__;
   }

   const char* __stdcall internal_guid() {
      return __INTERNAL_GUID__;
   }

   void init( int argc, boost::shared_ptr< char*[] > argv ) {
      Cobalt::Utility::Memmory::Singleton< Cobalt::Utility::Options >::instance().init( argc, argv.get() );
      Cobalt::Utility::Memmory::Singleton< Cobalt::Utility::Logger >::instance().init();
   }

   void run() {
      const std::string dispatchers_path( Cobalt::Utility::Memmory::Singleton< Cobalt::Utility::Options >::instance().get( Cobalt::Utility::Options::DISPATCHERS_FILE_PATH ) );
      const std::string server_port( Cobalt::Utility::Memmory::Singleton< Cobalt::Utility::Options >::instance().get( Cobalt::Utility::Options::MANAGEMENT_SERVER_PORT ) );

      Cobalt::Utility::Memmory::Singleton< Cobalt::Core::Core >::instance().run( dispatchers_path, server_port );
   }

   void stop() {
      Cobalt::Utility::Memmory::Singleton< Cobalt::Core::Core >::instance().stop();
   }

   BOOST_DLL_AUTO_ALIAS(internal_version)
   BOOST_DLL_AUTO_ALIAS(internal_guid)
   BOOST_DLL_AUTO_ALIAS(init)
   BOOST_DLL_AUTO_ALIAS(run)
   BOOST_DLL_AUTO_ALIAS(stop)
}

BOOL APIENTRY DllMain( const HMODULE /*hModule*/,
                       const DWORD reason,
                       const LPVOID /*lpReserved*/ ) {
   switch( reason ) {
   case DLL_PROCESS_ATTACH:
   case DLL_THREAD_ATTACH:
   case DLL_THREAD_DETACH:
   case DLL_PROCESS_DETACH:
      break;
   }
   return TRUE;
}
