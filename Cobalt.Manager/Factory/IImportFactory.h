#ifndef __MANAGER_I_IMPORT_FACTORY_H_INCLUDED__
#define __MANAGER_I_IMPORT_FACTORY_H_INCLUDED__

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
      class IImportFactory;

      template<>
      class IImportFactory< Import::ImportType::Amqp > {
      public:
         virtual boost::shared_ptr< Import::Utility::ISettingsBuilder< Import::ImportType::Amqp > > getSettingsBuilder() = 0;
         virtual boost::shared_ptr< Import::IConsume< Import::ImportType::Amqp > > getConsumer( const boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Amqp > >& settings ) = 0;
         virtual boost::shared_ptr< Import::IPublish< Import::ImportType::Amqp > > getPublisher( const boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Amqp > >& settings ) = 0;

         virtual ~IImportFactory() = default;
      };

      template<>
      class IImportFactory< Import::ImportType::Tcp > {
      public:
         virtual boost::shared_ptr< Import::Utility::ISettingsBuilder< Import::ImportType::Tcp > > getSettingsBuilder() = 0;
         virtual boost::shared_ptr< Import::IConsume< Import::ImportType::Tcp > > getConsumer(const boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Tcp > >& settings) = 0;
         virtual boost::shared_ptr< Import::IPublish< Import::ImportType::Tcp > > getPublisher(const boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Tcp > >& settings) = 0;

         virtual ~IImportFactory() = default;
      };
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_IMPORT_FACTORY_H_INCLUDED__
