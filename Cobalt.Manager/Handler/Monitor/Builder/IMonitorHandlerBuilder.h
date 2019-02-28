#ifndef __MANAGER_I_MONITOR_HANDLER_BUILDER_H_INCLUDED__
#define __MANAGER_I_MONITOR_HANDLER_BUILDER_H_INCLUDED__

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
         class IMonitorHandlerBuilder;

         template< class T >
         class IMonitorHandlerBuilder {
         public:
            typedef typename T base_type;
            typedef typename Utility::Traits< base_type >::const_reference_t function_arg_type;

            typedef typename Utility::Traits< std::function< void(function_arg_type) > >::base_t function_1_type;
            typedef typename Utility::Traits< std::function< void(function_arg_type) > >::const_reference_t lambda_1_type;

            typedef typename Utility::Traits< std::function< void(function_arg_type, function_arg_type) > >::base_t function_2_type;
            typedef typename Utility::Traits< std::function< void(function_arg_type, function_arg_type) > >::const_reference_t lambda_2_type;

            virtual IMonitorHandlerBuilder< T >& __fastcall setOnStart(lambda_1_type f) = 0;
            virtual IMonitorHandlerBuilder< T >& __fastcall setOnStop(lambda_1_type f) = 0;
            virtual IMonitorHandlerBuilder< T >& __fastcall setOnError(lambda_2_type f) = 0;

            virtual boost::shared_ptr< function_1_type > getOnStart() const = 0;
            virtual boost::shared_ptr< function_1_type > getOnStop() const = 0;
            virtual boost::shared_ptr< function_2_type > getOnError() const = 0;

            virtual boost::shared_ptr< IMonitorHandler< T > > build() const = 0;

            virtual ~IMonitorHandlerBuilder() = default;
         };

         template<>
         class IMonitorHandlerBuilder< void > {
         public:
            typedef void base_type;
            typedef typename Utility::Traits< std::function< void() > >::base_t function_1_type;
            typedef typename Utility::Traits< std::function< void() > >::const_reference_t lambda_1_type;

            typedef typename Utility::Traits< std::function< void() > >::base_t function_2_type;
            typedef typename Utility::Traits< std::function< void() > >::const_reference_t lambda_2_type;

            virtual IMonitorHandlerBuilder< void >& __fastcall setOnStart(lambda_1_type f) = 0;
            virtual IMonitorHandlerBuilder< void >& __fastcall setOnStop(lambda_1_type f) = 0;
            virtual IMonitorHandlerBuilder< void >& __fastcall setOnError(lambda_2_type f) = 0;

            virtual boost::shared_ptr< function_1_type > getOnStart() const = 0;
            virtual boost::shared_ptr< function_1_type > getOnStop() const = 0;
            virtual boost::shared_ptr< function_2_type > getOnError() const = 0;

            virtual boost::shared_ptr< IMonitorHandler< void > > build() const = 0;

            virtual ~IMonitorHandlerBuilder() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_MONITOR_HANDLER_BUILDER_H_INCLUDED__
