#ifndef __MANAGER_I_LAST_ERROR_HANDLER_H_INCLUDED__
#define __MANAGER_I_LAST_ERROR_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Error
      {
         template< class T >
         class ILastErrorHandler {
         public:
            typedef typename Utility::Traits< T >::base_t base_type;
            typedef typename Utility::Traits< base_type >::const_reference_t message_type;
            typedef typename Utility::Traits< boost::shared_ptr< boost::property_tree::ptree > >::base_t property_tree_base_type;

            virtual void __stdcall setLastError( message_type message ) = 0;
            virtual property_tree_base_type getLastError() = 0;
            virtual void cleanLastError() = 0;

            virtual typename std::enable_if< std::is_same< std::string, base_type >::value, bool >::type isLastErrorEmpty() = 0;

            virtual ~ILastErrorHandler() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_LAST_ERROR_HANDLER_H_INCLUDED__
