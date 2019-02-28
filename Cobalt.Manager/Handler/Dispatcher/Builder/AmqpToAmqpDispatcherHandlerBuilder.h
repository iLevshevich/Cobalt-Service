#ifndef __MANAGER_AMQP_TO_AMQP_DISPATCHER_HANDLER_BUILDER_H_INCLUDED__
#define __MANAGER_AMQP_TO_AMQP_DISPATCHER_HANDLER_BUILDER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Dispatcher
      {
         template< class T, class U >
         class AmqpToAmqpDispatcherHandlerBuilder :
            public IAmqpToAmqpDispatcherHandlerBuilder< T > {
         public:
            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::base_type base_type;

            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::state_type state_type;
            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::state_base_type state_base_type;

            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::meta_type meta_type;
            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::meta_base_type meta_base_type;

            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::factory_type factory_type;
            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::factory_base_type factory_base_type;

            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::settings_type settings_type;
            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::settings_base_type settings_base_type;

            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::input_acknowledge_type input_acknowledge_type;
            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::input_acknowledge_base_type input_acknowledge_base_type;

            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::output_acknowledge_type output_acknowledge_type;
            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::output_acknowledge_base_type output_acknowledge_base_type;

            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::key_type key_type;
            typedef typename IAmqpToAmqpDispatcherHandlerBuilder< T >::key_base_type key_base_type;

            AmqpToAmqpDispatcherHandlerBuilder() :
               state_( nullptr ),
               meta_( nullptr ),
               input_factory_( nullptr ),
               input_acknowledge_( nullptr ),
               input_settings_( nullptr ),
               input_key_( key_base_type() ),
               output_factory_( nullptr ),
               output_acknowledge_( nullptr ),
               output_settings_( nullptr ),
               output_key_( key_base_type() ) {
            }

            virtual IAmqpToAmqpDispatcherHandlerBuilder< T >& __fastcall setState( state_type f ) override {
               state_ = f;
               return *this;
            }

            virtual IAmqpToAmqpDispatcherHandlerBuilder< T >& __fastcall setMeta( meta_type f ) override {
               meta_ = f;
               return *this;
            }

            virtual boost::shared_ptr< state_base_type > getState() const override {
               return state_;
            }

            virtual boost::shared_ptr< meta_base_type > getMeta() const override {
               return meta_;
            }

            virtual IAmqpToAmqpDispatcherHandlerBuilder< T >& __fastcall setInputFactory( factory_type f ) override {
               input_factory_ = f;
               return *this;
            }

            virtual IAmqpToAmqpDispatcherHandlerBuilder< T >& __fastcall setInputSettings( settings_type f ) override {
               input_settings_ = f;
               return *this;
            }

            virtual IAmqpToAmqpDispatcherHandlerBuilder< T >& __fastcall setInputAcknowledge( input_acknowledge_type f ) override {
               input_acknowledge_ = f;
               return *this;
            }

            virtual IAmqpToAmqpDispatcherHandlerBuilder< T >& __fastcall setInputKey( key_type f ) override {
               input_key_ = f;
               return *this;
            }

            virtual boost::shared_ptr< factory_base_type > getInputFactory() const override {
               return input_factory_;
            }

            virtual boost::shared_ptr< input_acknowledge_base_type > getInputAcknowledge() const override {
               return input_acknowledge_;
            }

            virtual boost::shared_ptr< settings_base_type > getInputSettings() const override {
               return input_settings_;
            }

            virtual key_base_type getInputKey() const override {
               return input_key_;
            }

            virtual IAmqpToAmqpDispatcherHandlerBuilder< T >& __fastcall setOutputFactory( factory_type f ) override {
               output_factory_ = f;
               return *this;
            }

            virtual IAmqpToAmqpDispatcherHandlerBuilder< T >& __fastcall setOutputSettings( settings_type f ) override {
               output_settings_ = f;
               return *this;
            }

            virtual IAmqpToAmqpDispatcherHandlerBuilder< T >& __fastcall setOutputAcknowledge( output_acknowledge_type f ) override {
               output_acknowledge_ = f;
               return *this;
            }

            virtual IAmqpToAmqpDispatcherHandlerBuilder< T >& __fastcall setOutputKey( key_type f ) override {
               output_key_ = f;
               return *this;
            }

            virtual boost::shared_ptr< factory_base_type > getOutputFactory() const override {
               return output_factory_;
            }

            virtual boost::shared_ptr< output_acknowledge_base_type > getOutputAcknowledge() const override {
               return output_acknowledge_;
            }

            virtual boost::shared_ptr< settings_base_type > getOutputSettings() const override {
               return output_settings_;
            }

            virtual key_base_type getOutputKey() const override {
               return output_key_;
            }

            virtual boost::shared_ptr< IDispatcherHandler< T > > build() const override {
               BOOST_STATIC_ASSERT(boost::is_base_of<IDispatcherHandler< T >, U>::value);

               return Utility::make_shared_pool_enable< IDispatcherHandler< T >, U, boost::default_user_allocator_malloc_free >( *this );
            }

            virtual ~AmqpToAmqpDispatcherHandlerBuilder() = default;

         private:
            boost::shared_ptr< state_base_type > state_;
            boost::shared_ptr< meta_base_type > meta_;

            boost::shared_ptr< factory_base_type > input_factory_;
            boost::shared_ptr< input_acknowledge_base_type > input_acknowledge_;
            boost::shared_ptr< settings_base_type > input_settings_;
            key_base_type input_key_;

            boost::shared_ptr< factory_base_type > output_factory_;
            boost::shared_ptr< output_acknowledge_base_type > output_acknowledge_;
            boost::shared_ptr< settings_base_type > output_settings_;
            key_base_type output_key_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_AMQP_TO_AMQP_DISPATCHER_HANDLER_BUILDER_H_INCLUDED__
