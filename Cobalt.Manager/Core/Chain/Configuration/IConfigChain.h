#ifndef __MANAGER_I_CONFIG_CHAIN_H_INCLUDED__
#define __MANAGER_I_CONFIG_CHAIN_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Core
   {
      namespace Chain
      {
         class IConfigChain {
         public:
            typedef typename Utility::Traits< boost::property_tree::ptree::const_iterator >::const_reference_t config_type;
            typedef typename Utility::Traits< boost::shared_ptr< Handler::Dispatcher::IDispatcherHandler< std::string > > >::base_t return_type;

            virtual return_type __stdcall getDispatcher( config_type config ) = 0;

            virtual ~IConfigChain() = default;

         protected:
            template< Import::ImportType _En, typename std::enable_if< _En == Import::ImportType::Amqp >::type * = nullptr >
            boost::shared_ptr< Factory::IImportFactory< Import::ImportType::Amqp > > getFactory() const {
               return Factory::ImportFactory< Import::ImportType::Amqp >::getInstance(Utility::Memmory::Singleton< Utility::Options >::instance().get(Utility::Options::DLL_AMQP_PATH));
            }

            template< Import::ImportType _En, typename std::enable_if< _En == Import::ImportType::Tcp >::type * = nullptr >
            boost::shared_ptr< Factory::IImportFactory< Import::ImportType::Tcp > > getFactory() const {
               return Factory::ImportFactory< Import::ImportType::Tcp >::getInstance(Utility::Memmory::Singleton< Utility::Options >::instance().get(Utility::Options::DLL_TCP_PATH));
            }
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_CONFIG_CHAIN_H_INCLUDED__
