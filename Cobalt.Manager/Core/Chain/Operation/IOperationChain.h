#ifndef __MANAGER_I_OPERATION_CHAIN_H_INCLUDED__
#define __MANAGER_I_OPERATION_CHAIN_H_INCLUDED__

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
         class IOperationChain {
         public:
            typedef typename Utility::Traits< boost::property_tree::ptree >::const_reference_t request_type;
            typedef typename Utility::Traits< std::tuple< bool, std::string > >::base_t responce_type;

            virtual responce_type __stdcall execute( request_type request ) = 0;

            virtual ~IOperationChain() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_OPERATION_CHAIN_H_INCLUDED__
