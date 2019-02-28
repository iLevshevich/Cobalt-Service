#ifndef __MANAGER_OUTPUT_MONITOR_HANDLER_BUILDER_H_INCLUDED__
#define __MANAGER_OUTPUT_MONITOR_HANDLER_BUILDER_H_INCLUDED__

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
         class OutputMonitorHandlerBuilder;

         template< class T >
         class OutputMonitorHandlerBuilder :
            public IOutputMonitorHandlerBuilder< T > {
         public:
            typedef typename IOutputMonitorHandlerBuilder< T >::function_1_type function_1_type;
            typedef typename IOutputMonitorHandlerBuilder< T >::lambda_1_type lambda_1_type;

            typedef typename IOutputMonitorHandlerBuilder< T >::function_2_type function_2_type;
            typedef typename IOutputMonitorHandlerBuilder< T >::lambda_2_type lambda_2_type;

            OutputMonitorHandlerBuilder() :
               on_start_( nullptr ),
               on_stop_( nullptr ),
               on_error_( nullptr ),
               on_before_pop_( nullptr ),
               on_pop_( nullptr ),
               on_after_pop_( nullptr ) {
            }

            virtual IOutputMonitorHandlerBuilder< T >& __fastcall setOnStart( lambda_1_type f ) override {
               on_start_ = Utility::make_shared_pool< function_1_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IOutputMonitorHandlerBuilder< T >& __fastcall setOnStop( lambda_1_type f ) override {
               on_stop_ = Utility::make_shared_pool< function_1_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IOutputMonitorHandlerBuilder< T >& __fastcall setOnError( lambda_2_type f ) override {
               on_error_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IOutputMonitorHandlerBuilder< T >& __fastcall setOnBeforePop( lambda_2_type f ) override {
               on_before_pop_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IOutputMonitorHandlerBuilder< T >& __fastcall setOnPop( lambda_2_type f ) override {
               on_pop_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IOutputMonitorHandlerBuilder< T >& __fastcall setOnAfterPop( lambda_2_type f ) override {
               on_after_pop_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >( f );
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

            virtual boost::shared_ptr< function_2_type > getOnBeforePop() const override {
               return on_before_pop_;
            }

            virtual boost::shared_ptr< function_2_type > getOnPop() const override {
               return on_pop_;
            }

            virtual boost::shared_ptr< function_2_type > getOnAfterPop() const override {
               return on_after_pop_;
            }

            virtual boost::shared_ptr< IOutputMonitorHandler< T > > build() const override {
               return Utility::make_shared_pool_enable< IOutputMonitorHandler< T >, OutputMonitorHandler< T >, boost::default_user_allocator_malloc_free >( *this );
            }

            virtual ~OutputMonitorHandlerBuilder() = default;

         private:
            boost::shared_ptr< function_1_type > on_start_;
            boost::shared_ptr< function_1_type > on_stop_;
            boost::shared_ptr< function_2_type > on_error_;
            boost::shared_ptr< function_2_type > on_before_pop_;
            boost::shared_ptr< function_2_type > on_pop_;
            boost::shared_ptr< function_2_type > on_after_pop_;
         };

         template<>
         class OutputMonitorHandlerBuilder< void > :
            public IOutputMonitorHandlerBuilder< void > {
         public:
            typedef void base_type;
            typedef typename IOutputMonitorHandlerBuilder< typename base_type >::function_1_type function_1_type;
            typedef typename IOutputMonitorHandlerBuilder< typename base_type >::lambda_1_type lambda_1_type;

            typedef typename IOutputMonitorHandlerBuilder< typename base_type >::function_2_type function_2_type;
            typedef typename IOutputMonitorHandlerBuilder< typename base_type >::lambda_2_type lambda_2_type;

            OutputMonitorHandlerBuilder() :
               on_start_( nullptr ),
               on_stop_( nullptr ),
               on_error_( nullptr ),
               on_before_pop_( nullptr ),
               on_pop_( nullptr ),
               on_after_pop_( nullptr ) {
            }

            virtual IOutputMonitorHandlerBuilder< void >& __fastcall setOnStart( lambda_1_type f ) override {
               on_start_ = Utility::make_shared_pool< function_1_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IOutputMonitorHandlerBuilder< void >& __fastcall setOnStop( lambda_1_type f ) override {
               on_stop_ = Utility::make_shared_pool< function_1_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IOutputMonitorHandlerBuilder< void >& __fastcall setOnError( lambda_2_type f ) override {
               on_error_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IOutputMonitorHandlerBuilder< void >& __fastcall setOnBeforePop( lambda_2_type f ) override {
               on_before_pop_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IOutputMonitorHandlerBuilder< void >& __fastcall setOnPop( lambda_2_type f ) override {
               on_pop_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >( f );
               return *this;
            }

            virtual IOutputMonitorHandlerBuilder< void >& __fastcall setOnAfterPop( lambda_2_type f ) override {
               on_after_pop_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >( f );
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

            virtual boost::shared_ptr< function_2_type > getOnBeforePop() const override {
               return on_before_pop_;
            }

            virtual boost::shared_ptr< function_2_type > getOnPop() const override {
               return on_pop_;
            }

            virtual boost::shared_ptr< function_2_type > getOnAfterPop() const override {
               return on_after_pop_;
            }

            virtual boost::shared_ptr< IOutputMonitorHandler< void > > build() const override {
               return Utility::make_shared_pool_enable< IOutputMonitorHandler< void >, OutputMonitorHandler< void >, boost::default_user_allocator_malloc_free >( *this );
            }

            virtual ~OutputMonitorHandlerBuilder() = default;

         private:
            boost::shared_ptr< function_1_type > on_start_;
            boost::shared_ptr< function_1_type > on_stop_;
            boost::shared_ptr< function_2_type > on_error_;
            boost::shared_ptr< function_2_type > on_before_pop_;
            boost::shared_ptr< function_2_type > on_pop_;
            boost::shared_ptr< function_2_type > on_after_pop_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_OUTPUT_MONITOR_HANDLER_BUILDER_H_INCLUDED__
