#ifndef __MANAGER_INPUT_HANDLER_ACKNOWLEDGE_TYPE_H_INCLUDED__
#define __MANAGER_INPUT_HANDLER_ACKNOWLEDGE_TYPE_H_INCLUDED__

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
         class InputHandlerAcknowledge :
            public IInputHandlerAcknowledge< _Type > {
         public:
            typedef typename IInputHandlerAcknowledge< _Type >::base_type base_type;
            typedef typename IInputHandlerAcknowledge< _Type >::consumer_type consumer_type;
            typedef typename IInputHandlerAcknowledge< _Type >::executor_type executor_type;
            typedef typename IInputHandlerAcknowledge< _Type >::key_type key_type;

            virtual void __stdcall consume( consumer_type consumer,
                                            executor_type executor,
                                            key_type routingKey = base_type() ) override {
               consumer->consumeAck( executor, routingKey );
            }

            virtual ~InputHandlerAcknowledge() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_INPUT_HANDLER_ACKNOWLEDGE_TYPE_H_INCLUDED__
