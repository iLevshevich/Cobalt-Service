#ifndef __MANAGER_I_REPOSITORY_HANDLER_H_INCLUDED__
#define __MANAGER_I_REPOSITORY_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Repository
      {
         template< class T >
         class IRepositoryHandler {
         public:
            typedef T base_type;
            typedef typename Utility::Traits< boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > >::const_reference_t handler_type;
            typedef typename Utility::Traits< base_type >::const_reference_t id_type;
            typedef typename Utility::Traits< boost::shared_ptr< boost::property_tree::ptree > >::base_t property_tree_base_type;

            virtual property_tree_base_type getStatuses() = 0;
            virtual property_tree_base_type getProperties() = 0;

            virtual void cleanLastError() = 0;
            virtual void __stdcall cleanLastError( id_type t ) = 0;

            virtual void start() = 0;
            virtual void stop() = 0;
            virtual void abort() = 0;
            virtual void reset() = 0;

            virtual void __stdcall start( id_type t ) = 0;
            virtual void __stdcall stop( id_type t ) = 0;
            virtual void __stdcall abort( id_type t ) = 0;
            virtual void __stdcall reset( id_type t ) = 0;

            virtual void __stdcall add( handler_type t ) = 0;
            virtual void __stdcall remove( id_type t ) = 0;

            virtual ~IRepositoryHandler() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_REPOSITORY_HANDLER_H_INCLUDED__
