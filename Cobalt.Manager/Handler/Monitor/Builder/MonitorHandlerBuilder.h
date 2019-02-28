#ifndef __MANAGER_MONITOR_HANDLER_BUILDER_H_INCLUDED__
#define __MANAGER_MONITOR_HANDLER_BUILDER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Monitor
      {
         template< class T >
         class MonitorHandlerBuilder;

         template< class T >
         class MonitorHandlerBuilder :
            public IMonitorHandlerBuilder< T > {
         public:
            typedef typename IMonitorHandlerBuilder< T >::function_1_type function_1_type;
            typedef typename IMonitorHandlerBuilder< T >::lambda_1_type lambda_1_type;

            typedef typename IMonitorHandlerBuilder< T >::function_2_type function_2_type;
            typedef typename IMonitorHandlerBuilder< T >::lambda_2_type lambda_2_type;

            MonitorHandlerBuilder():
               on_start_( nullptr ),
               on_stop_( nullptr ),
               on_error_( nullptr ) {
            }

            virtual IMonitorHandlerBuilder< T >& __fastcall setOnStart( lambda_1_type f ) override {
               on_start_ = Utility::make_shared_pool< function_1_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IMonitorHandlerBuilder< T >& __fastcall setOnStop( lambda_1_type f ) override {
               on_stop_ = Utility::make_shared_pool< function_1_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IMonitorHandlerBuilder< T >& __fastcall setOnError( lambda_2_type f ) override {
               on_error_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual boost::shared_ptr< function_1_type > getOnStart() const override {
               return on_start_;
            }

            virtual boost::shared_ptr< function_1_type > getOnStop() const override {
               return on_stop_;
            }

            virtual boost::shared_ptr< function_2_type > getOnError() const override {
               return on_error_;
            }

            virtual boost::shared_ptr< IMonitorHandler< T > > build() const override {
               return Utility::make_shared_pool_enable< IMonitorHandler< T >, MonitorHandler< T >, boost::default_user_allocator_malloc_free >( *this );
            }

            virtual ~MonitorHandlerBuilder() = default;

         private:
            boost::shared_ptr< function_1_type > on_start_;
            boost::shared_ptr< function_1_type > on_stop_;
            boost::shared_ptr< function_2_type > on_error_;

         };

         template<>
         class MonitorHandlerBuilder< void > :
            public IMonitorHandlerBuilder< void > {
         public:
            typedef void base_type;
            typedef typename IMonitorHandlerBuilder< typename base_type >::function_1_type function_1_type;
            typedef typename IMonitorHandlerBuilder< typename base_type >::lambda_1_type lambda_1_type;

            typedef typename IMonitorHandlerBuilder< typename base_type >::function_2_type function_2_type;
            typedef typename IMonitorHandlerBuilder< typename base_type >::lambda_2_type lambda_2_type;

            MonitorHandlerBuilder() :
               on_start_( nullptr ),
               on_stop_( nullptr ),
               on_error_( nullptr ) {
            }

            virtual IMonitorHandlerBuilder< void >& __fastcall setOnStart( lambda_1_type f ) override {
               on_start_ = Utility::make_shared_pool< function_1_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IMonitorHandlerBuilder< void >& __fastcall setOnStop( lambda_1_type f ) override {
               on_stop_ = Utility::make_shared_pool< function_1_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IMonitorHandlerBuilder< void >& __fastcall setOnError( lambda_2_type f ) override {
               on_error_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual boost::shared_ptr< function_1_type > getOnStart() const override {
               return on_start_;
            }

            virtual boost::shared_ptr< function_1_type > getOnStop() const override {
               return on_stop_;
            }

            virtual boost::shared_ptr< function_2_type > getOnError() const override {
               return on_error_;
            }

            virtual boost::shared_ptr< IMonitorHandler< void > > build() const override {
               return Utility::make_shared_pool_enable< IMonitorHandler< void >, MonitorHandler< void >, boost::default_user_allocator_malloc_free >( *this );
            }

            virtual ~MonitorHandlerBuilder() = default;

         private:
            boost::shared_ptr< function_1_type > on_start_;
            boost::shared_ptr< function_1_type > on_stop_;
            boost::shared_ptr< function_2_type > on_error_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_MONITOR_HANDLER_BUILDER_H_INCLUDED__
