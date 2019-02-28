#include "stdafx.h"

#include "Utility/Settings/ISettings.h"
#include "Utility/Settings/Settings.h"

#include "Utility/Settings/Builder/ISettingsBuilder.h"
#include "Utility/Settings/Builder/SettingsBuilder.h"

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

BOOL APIENTRY DllMain( const HMODULE hModule,
                       const DWORD reason,
                       const LPVOID lpReserved ) {
   switch( reason ) {
   case DLL_PROCESS_ATTACH:
   case DLL_THREAD_ATTACH:
   case DLL_THREAD_DETACH:
   case DLL_PROCESS_DETACH:
      break;
   }
   return TRUE;
}
