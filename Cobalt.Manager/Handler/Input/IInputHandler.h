#ifndef __MANAGER_I_INPUT_HANDLER_H_INCLUDED__
#define __MANAGER_I_INPUT_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Input
      {
         template< class T >
         class IInputHandler :
            public State::IStateHandler,
            public Meta::IMetaHandler< T > {
         public:
            typedef typename Utility::Traits< T >::const_rvalue_reference_t handler_arg_type;

            virtual ~IInputHandler() = default;

         protected:
            virtual void __fastcall consume( handler_arg_type ) = 0;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_INPUT_HANDLER_H_INCLUDED__
