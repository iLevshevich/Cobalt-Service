#ifndef __MANAGER_I_INPUT_MONITOR_HANDLER_BUILDER_H_INCLUDED__
#define __MANAGER_I_INPUT_MONITOR_HANDLER_BUILDER_H_INCLUDED__

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
         class IInputMonitorHandlerBuilder;

         template< class T >
         class IInputMonitorHandlerBuilder {
         public:
            typedef typename T base_type;
            typedef typename Utility::Traits< base_type >::const_reference_t function_arg_type;

            typedef typename Utility::Traits< std::function< void( function_arg_type ) > >::base_t function_1_type;
            typedef typename Utility::Traits< std::function< void( function_arg_type ) > >::const_reference_t lambda_1_type;

            typedef typename Utility::Traits< std::function< void( function_arg_type, function_arg_type ) > >::base_t function_2_type;
            typedef typename Utility::Traits< std::function< void( function_arg_type, function_arg_type ) > >::const_reference_t lambda_2_type;

            virtual IInputMonitorHandlerBuilder< T >& __fastcall setOnStart( lambda_1_type f ) = 0;
            virtual IInputMonitorHandlerBuilder< T >& __fastcall setOnStop( lambda_1_type f ) = 0;
            virtual IInputMonitorHandlerBuilder< T >& __fastcall setOnError( lambda_2_type f ) = 0;
            virtual IInputMonitorHandlerBuilder< T >& __fastcall setOnBeforePush( lambda_2_type f ) = 0;
            virtual IInputMonitorHandlerBuilder< T >& __fastcall setOnPush( lambda_2_type f ) = 0;
            virtual IInputMonitorHandlerBuilder< T >& __fastcall setOnAfterPush( lambda_2_type f ) = 0;

            virtual boost::shared_ptr< function_1_type > getOnStart() const = 0;
            virtual boost::shared_ptr< function_1_type > getOnStop() const = 0;
            virtual boost::shared_ptr< function_2_type > getOnError() const = 0;
            virtual boost::shared_ptr< function_2_type > getOnBeforePush() const = 0;
            virtual boost::shared_ptr< function_2_type > getOnPush() const = 0;
            virtual boost::shared_ptr< function_2_type > getOnAfterPush() const = 0;

            virtual boost::shared_ptr< IInputMonitorHandler< T > > build() const = 0;

            virtual ~IInputMonitorHandlerBuilder() = default;
         };

         template<>
         class IInputMonitorHandlerBuilder< void > {
         public:
            typedef void base_type;
            typedef typename Utility::Traits< std::function< void() > >::base_t function_1_type;
            typedef typename Utility::Traits< std::function< void() > >::const_reference_t lambda_1_type;

            typedef typename Utility::Traits< std::function< void() > >::base_t function_2_type;
            typedef typename Utility::Traits< std::function< void() > >::const_reference_t lambda_2_type;

            virtual IInputMonitorHandlerBuilder< void >& __fastcall setOnStart( lambda_1_type f ) = 0;
            virtual IInputMonitorHandlerBuilder< void >& __fastcall setOnStop( lambda_1_type f ) = 0;
            virtual IInputMonitorHandlerBuilder< void >& __fastcall setOnError( lambda_2_type f ) = 0;
            virtual IInputMonitorHandlerBuilder< void >& __fastcall setOnBeforePush( lambda_2_type f ) = 0;
            virtual IInputMonitorHandlerBuilder< void >& __fastcall setOnPush( lambda_2_type f ) = 0;
            virtual IInputMonitorHandlerBuilder< void >& __fastcall setOnAfterPush( lambda_2_type f ) = 0;

            virtual boost::shared_ptr< function_1_type > getOnStart() const = 0;
            virtual boost::shared_ptr< function_1_type > getOnStop() const = 0;
            virtual boost::shared_ptr< function_2_type > getOnError() const = 0;
            virtual boost::shared_ptr< function_2_type > getOnBeforePush() const = 0;
            virtual boost::shared_ptr< function_2_type > getOnPush() const = 0;
            virtual boost::shared_ptr< function_2_type > getOnAfterPush() const = 0;

            virtual boost::shared_ptr< IInputMonitorHandler< void > > build() const = 0;

            virtual ~IInputMonitorHandlerBuilder() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_INPUT_MONITOR_HANDLER_BUILDER_H_INCLUDED__
