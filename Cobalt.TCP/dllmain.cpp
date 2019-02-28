#include "stdafx.h"

#include "Utility/Traits.h"
#include "Utility/MakeAsync.h"

#include "Memmory/Buffer.h"

#include "Utility/Settings/ISettings.h"
#include "Utility/Settings/Builder/ISettingsBuilder.h"
#include "Utility/Settings/Settings.h"
#include "Utility/Settings/Builder/SettingsBuilder.h"

#include "Tcp/Client/BlockClient.h"
#include "Tcp/Server/BlockServer.h"

#include "EntryPoint/IConsume.h"
#include "EntryPoint/Consume.h"

#include "EntryPoint/IPublish.h"
#include "EntryPoint/Publish.h"

#include "dllmain.h"

namespace EntryPoint
{
   const char* __stdcall internal_version() {
      return __INTERNAL_VERSION__;
   }

   const char* __stdcall internal_guid() {
      return __INTERNAL_GUID__;
   }

   BOOST_DLL_ALIAS(Cobalt::Utility::SettingsBuilder::getInstance, settings_builder_instance)
   BOOST_DLL_ALIAS(Cobalt::EntryPoint::Consume::getInstance, consume_instance)
   BOOST_DLL_ALIAS(Cobalt::EntryPoint::Publish::getInstance, publish_instance)

   BOOST_DLL_AUTO_ALIAS(internal_version)
   BOOST_DLL_AUTO_ALIAS(internal_guid)
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

