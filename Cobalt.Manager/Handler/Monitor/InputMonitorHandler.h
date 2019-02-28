#ifndef __MANAGER_INPUT_MONITOR_HANDLER_H_INCLUDED__
#define __MANAGER_INPUT_MONITOR_HANDLER_H_INCLUDED__

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
         class InputMonitorHandler;

         template< class T >
         class InputMonitorHandler :
            public IInputMonitorHandler< T > {
         public:
            typedef typename IInputMonitorHandler< T >::handle_arg_type handle_arg_type;
            typedef typename IMonitorHandler< T >::monitor_arg_type monitor_arg_type;
            typedef typename Utility::Traits< std::function< void( typename handle_arg_type ) > >::base_t function_1_type;
            typedef typename Utility::Traits< std::function< void( typename handle_arg_type, typename handle_arg_type ) > >::base_t function_2_type;

            virtual void __fastcall onBeforePush( handle_arg_type f1, handle_arg_type f2 ) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_2_ARG(on_before_push_, f1, f2);
            }

            virtual void __fastcall onPush( handle_arg_type f1, handle_arg_type f2 ) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_2_ARG(on_push_, f1, f2);
            }

            virtual void __fastcall onAfterPush( handle_arg_type f1, handle_arg_type f2 ) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_2_ARG(on_after_push_, f1, f2);
            }

            virtual void __fastcall onStart( monitor_arg_type f ) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_1_ARG(on_start_,f);
            }

            virtual void __fastcall onStop( monitor_arg_type f ) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_1_ARG(on_stop_,f);
            }

            virtual void __fastcall onError( monitor_arg_type f1, monitor_arg_type f2 ) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_2_ARG(on_error_, f1, f2);
            }

            virtual ~InputMonitorHandler() = default;

         protected:
            explicit InputMonitorHandler( const IInputMonitorHandlerBuilder< T >& builder ) :
               on_before_push_( builder.getOnBeforePush() ),
               on_push_( builder.getOnPush() ),
               on_after_push_( builder.getOnAfterPush() ),
               on_start_( builder.getOnStart() ),
               on_stop_( builder.getOnStop() ),
               on_error_( builder.getOnError() ) {
            }

         private:
            boost::shared_ptr< function_2_type > on_before_push_;
            boost::shared_ptr< function_2_type > on_push_;
            boost::shared_ptr< function_2_type > on_after_push_;
            boost::shared_ptr< function_1_type > on_start_;
            boost::shared_ptr< function_1_type > on_stop_;
            boost::shared_ptr< function_2_type > on_error_;
         };

         template<>
         class InputMonitorHandler< void > :
            public IInputMonitorHandler< void > {
         public:
            typedef typename Utility::Traits< std::function< void() > >::base_t function_type;

            virtual void __fastcall onBeforePush() override {
               COBALT_MONITOR_IF_EXIST_HANDLER(on_before_push_);
            }

            virtual void __fastcall onPush() override {
               COBALT_MONITOR_IF_EXIST_HANDLER(on_push_);
            }

            virtual void __fastcall onAfterPush() override {
               COBALT_MONITOR_IF_EXIST_HANDLER(on_after_push_);
            }

            virtual void __fastcall onStart() override {
               COBALT_MONITOR_IF_EXIST_HANDLER(on_start_);
            }

            virtual void __fastcall onStop() override {
               COBALT_MONITOR_IF_EXIST_HANDLER(on_stop_);
            }

            virtual void __fastcall onError() override {
               COBALT_MONITOR_IF_EXIST_HANDLER(on_error_);
            }

            virtual ~InputMonitorHandler() = default;

         protected:
            explicit InputMonitorHandler( const IInputMonitorHandlerBuilder< void >& builder ) :
               on_before_push_( builder.getOnBeforePush() ),
               on_push_( builder.getOnPush() ),
               on_after_push_( builder.getOnAfterPush() ),
               on_start_( builder.getOnStart() ),
               on_stop_( builder.getOnStop() ),
               on_error_( builder.getOnError() ) {
            }

         private:
            boost::shared_ptr< function_type > on_before_push_;
            boost::shared_ptr< function_type > on_push_;
            boost::shared_ptr< function_type > on_after_push_;
            boost::shared_ptr< function_type > on_start_;
            boost::shared_ptr< function_type > on_stop_;
            boost::shared_ptr< function_type > on_error_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_INPUT_MONITOR_HANDLER_H_INCLUDED__
