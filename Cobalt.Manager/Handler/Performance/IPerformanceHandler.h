#ifndef __MANAGER_I_PERFORMANCE_HANDLER_H_INCLUDED__
#define __MANAGER_I_PERFORMANCE_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Performance
      {
         class IPerformanceHandler {
         public:
			typedef typename Utility::Traits< std::string >::const_reference_t hash_arg_type;
            typedef typename Utility::Traits< boost::shared_ptr< boost::property_tree::ptree > >::base_t property_tree_base_type;

            virtual void __fastcall begin(hash_arg_type s) = 0;
            virtual void __fastcall end(hash_arg_type s) = 0;
            virtual property_tree_base_type getLastPerform() = 0;
            virtual void __fastcall cleanLastPerform(hash_arg_type s) = 0;

            virtual ~IPerformanceHandler() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_PERFORMANCE_HANDLER_H_INCLUDED__
