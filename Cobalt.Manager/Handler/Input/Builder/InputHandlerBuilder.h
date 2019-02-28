#ifndef __MANAGER_INPUT_HANDLER_BUILDER_H_INCLUDED__
#define __MANAGER_INPUT_HANDLER_BUILDER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Input
      {
         template< class T, class U, Import::ImportType _Type >
         class InputHandlerBuilder;

         template< class T, class U >
         class InputHandlerBuilder< T, U, Import::ImportType::Amqp >:
            public IInputHandlerBuilder< T, U, Import::ImportType::Amqp > {
         public:
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::monitor_type monitor_type;
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::monitor_base_type monitor_base_type;

            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::state_type state_type;
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::state_base_type state_base_type;

            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::factory_type factory_type;
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::factory_base_type factory_base_type;

            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::settings_type settings_type;
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::settings_base_type settings_base_type;

            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::meta_type meta_type;
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::meta_base_type meta_base_type;

            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::acknowledge_type acknowledge_type;
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::acknowledge_base_type acknowledge_base_type;

            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::key_type key_type;
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Amqp >::key_base_type key_base_type;

            InputHandlerBuilder():
               monitor_( nullptr ),
               state_( nullptr ),
               factory_( nullptr ),
               acknowledge_( nullptr ),
               meta_( nullptr ),
               settings_( nullptr ),
               key_( key_base_type() ) {
            }

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setMonitor( monitor_type f ) override {
               monitor_ = f;
               return *this;
            }

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setState( state_type f ) override {
               state_ = f;
               return *this;
            }

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setFactory( factory_type f ) override {
               factory_ = f;
               return *this;
            }

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setSettings( settings_type f ) override {
               settings_ = f;
               return *this;
            }

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setMeta( meta_type f ) override {
               meta_ = f;
               return *this;
            }

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setAcknowledge( acknowledge_type f ) override {
               acknowledge_ = f;
               return *this;
            }

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setKey( key_type f ) override {
               key_ = f;
               return *this;
            }

            virtual boost::shared_ptr< monitor_base_type > getMonitor() const override {
               return monitor_;
            }

            virtual boost::shared_ptr< state_base_type > getState() const override {
               return state_;
            }

            virtual boost::shared_ptr< factory_base_type > getFactory() const override {
               return factory_;
            }

            virtual boost::shared_ptr< settings_base_type > getSettings() const override {
               return settings_;
            }

            virtual boost::shared_ptr< meta_base_type > getMeta() const override {
               return meta_;
            }

            virtual boost::shared_ptr< acknowledge_base_type > getAcknowledge() const override {
               return acknowledge_;
            }

            virtual key_base_type getKey() const override {
               return key_;
            }

            virtual boost::shared_ptr< IInputHandler< T > > build() const override {
               BOOST_STATIC_ASSERT(boost::is_base_of<IInputHandler< T >, U>::value);

               return Utility::make_shared_pool_enable< IInputHandler< T >, U, boost::default_user_allocator_malloc_free >( *this );
            }

            virtual ~InputHandlerBuilder() = default;

         private:
            boost::shared_ptr< monitor_base_type > monitor_;
            boost::shared_ptr< state_base_type > state_;
            boost::shared_ptr< factory_base_type > factory_;
            boost::shared_ptr< acknowledge_base_type > acknowledge_;
            boost::shared_ptr< meta_base_type > meta_;
            boost::shared_ptr< settings_base_type > settings_;
            key_base_type key_;
         };

         template< class T, class U >
         class InputHandlerBuilder< T, U, Import::ImportType::Tcp > :
            public IInputHandlerBuilder< T, U, Import::ImportType::Tcp > {
         public:
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Tcp >::monitor_type monitor_type;
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Tcp >::monitor_base_type monitor_base_type;

            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Tcp >::state_type state_type;
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Tcp >::state_base_type state_base_type;

            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Tcp >::factory_type factory_type;
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Tcp >::factory_base_type factory_base_type;

            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Tcp >::settings_type settings_type;
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Tcp >::settings_base_type settings_base_type;

            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Tcp >::meta_type meta_type;
            typedef typename IInputHandlerBuilder< T, U, Import::ImportType::Tcp >::meta_base_type meta_base_type;

            InputHandlerBuilder() :
               monitor_(nullptr),
               state_(nullptr),
               factory_(nullptr),
               meta_(nullptr),
               settings_(nullptr) {
            }

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Tcp >& __fastcall setMonitor(monitor_type f) override {
               monitor_ = f;
               return *this;
            }

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Tcp >& __fastcall setState(state_type f) override {
               state_ = f;
               return *this;
            }

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Tcp >& __fastcall setFactory(factory_type f) override {
               factory_ = f;
               return *this;
            }

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Tcp >& __fastcall setSettings(settings_type f) override {
               settings_ = f;
               return *this;
            }

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Tcp >& __fastcall setMeta(meta_type f) override {
               meta_ = f;
               return *this;
            }

            virtual boost::shared_ptr< monitor_base_type > getMonitor() const override {
               return monitor_;
            }

            virtual boost::shared_ptr< state_base_type > getState() const override {
               return state_;
            }

            virtual boost::shared_ptr< factory_base_type > getFactory() const override {
               return factory_;
            }

            virtual boost::shared_ptr< settings_base_type > getSettings() const override {
               return settings_;
            }

            virtual boost::shared_ptr< meta_base_type > getMeta() const override {
               return meta_;
            }

            virtual boost::shared_ptr< IInputHandler< T > > build() const override {
               BOOST_STATIC_ASSERT(boost::is_base_of<IInputHandler< T >, U>::value);

               return Utility::make_shared_pool_enable< IInputHandler< T >, U, boost::default_user_allocator_malloc_free >(*this);
            }

            virtual ~InputHandlerBuilder() = default;

         private:
            boost::shared_ptr< monitor_base_type > monitor_;
            boost::shared_ptr< state_base_type > state_;
            boost::shared_ptr< factory_base_type > factory_;
            boost::shared_ptr< meta_base_type > meta_;
            boost::shared_ptr< settings_base_type > settings_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_INPUT_HANDLER_BUILDER_H_INCLUDED__
