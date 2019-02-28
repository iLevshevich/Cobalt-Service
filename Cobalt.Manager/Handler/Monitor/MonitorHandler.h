#ifndef __MANAGER_MONITOR_HANDLER_H_INCLUDED__
#define __MANAGER_MONITOR_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Monitor
      {
         template< class T >
         class MonitorHandler;

         template< class T >
         class MonitorHandler :
            public IMonitorHandler< T > {
         public:
            typedef typename IMonitorHandler< T >::monitor_arg_type monitor_arg_type;
            typedef typename Utility::Traits< std::function< void(monitor_arg_type) > >::base_t function_1_type;
            typedef typename Utility::Traits< std::function< void(monitor_arg_type, monitor_arg_type) > >::base_t function_2_type;

            virtual void __fastcall onStart(monitor_arg_type f) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_1_ARG(on_start_, f);
            }

            virtual void __fastcall onStop(monitor_arg_type f) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_1_ARG(on_stop_, f);
            }

            virtual void __fastcall onError(monitor_arg_type f1, monitor_arg_type f2) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_2_ARG(on_error_, f1, f2);
            }

            virtual ~MonitorHandler() = default;

         protected:
            explicit MonitorHandler(const IMonitorHandlerBuilder< T >& builder) :
               on_start_(builder.getOnStart()),
               on_stop_(builder.getOnStop()),
               on_error_(builder.getOnError()) {
            }

         private:
            boost::shared_ptr< function_1_type > on_start_;
            boost::shared_ptr< function_1_type > on_stop_;
            boost::shared_ptr< function_2_type > on_error_;
         };

         template<>
         class MonitorHandler< void > :
            public IMonitorHandler< void > {
         public:
            typedef typename Utility::Traits< std::function< void() > >::base_t function_type;

            virtual void __fastcall onStart() override {
               COBALT_MONITOR_IF_EXIST_HANDLER(on_start_);
            }

            virtual void __fastcall onStop() override {
               COBALT_MONITOR_IF_EXIST_HANDLER(on_stop_);
            }

            virtual void __fastcall onError() override {
               COBALT_MONITOR_IF_EXIST_HANDLER(on_error_);
            }

            virtual ~MonitorHandler() = default;

         protected:
            explicit MonitorHandler(const IMonitorHandlerBuilder< void >& builder) :
               on_start_(builder.getOnStart()),
               on_stop_(builder.getOnStop()),
               on_error_(builder.getOnError()) {
            }

         private:
            boost::shared_ptr< function_type > on_start_;
            boost::shared_ptr< function_type > on_stop_;
            boost::shared_ptr< function_type > on_error_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_MONITOR_HANDLER_H_INCLUDED__
