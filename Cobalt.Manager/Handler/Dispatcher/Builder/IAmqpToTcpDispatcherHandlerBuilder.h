﻿#ifndef __MANAGER_I_AMQP_TO_TCP_DISPATCHER_HANDLER_BUILDER_H_INCLUDED__
#define __MANAGER_I_AMQP_TO_TCP_DISPATCHER_HANDLER_BUILDER_H_INCLUDED__

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
         template< class T >
         class IAmqpToTcpDispatcherHandlerBuilder {
         public:
            typedef typename T base_type;
            typedef typename Utility::Traits< boost::shared_ptr< State::IStateHandler > >::const_reference_t state_type;
            typedef typename Utility::Traits< State::IStateHandler >::base_t state_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Meta::IMetaHandler< base_type > > >::const_reference_t meta_type;
            typedef typename Utility::Traits< Meta::IMetaHandler< base_type > >::base_t meta_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Factory::IImportFactory< Import::ImportType::Amqp > > >::const_reference_t input_factory_type;
            typedef typename Utility::Traits< Factory::IImportFactory< Import::ImportType::Amqp > >::base_t input_factory_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Factory::IImportFactory< Import::ImportType::Tcp > > >::const_reference_t output_factory_type;
            typedef typename Utility::Traits< Factory::IImportFactory< Import::ImportType::Tcp > >::base_t output_factory_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Amqp > > >::const_reference_t input_settings_type;
            typedef typename Utility::Traits< Import::Utility::ISettings< Import::ImportType::Amqp > >::base_t input_settings_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Import::Utility::ISettings< Import::ImportType::Tcp > > >::const_reference_t output_settings_type;
            typedef typename Utility::Traits< Import::Utility::ISettings< Import::ImportType::Tcp > >::base_t output_settings_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Input::IInputHandlerAcknowledge< Import::ImportType::Amqp > > >::const_reference_t input_acknowledge_type;
            typedef typename Utility::Traits< Input::IInputHandlerAcknowledge< Import::ImportType::Amqp > >::base_t input_acknowledge_base_type;

            typedef typename Utility::Traits< base_type >::const_reference_t key_type;
            typedef typename Utility::Traits< base_type >::base_t key_base_type;

            virtual IAmqpToTcpDispatcherHandlerBuilder< T >& __fastcall setState( state_type f ) = 0;
            virtual IAmqpToTcpDispatcherHandlerBuilder< T >& __fastcall setMeta( meta_type f ) = 0;
            virtual boost::shared_ptr< state_base_type > getState() const = 0;
            virtual boost::shared_ptr< meta_base_type > getMeta() const = 0;

            virtual IAmqpToTcpDispatcherHandlerBuilder< T >& __fastcall setInputFactory( input_factory_type f ) = 0;
            virtual IAmqpToTcpDispatcherHandlerBuilder< T >& __fastcall setInputSettings( input_settings_type f ) = 0;
            virtual IAmqpToTcpDispatcherHandlerBuilder< T >& __fastcall setInputAcknowledge( input_acknowledge_type f ) = 0;
            virtual IAmqpToTcpDispatcherHandlerBuilder< T >& __fastcall setInputKey( key_type f ) = 0;
            virtual boost::shared_ptr< input_factory_base_type > getInputFactory() const = 0;
            virtual boost::shared_ptr< input_acknowledge_base_type > getInputAcknowledge() const = 0;
            virtual boost::shared_ptr< input_settings_base_type > getInputSettings() const = 0;
            virtual key_base_type getInputKey() const = 0;

            virtual IAmqpToTcpDispatcherHandlerBuilder< T >& __fastcall setOutputFactory( output_factory_type f ) = 0;
            virtual IAmqpToTcpDispatcherHandlerBuilder< T >& __fastcall setOutputSettings( output_settings_type f ) = 0;
            virtual boost::shared_ptr< output_factory_base_type > getOutputFactory() const = 0;
            virtual boost::shared_ptr< output_settings_base_type > getOutputSettings() const = 0;

            virtual boost::shared_ptr< IDispatcherHandler< T > > build() const = 0;

            virtual ~IAmqpToTcpDispatcherHandlerBuilder() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_AMQP_TO_TCP_DISPATCHER_HANDLER_BUILDER_H_INCLUDED__
