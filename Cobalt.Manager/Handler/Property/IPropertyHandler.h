#ifndef __MANAGER_I_PROPERTY_HANDLER_H_INCLUDED__
#define __MANAGER_I_PROPERTY_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Property
      {
         class IPropertyHandler {
         public:
            typedef typename Utility::Traits< boost::shared_ptr< boost::property_tree::ptree > >::base_t property_base_type;

            virtual property_base_type getProperty() const = 0;

            virtual ~IPropertyHandler() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_PROPERTY_HANDLER_H_INCLUDED__
