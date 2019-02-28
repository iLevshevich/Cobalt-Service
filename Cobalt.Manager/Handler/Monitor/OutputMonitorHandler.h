#ifndef __MANAGER_OUTPUT_MONITOR_HANDLER_H_INCLUDED__
#define __MANAGER_OUTPUT_MONITOR_HANDLER_H_INCLUDED__

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
         class OutputMonitorHandler;

         template< class T >
         class OutputMonitorHandler :
            public IOutputMonitorHandler< T > {
         public:
            typedef typename IOutputMonitorHandler< T >::handle_arg_type handle_arg_type;
            typedef typename IMonitorHandler< T >::monitor_arg_type monitor_arg_type;
            typedef typename Utility::Traits< std::function< void( typename handle_arg_type ) > >::base_t function_1_type;
            typedef typename Utility::Traits< std::function< void( typename handle_arg_type, typename handle_arg_type ) > >::base_t function_2_type;

            virtual void __fastcall onBeforePop( handle_arg_type f1, handle_arg_type f2 ) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_2_ARG( on_before_pop_, f1, f2 );
            }

            virtual void __fastcall onPop( handle_arg_type f1, handle_arg_type f2 ) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_2_ARG( on_pop_, f1, f2 );
            }

            virtual void __fastcall onAfterPop( handle_arg_type f1, handle_arg_type f2 ) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_2_ARG( on_after_pop_, f1, f2 );
            }

            virtual void __fastcall onStart( monitor_arg_type f ) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_1_ARG( on_start_, f );
            }

            virtual void __fastcall onStop( monitor_arg_type f ) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_1_ARG( on_stop_, f );
            }

            virtual void __fastcall onError( monitor_arg_type f1, monitor_arg_type f2 ) override {
               COBALT_MONITOR_IF_EXIST_HANDLER_2_ARG( on_error_, f1, f2 );
            }

            virtual ~OutputMonitorHandler() = default;

         protected:
            explicit OutputMonitorHandler( const IOutputMonitorHandlerBuilder< T >& builder ) :
               on_before_pop_( builder.getOnBeforePop() ),
               on_pop_( builder.getOnPop() ),
               on_after_pop_( builder.getOnAfterPop() ),
               on_start_( builder.getOnStart() ),
               on_stop_( builder.getOnStop() ),
               on_error_( builder.getOnError() ) {
            }

         private:
            boost::shared_ptr< function_2_type > on_before_pop_;
            boost::shared_ptr< function_2_type > on_pop_;
            boost::shared_ptr< function_2_type > on_after_pop_;
            boost::shared_ptr< function_1_type > on_start_;
            boost::shared_ptr< function_1_type > on_stop_;
            boost::shared_ptr< function_2_type > on_error_;
         };

         template<>
         class OutputMonitorHandler< void > :
            public IOutputMonitorHandler< void > {
         public:
            typedef typename Utility::Traits< std::function< void() > >::base_t function_type;

            virtual void __fastcall onBeforePop() override {
               COBALT_MONITOR_IF_EXIST_HANDLER( on_before_pop_ );
            }

            virtual void __fastcall onPop() override {
               COBALT_MONITOR_IF_EXIST_HANDLER( on_pop_ );
            }

            virtual void __fastcall onAfterPop() override {
               COBALT_MONITOR_IF_EXIST_HANDLER( on_after_pop_ );
            }

            virtual void __fastcall onStart() override {
               COBALT_MONITOR_IF_EXIST_HANDLER( on_start_ );
            }

            virtual void __fastcall onStop() override {
               COBALT_MONITOR_IF_EXIST_HANDLER( on_stop_ );
            }

            virtual void __fastcall onError() override {
               COBALT_MONITOR_IF_EXIST_HANDLER( on_error_ );
            }

            virtual ~OutputMonitorHandler() = default;

         protected:
            explicit OutputMonitorHandler( const IOutputMonitorHandlerBuilder< void >& builder ) :
               on_before_pop_( builder.getOnBeforePop() ),
               on_pop_( builder.getOnPop() ),
               on_after_pop_( builder.getOnAfterPop() ),
               on_start_( builder.getOnStart() ),
               on_stop_( builder.getOnStop() ),
               on_error_( builder.getOnError() ) {
            }

         private:
            boost::shared_ptr< function_type > on_before_pop_;
            boost::shared_ptr< function_type > on_pop_;
            boost::shared_ptr< function_type > on_after_pop_;
            boost::shared_ptr< function_type > on_start_;
            boost::shared_ptr< function_type > on_stop_;
            boost::shared_ptr< function_type > on_error_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_OUTPUT_MONITOR_HANDLER_H_INCLUDED__
