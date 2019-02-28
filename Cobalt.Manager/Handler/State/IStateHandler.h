#ifndef __MANAGER_I_STATE_HANDLER_H_INCLUDED__
#define __MANAGER_I_STATE_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace State
      {
         class IStateHandler {
         public:
            typedef typename Utility::Traits< boost::shared_ptr< boost::property_tree::ptree > >::base_t property_tree_base_type;

            virtual property_tree_base_type getState() const = 0;

            virtual void start() = 0;
            virtual void stop() = 0;
            virtual void abort() = 0;

            virtual bool isRunning() const = 0;
            virtual bool isStopped() const = 0;
            virtual bool isAborted() const = 0;

            virtual ~IStateHandler() = default;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_STATE_HANDLER_H_INCLUDED__
