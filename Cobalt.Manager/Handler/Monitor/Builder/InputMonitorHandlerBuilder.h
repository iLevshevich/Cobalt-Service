#ifndef __MANAGER_INPUT_MONITOR_HANDLER_BUILDER_H_INCLUDED__
#define __MANAGER_INPUT_MONITOR_HANDLER_BUILDER_H_INCLUDED__

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
         class InputMonitorHandlerBuilder;

         template< class T >
         class InputMonitorHandlerBuilder :
            public IInputMonitorHandlerBuilder< T > {
         public:
            typedef typename IInputMonitorHandlerBuilder< T >::function_1_type function_1_type;
            typedef typename IInputMonitorHandlerBuilder< T >::lambda_1_type lambda_1_type;

            typedef typename IInputMonitorHandlerBuilder< T >::function_2_type function_2_type;
            typedef typename IInputMonitorHandlerBuilder< T >::lambda_2_type lambda_2_type;

            InputMonitorHandlerBuilder() :
               on_start_(nullptr),
               on_stop_(nullptr),
               on_error_(nullptr),
               on_before_push_(nullptr),
               on_push_(nullptr),
               on_after_push_(nullptr) {
            }

            virtual IInputMonitorHandlerBuilder< T >& __fastcall setOnStart(lambda_1_type f) override {
               on_start_ = Utility::make_shared_pool< function_1_type, boost::default_user_allocator_malloc_free >(f);
               return *this;
            }

            virtual IInputMonitorHandlerBuilder< T >& __fastcall setOnStop(lambda_1_type f) override {
               on_stop_ = Utility::make_shared_pool< function_1_type, boost::default_user_allocator_malloc_free >(f);
               return *this;
            }

            virtual IInputMonitorHandlerBuilder< T >& __fastcall setOnError(lambda_2_type f) override {
               on_error_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >(f);
               return *this;
            }

            virtual IInputMonitorHandlerBuilder< T >& __fastcall setOnBeforePush(lambda_2_type f) override {
               on_before_push_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >(f);
               return *this;
            }

            virtual IInputMonitorHandlerBuilder< T >& __fastcall setOnPush(lambda_2_type f) override {
               on_push_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >(f);
               return *this;
            }

            virtual IInputMonitorHandlerBuilder< T >& __fastcall setOnAfterPush(lambda_2_type f) override {
               on_after_push_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >(f);
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

            virtual boost::shared_ptr< function_2_type > getOnBeforePush() const override {
               return on_before_push_;
            }

            virtual boost::shared_ptr< function_2_type > getOnPush() const override {
               return on_push_;
            }

            virtual boost::shared_ptr< function_2_type > getOnAfterPush() const override {
               return on_after_push_;
            }

            virtual boost::shared_ptr< IInputMonitorHandler< T > > build() const override {
               return Utility::make_shared_pool_enable< IInputMonitorHandler< T >, InputMonitorHandler< T >, boost::default_user_allocator_malloc_free >(*this);
            }

            virtual ~InputMonitorHandlerBuilder() = default;

         private:
            boost::shared_ptr< function_1_type > on_start_;
            boost::shared_ptr< function_1_type > on_stop_;
            boost::shared_ptr< function_2_type > on_error_;
            boost::shared_ptr< function_2_type > on_before_push_;
            boost::shared_ptr< function_2_type > on_push_;
            boost::shared_ptr< function_2_type > on_after_push_;
         };

         template<>
         class InputMonitorHandlerBuilder< void > :
            public IInputMonitorHandlerBuilder< void > {
         public:
            typedef void base_type;
            typedef typename IInputMonitorHandlerBuilder< typename base_type >::function_1_type function_1_type;
            typedef typename IInputMonitorHandlerBuilder< typename base_type >::lambda_1_type lambda_1_type;

            typedef typename IInputMonitorHandlerBuilder< typename base_type >::function_2_type function_2_type;
            typedef typename IInputMonitorHandlerBuilder< typename base_type >::lambda_2_type lambda_2_type;

            InputMonitorHandlerBuilder() :
               on_start_(nullptr),
               on_stop_(nullptr),
               on_error_(nullptr),
               on_before_push_(nullptr),
               on_push_(nullptr),
               on_after_push_(nullptr) {
            }

            virtual IInputMonitorHandlerBuilder< void >& __fastcall setOnStart(lambda_1_type f) override {
               on_start_ = Utility::make_shared_pool< function_1_type, boost::default_user_allocator_malloc_free >(f);
               return *this;
            }

            virtual IInputMonitorHandlerBuilder< void >& __fastcall setOnStop(lambda_1_type f) override {
               on_stop_ = Utility::make_shared_pool< function_1_type, boost::default_user_allocator_malloc_free >(f);
               return *this;
            }

            virtual IInputMonitorHandlerBuilder< void >& __fastcall setOnError(lambda_2_type f) override {
               on_error_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >(f);
               return *this;
            }

            virtual IInputMonitorHandlerBuilder< void >& __fastcall setOnBeforePush(lambda_2_type f) override {
               on_before_push_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >(f);
               return *this;
            }

            virtual IInputMonitorHandlerBuilder< void >& __fastcall setOnPush(lambda_2_type f) override {
               on_push_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >(f);
               return *this;
            }

            virtual IInputMonitorHandlerBuilder< void >& __fastcall setOnAfterPush(lambda_2_type f) override {
               on_after_push_ = Utility::make_shared_pool< function_2_type, boost::default_user_allocator_malloc_free >(f);
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

            virtual boost::shared_ptr< function_2_type > getOnBeforePush() const override {
               return on_before_push_;
            }

            virtual boost::shared_ptr< function_2_type > getOnPush() const override {
               return on_push_;
            }

            virtual boost::shared_ptr< function_2_type > getOnAfterPush() const override {
               return on_after_push_;
            }

            virtual boost::shared_ptr< IInputMonitorHandler< void > > build() const override {
               return Utility::make_shared_pool_enable< IInputMonitorHandler< void >, InputMonitorHandler< void >, boost::default_user_allocator_malloc_free >(*this);
            }

            virtual ~InputMonitorHandlerBuilder() = default;

         private:
            boost::shared_ptr< function_1_type > on_start_;
            boost::shared_ptr< function_1_type > on_stop_;
            boost::shared_ptr< function_2_type > on_error_;
            boost::shared_ptr< function_2_type > on_before_push_;
            boost::shared_ptr< function_2_type > on_push_;
            boost::shared_ptr< function_2_type > on_after_push_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_INPUT_MONITOR_HANDLER_BUILDER_H_INCLUDED__
