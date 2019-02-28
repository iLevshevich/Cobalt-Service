#ifndef __MANAGER_I_DISPATCHER_HANDLER_H_INCLUDED__
#define __MANAGER_I_DISPATCHER_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Dispatcher
      {
         template< class T >
         class IDispatcherHandler:
            public State::IStateHandler,
            public State::IResetHandler,
            public Meta::IMetaHandler< T > {
         public:
            typedef T base_type;
            typedef typename State::IStateHandler::property_tree_base_type property_tree_base_type;

            virtual property_tree_base_type getStatus() = 0;
            virtual property_tree_base_type getProperty() = 0;

            virtual Type::DispatcherHandlerType getType() const = 0;
            virtual Priority::DispatcherHandlerPriority getPriority() const = 0;

            virtual void cleanLastError() = 0;
            virtual bool isLastErrorEmpty() = 0;

            virtual ~IDispatcherHandler() = default;

         protected:
            virtual property_tree_base_type getQueueSize() = 0;
            virtual property_tree_base_type getLastPerform() = 0;
            virtual property_tree_base_type getLastError() = 0;
            virtual property_tree_base_type getInputProperty() const = 0;
            virtual property_tree_base_type getOutputProperty() const = 0;
            virtual property_tree_base_type getInputState() const = 0;
            virtual property_tree_base_type getQueueState() const = 0;
            virtual property_tree_base_type getOutputState() const = 0;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_DISPATCHER_HANDLER_H_INCLUDED__
