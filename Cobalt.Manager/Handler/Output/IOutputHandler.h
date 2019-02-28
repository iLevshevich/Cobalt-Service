#ifndef __MANAGER_I_OUTPUT_HANDLER_H_INCLUDED__
#define __MANAGER_I_OUTPUT_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Output
      {
         template< class T >
         class IOutputHandler :
            public State::IStateHandler,
            public Meta::IMetaHandler< T > {
         public:
            typedef typename Utility::Traits< T >::const_rvalue_reference_t handler_arg_1_type;
            typedef typename Utility::Traits< std::vector< T > >::const_reference_t handler_arg_2_type;

            virtual void __fastcall produce( handler_arg_1_type ) = 0;
            virtual void __fastcall produce( handler_arg_2_type ) = 0;

            virtual void wait() const = 0;

            virtual ~IOutputHandler() = default;

         protected:
            virtual handler_arg_1_type __fastcall publish( handler_arg_1_type ) = 0;
            virtual handler_arg_2_type __fastcall publish( handler_arg_2_type ) = 0;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_I_OUTPUT_HANDLER_H_INCLUDED__
