#ifndef __MANAGER_META_HANDLER_H_INCLUDED__
#define __MANAGER_META_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Meta
      {
         class MetaHandler:
            public IMetaHandler< std::string > {
         public:
            typedef typename IMetaHandler< std::string >::base_type base_type;
            typedef typename Utility::Traits< base_type >::const_reference_t const_reference_type;

            explicit MetaHandler( const_reference_type id,
                                  const_reference_type description = base_type() ):
               id_( id ),
               description_( description ) {
            }

            virtual base_type getId() override {
               return id_;
            }

            virtual base_type getDescription() override {
               return description_;
            }

            virtual ~MetaHandler() = default;

         private:
            base_type id_;
            base_type description_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_META_HANDLER_H_INCLUDED__
