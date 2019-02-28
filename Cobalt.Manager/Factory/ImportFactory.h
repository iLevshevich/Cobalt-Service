#ifndef __MANAGER_IMPORT_FACTORY_H_INCLUDED__
#define __MANAGER_IMPORT_FACTORY_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Factory
   {
      template< Import::ImportType _Type >
      class ImportFactory;

      template<>
      class ImportFactory< Import::ImportType::Amqp > :
         public IImportFactory< Import::ImportType::Amqp > {
      public:
         typedef boost::shared_ptr< Import::Utility::ISettingsBuilder< Import::ImportType::Amqp > > (settings_builder_type)();
         typedef boost::shared_ptr< Import::IConsume< Import::ImportType::Amqp > > (consume_type)( const boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Amqp > >& settings );
         typedef boost::shared_ptr< Import::IPublish< Import::ImportType::Amqp > > (publish_type)( const boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Amqp > >& settings );

         static boost::shared_ptr< IImportFactory< Import::ImportType::Amqp > > getInstance( const boost::filesystem::path& lib ) {
            return Utility::make_shared_pool_enable< IImportFactory< Import::ImportType::Amqp >, ImportFactory< Import::ImportType::Amqp >, boost::default_user_allocator_malloc_free >( lib );
         }

         virtual boost::shared_ptr< Import::Utility::ISettingsBuilder< Import::ImportType::Amqp > > getSettingsBuilder() override {
            return builder_alias_();
         }

         virtual boost::shared_ptr< Import::IConsume< Import::ImportType::Amqp > > getConsumer( const boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Amqp > >& settings ) override {
            return consumer_alias_( settings );
         }

         virtual boost::shared_ptr< Import::IPublish< Import::ImportType::Amqp > > getPublisher( const boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Amqp > >& settings ) override {
            return publisher_alias_( settings );
         }

         virtual ~ImportFactory() = default;

      protected:
         const std::string BUILDER_ALIAS = "settings_builder_instance";
         const std::string PUBLISHER_ALIAS = "publish_instance";
         const std::string CONSUMER_ALIAS = "consume_instance";

         explicit ImportFactory( const boost::filesystem::path& lib ) :
            builder_alias_( boost::dll::import_alias< settings_builder_type >( lib, BUILDER_ALIAS, boost::dll::load_mode::append_decorations ) ),
            publisher_alias_( boost::dll::import_alias< publish_type >( lib, PUBLISHER_ALIAS, boost::dll::load_mode::append_decorations ) ),
            consumer_alias_( boost::dll::import_alias< consume_type >( lib, CONSUMER_ALIAS, boost::dll::load_mode::append_decorations ) ) {
         }

      private:
         boost::function< settings_builder_type > builder_alias_;
         boost::function< publish_type > publisher_alias_;
         boost::function< consume_type > consumer_alias_;
      };

      template<>
      class ImportFactory< Import::ImportType::Tcp > :
         public IImportFactory< Import::ImportType::Tcp > {
      public:
         typedef boost::shared_ptr< Import::Utility::ISettingsBuilder< Import::ImportType::Tcp > >(settings_builder_type)();
         typedef boost::shared_ptr< Import::IConsume< Import::ImportType::Tcp > >(consume_type)(const boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Tcp > >& settings);
         typedef boost::shared_ptr< Import::IPublish< Import::ImportType::Tcp > >(publish_type)(const boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Tcp > >& settings);

         static boost::shared_ptr< IImportFactory< Import::ImportType::Tcp > > getInstance(const boost::filesystem::path& lib) {
            return Utility::make_shared_pool_enable< IImportFactory< Import::ImportType::Tcp >, ImportFactory< Import::ImportType::Tcp >, boost::default_user_allocator_malloc_free >(lib);
         }

         virtual boost::shared_ptr< Import::Utility::ISettingsBuilder< Import::ImportType::Tcp > > getSettingsBuilder() override {
            return builder_alias_();
         }

         virtual boost::shared_ptr< Import::IConsume< Import::ImportType::Tcp > > getConsumer(const boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Tcp > >& settings) override {
            return consumer_alias_(settings);
         }

         virtual boost::shared_ptr< Import::IPublish< Import::ImportType::Tcp > > getPublisher(const boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Tcp > >& settings) override {
            return publisher_alias_(settings);
         }

         virtual ~ImportFactory() = default;

      protected:
         const std::string BUILDER_ALIAS = "settings_builder_instance";
         const std::string PUBLISHER_ALIAS = "publish_instance";
         const std::string CONSUMER_ALIAS = "consume_instance";

         explicit ImportFactory(const boost::filesystem::path& lib) :
            builder_alias_(boost::dll::import_alias< settings_builder_type >(lib, BUILDER_ALIAS, boost::dll::load_mode::append_decorations)),
            publisher_alias_(boost::dll::import_alias< publish_type >(lib, PUBLISHER_ALIAS, boost::dll::load_mode::append_decorations)),
            consumer_alias_(boost::dll::import_alias< consume_type >(lib, CONSUMER_ALIAS, boost::dll::load_mode::append_decorations)) {
         }

      private:
         boost::function< settings_builder_type > builder_alias_;
         boost::function< publish_type > publisher_alias_;
         boost::function< consume_type > consumer_alias_;
      };
   }
}

#pragma pack( pop )

#endif //__MANAGER_IMPORT_FACTORY_H_INCLUDED__
