#ifndef __MANAGER_OUTPUT_HANDLER_ACKNOWLEDGE_TYPE_H_INCLUDED__
#define __MANAGER_OUTPUT_HANDLER_ACKNOWLEDGE_TYPE_H_INCLUDED__

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
         class OutputHandlerAcknowledge:
            public IOutputHandlerAcknowledge< _Type > {
         public:
            typedef typename IOutputHandlerAcknowledge< _Type >::base_type base_type;
            typedef typename IOutputHandlerAcknowledge< _Type >::publisher_type publisher_type;
            typedef typename IOutputHandlerAcknowledge< _Type >::executor_1_type executor_1_type;
            typedef typename IOutputHandlerAcknowledge< _Type >::executor_2_type executor_2_type;
            typedef typename IOutputHandlerAcknowledge< _Type >::key_type key_type;

            virtual void __stdcall publish( publisher_type publisher,
                                            executor_1_type executor,
                                            key_type routingKey ) override {
               publisher->publishAck( executor, routingKey );
            }

            virtual void __stdcall publish( publisher_type publisher,
                                            executor_2_type executor,
                                            key_type routingKey = base_type() ) override {
               publisher->publishAck( executor, routingKey );
            }

            virtual ~OutputHandlerAcknowledge() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_OUTPUT_HANDLER_ACKNOWLEDGE_TYPE_H_INCLUDED__
