#ifndef __MANAGER_PROPERTY_HANDLER_H_INCLUDED__
#define __MANAGER_PROPERTY_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Property
      {
         template< class _Type >
         class PropertyHandler;

         template<>
         class PropertyHandler< Import::Utility::ISettings< Import::ImportType::Amqp > > :
            public IPropertyHandler {
         public:
            typedef typename IPropertyHandler::property_base_type property_base_type;
            typedef typename Utility::Traits< boost::shared_ptr< boost::property_tree::ptree > >::const_reference_t property_type;
            typedef typename Utility::Traits< boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Amqp > > >::const_reference_t settings_type;
            typedef typename Utility::Traits< std::string >::const_reference_t key_type;
            typedef typename Utility::Traits< std::string >::const_reference_t prefetch_type;

            template< PropertyHandlerType _En, typename std::enable_if< _En == PropertyHandlerType::input >::type * = nullptr >
            static boost::shared_ptr< IPropertyHandler > __stdcall getInstance( settings_type settings, key_type routing_key, prefetch_type prefetch = "1000" ) {
               return Utility::make_shared_pool_enable< IPropertyHandler, PropertyHandler< Import::Utility::ISettings< Import::ImportType::Amqp > >, boost::default_user_allocator_malloc_free >( toProperty< PropertyHandlerType::input >( settings, routing_key, prefetch ) );
            }

            template< PropertyHandlerType _En, typename std::enable_if< _En == PropertyHandlerType::output >::type * = nullptr >
            static boost::shared_ptr< IPropertyHandler > __stdcall getInstance( settings_type settings, key_type routing_key, prefetch_type prefetch = "1000" ) {
               return Utility::make_shared_pool_enable< IPropertyHandler, PropertyHandler< Import::Utility::ISettings< Import::ImportType::Amqp > >, boost::default_user_allocator_malloc_free >( toProperty< PropertyHandlerType::output >( settings, routing_key, prefetch ) );
            }

            virtual property_base_type getProperty() const override {
               return property_;
            }

            virtual ~PropertyHandler() = default;

         protected:
            explicit PropertyHandler( property_type property ) :
               property_( property ) {
            }

            template< PropertyHandlerType _En, typename std::enable_if< _En == PropertyHandlerType::input >::type * = nullptr >
            static property_base_type __stdcall toProperty( settings_type settings, key_type routing_key, prefetch_type prefetch ) {
               boost::property_tree::ptree result;
               ///
               result.put( "input.host", settings->getHost()->getHost() );
               result.put( "input.port", settings->getHost()->getPort() );
               result.put( "input.user", settings->getLogin()->getUser() );
               result.put( "input.password", settings->getLogin()->getPassword() );
               result.put( "input.vhost", settings->getConnection()->getVirtualHost() );
               result.put( "input.prefetch", prefetch );
               result.put( "input.exchange", settings->getExchange()->getName() );
               result.put( "input.queue", settings->getQueue()->getName() );
               result.put( "input.routing_key", routing_key );
               ///
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

            template< PropertyHandlerType _En, typename std::enable_if< _En == PropertyHandlerType::output >::type * = nullptr >
            static property_base_type __stdcall toProperty( settings_type settings, key_type routing_key, prefetch_type prefetch ) {
               boost::property_tree::ptree result;
               ///
               result.put( "output.host", settings->getHost()->getHost() );
               result.put( "output.port", settings->getHost()->getPort() );
               result.put( "output.user", settings->getLogin()->getUser() );
               result.put( "output.password", settings->getLogin()->getPassword() );
               result.put( "output.vhost", settings->getConnection()->getVirtualHost() );
               result.put( "output.prefetch", prefetch );
               result.put( "output.exchange", settings->getExchange()->getName() );
               result.put( "output.queue", settings->getQueue()->getName() );
               result.put( "output.routing_key", routing_key );
               ///
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

         private:
            property_base_type property_;
         };

         template<>
         class PropertyHandler< Import::Utility::ISettings< Import::ImportType::Tcp > > :
            public IPropertyHandler {
         public:
            typedef typename IPropertyHandler::property_base_type property_base_type;
            typedef typename Utility::Traits< boost::shared_ptr< boost::property_tree::ptree > >::const_reference_t property_type;
            typedef typename Utility::Traits< boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Tcp > > >::const_reference_t settings_type;

            template< PropertyHandlerType _En, typename std::enable_if< _En == PropertyHandlerType::input >::type * = nullptr >
            static boost::shared_ptr< IPropertyHandler > __stdcall getInstance( settings_type settings ) {
               return Utility::make_shared_pool_enable< IPropertyHandler, PropertyHandler< Import::Utility::ISettings< Import::ImportType::Tcp > >, boost::default_user_allocator_malloc_free >( toProperty< PropertyHandlerType::input >( settings ) );
            }

            template< PropertyHandlerType _En, typename std::enable_if< _En == PropertyHandlerType::output >::type * = nullptr >
            static boost::shared_ptr< IPropertyHandler > __stdcall getInstance( settings_type settings ) {
               return Utility::make_shared_pool_enable< IPropertyHandler, PropertyHandler< Import::Utility::ISettings< Import::ImportType::Tcp > >, boost::default_user_allocator_malloc_free >( toProperty< PropertyHandlerType::output >( settings ) );
            }

            virtual property_base_type getProperty() const override {
               return property_;
            }

            virtual ~PropertyHandler() = default;

         protected:
            explicit PropertyHandler( property_type property ) :
               property_( property ) {
            }

            template< PropertyHandlerType _En, typename std::enable_if< _En == PropertyHandlerType::input >::type * = nullptr >
            static property_base_type __stdcall toProperty( settings_type settings ) {
               boost::property_tree::ptree result;
               ///
               result.put( "input.host", settings->getHost() );
               result.put( "input.port", settings->getPort() );
               ///
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

            template< PropertyHandlerType _En, typename std::enable_if< _En == PropertyHandlerType::output >::type * = nullptr >
            static property_base_type __stdcall toProperty( settings_type settings ) {
               boost::property_tree::ptree result;
               ///
               result.put( "output.host", settings->getHost() );
               result.put( "output.port", settings->getPort() );
               ///
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

         private:
            property_base_type property_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_PROPERTY_HANDLER_H_INCLUDED__
