#ifndef __MANAGER_I_INPUT_HANDLER_ACKNOWLEDGE_TYPE_H_INCLUDED__
#define __MANAGER_I_INPUT_HANDLER_ACKNOWLEDGE_TYPE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Input
      {
         template< Import::ImportType _Type >
         class IInputHandlerAcknowledge {
         public:
            typedef std::string base_type;
            typedef typename Utility::Traits< boost::shared_ptr< Import::IConsume< _Type > > >::const_reference_t consumer_type;
            typedef typename Utility::Traits< std::function< void( typename Utility::Traits< base_type >::const_rvalue_reference_t ) > >::const_reference_t executor_type;
            typedef typename Utility::Traits< base_type >::const_reference_t key_type;

            virtual void __stdcall consume( consumer_type consumer,
                                            executor_type executor,
                                            key_type = base_type() ) = 0;

            virtual ~IInputHandlerAcknowledge() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_INPUT_HANDLER_ACKNOWLEDGE_TYPE_H_INCLUDED__
