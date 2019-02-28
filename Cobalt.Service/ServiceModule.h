#ifndef __SERVICE_MODULE_H_INCLUDED__
#define __SERVICE_MODULE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#pragma pack( push, 8 )

namespace Cobalt
{
   class ServiceModule : public ATL::CAtlServiceModuleT< ServiceModule, IDS_SERVICENAME > {
   public:
      DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SERVICE, "{01D73C58-D8F4-4A85-B27D-424443739977}")

      HRESULT InitializeSecurity() throw() {
         return S_OK;
      }

      HRESULT PreMessageLoop(int nShowCmd) throw() {
         const HRESULT result(CAtlServiceModuleT< ServiceModule, IDS_SERVICENAME >::PreMessageLoop(nShowCmd));
         if (SUCCEEDED(result)) {
            Cobalt::Core& core(Cobalt::Singleton< Cobalt::Core >::instance());
            core.Run();
         }
         return result;
      }

      HRESULT PostMessageLoop() throw() {
         Cobalt::Core& core(Cobalt::Singleton< Cobalt::Core >::instance());
         core.Stop();

         return CAtlServiceModuleT< ServiceModule, IDS_SERVICENAME >::PostMessageLoop();
      }

      void RunMessageLoop() throw() {
         CAtlServiceModuleT< ServiceModule, IDS_SERVICENAME >::RunMessageLoop();
      }

      void OnContinue() throw() {
         CAtlServiceModuleT< ServiceModule, IDS_SERVICENAME >::OnContinue();
      }

      void OnPause() throw() {
         CAtlServiceModuleT< ServiceModule, IDS_SERVICENAME >::OnPause();
      }

      void OnShutdown() throw() {
         OnStop();
      }

      void OnStop() throw() {
         CAtlServiceModuleT< ServiceModule, IDS_SERVICENAME >::OnStop();
      }
   };
}

#pragma pack( pop )

#endif //__SERVICE_MODULE_H_INCLUDED__
