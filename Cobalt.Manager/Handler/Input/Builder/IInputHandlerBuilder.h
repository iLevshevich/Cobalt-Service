#ifndef __MANAGER_I_INPUT_HANDLER_BUILDER_H_INCLUDED__
#define __MANAGER_I_INPUT_HANDLER_BUILDER_H_INCLUDED__

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
         class IInputHandlerBuilder;

         template< class T, class U >
         class IInputHandlerBuilder< T, U, Import::ImportType::Amqp > {
         public:
            typedef typename T base_type;
            typedef typename Utility::Traits< boost::shared_ptr< Monitor::IInputMonitorHandler< base_type > > >::const_reference_t monitor_type;
            typedef typename Utility::Traits< Monitor::IInputMonitorHandler< base_type > >::base_t monitor_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< State::IStateHandler > >::const_reference_t state_type;
            typedef typename Utility::Traits< State::IStateHandler >::base_t state_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Factory::IImportFactory< Import::ImportType::Amqp > > >::const_reference_t factory_type;
            typedef typename Utility::Traits< Factory::IImportFactory< Import::ImportType::Amqp > >::base_t factory_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Amqp > > >::const_reference_t settings_type;
            typedef typename Utility::Traits< Import::Utility::ISettings< Import::ImportType::Amqp > >::base_t settings_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Meta::IMetaHandler< base_type > > >::const_reference_t meta_type;
            typedef typename Utility::Traits< Meta::IMetaHandler< base_type > >::base_t meta_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< IInputHandlerAcknowledge< Import::ImportType::Amqp > > >::const_reference_t acknowledge_type;
            typedef typename Utility::Traits< IInputHandlerAcknowledge< Import::ImportType::Amqp > >::base_t acknowledge_base_type;

            typedef typename Utility::Traits< base_type >::const_reference_t key_type;
            typedef typename Utility::Traits< base_type >::base_t key_base_type;

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setMonitor( monitor_type f ) = 0;
            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setState( state_type f ) = 0;
            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setFactory( factory_type f ) = 0;
            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setSettings( settings_type f ) = 0;
            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setMeta( meta_type f ) = 0;
            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setAcknowledge( acknowledge_type f ) = 0;
            virtual IInputHandlerBuilder< T, U, Import::ImportType::Amqp >& __fastcall setKey( key_type f ) = 0;

            virtual boost::shared_ptr< monitor_base_type > getMonitor() const = 0;
            virtual boost::shared_ptr< state_base_type > getState() const = 0;
            virtual boost::shared_ptr< factory_base_type > getFactory() const = 0;
            virtual boost::shared_ptr< meta_base_type > getMeta() const = 0;
            virtual boost::shared_ptr< acknowledge_base_type > getAcknowledge() const = 0;
            virtual boost::shared_ptr< settings_base_type > getSettings() const = 0;
            virtual key_base_type getKey() const = 0;

            virtual boost::shared_ptr< IInputHandler< T > > build() const = 0;

            virtual ~IInputHandlerBuilder() = default;
         };

         template< class T, class U >
         class IInputHandlerBuilder< T, U, Import::ImportType::Tcp > {
         public:
            typedef typename T base_type;
            typedef typename Utility::Traits< boost::shared_ptr< Monitor::IInputMonitorHandler< base_type > > >::const_reference_t monitor_type;
            typedef typename Utility::Traits< Monitor::IInputMonitorHandler< base_type > >::base_t monitor_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< State::IStateHandler > >::const_reference_t state_type;
            typedef typename Utility::Traits< State::IStateHandler >::base_t state_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Factory::IImportFactory< Import::ImportType::Tcp > > >::const_reference_t factory_type;
            typedef typename Utility::Traits< Factory::IImportFactory< Import::ImportType::Tcp > >::base_t factory_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Tcp > > >::const_reference_t settings_type;
            typedef typename Utility::Traits< Import::Utility::ISettings< Import::ImportType::Tcp > >::base_t settings_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Meta::IMetaHandler< base_type > > >::const_reference_t meta_type;
            typedef typename Utility::Traits< Meta::IMetaHandler< base_type > >::base_t meta_base_type;

            virtual IInputHandlerBuilder< T, U, Import::ImportType::Tcp >& __fastcall setMonitor(monitor_type f) = 0;
            virtual IInputHandlerBuilder< T, U, Import::ImportType::Tcp >& __fastcall setState(state_type f) = 0;
            virtual IInputHandlerBuilder< T, U, Import::ImportType::Tcp >& __fastcall setFactory(factory_type f) = 0;
            virtual IInputHandlerBuilder< T, U, Import::ImportType::Tcp >& __fastcall setSettings(settings_type f) = 0;
            virtual IInputHandlerBuilder< T, U, Import::ImportType::Tcp >& __fastcall setMeta(meta_type f) = 0;

            virtual boost::shared_ptr< monitor_base_type > getMonitor() const = 0;
            virtual boost::shared_ptr< state_base_type > getState() const = 0;
            virtual boost::shared_ptr< factory_base_type > getFactory() const = 0;
            virtual boost::shared_ptr< meta_base_type > getMeta() const = 0;
            virtual boost::shared_ptr< settings_base_type > getSettings() const = 0;

            virtual boost::shared_ptr< IInputHandler< T > > build() const = 0;

            virtual ~IInputHandlerBuilder() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_INPUT_HANDLER_BUILDER_H_INCLUDED__
