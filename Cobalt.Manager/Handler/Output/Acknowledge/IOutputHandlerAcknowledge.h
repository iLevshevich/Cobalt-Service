#ifndef __MANAGER_I_OUTPUT_HANDLER_ACKNOWLEDGE_TYPE_H_INCLUDED__
#define __MANAGER_I_OUTPUT_HANDLER_ACKNOWLEDGE_TYPE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Output
      {
         template< Import::ImportType _Type >
         class IOutputHandlerAcknowledge {
         public:
            typedef std::string base_type;
            typedef typename Utility::Traits< boost::shared_ptr< Import::IPublish< _Type > > >::const_reference_t publisher_type;
            typedef typename Utility::Traits< std::function< std::vector< base_type >() > >::const_reference_t executor_1_type;
            typedef typename Utility::Traits< std::function< base_type() > >::const_reference_t executor_2_type;
            typedef typename Utility::Traits< base_type >::const_reference_t key_type;

            virtual void __stdcall publish( publisher_type publisher,
                                            executor_1_type executor,
                                            key_type routingKey ) = 0;

            virtual void __stdcall publish( publisher_type publisher,
                                            executor_2_type executor,
                                            key_type routingKey = base_type() ) = 0;

            virtual ~IOutputHandlerAcknowledge() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_OUTPUT_HANDLER_ACKNOWLEDGE_TYPE_H_INCLUDED__
