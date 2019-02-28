#ifndef __MANAGER_ENABLE_MAKE_H_INCLUDED__
#define __MANAGER_ENABLE_MAKE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      template< typename Base >
      class enable_make : public Base {
      public:
         template< typename... T >
         enable_make( T&&... t )
            : Base( std::forward< T >( t )... ) {
         }
      };
   }
}

#pragma pack( pop )

#endif //__MANAGER_ENABLE_MAKE_H_INCLUDED__
