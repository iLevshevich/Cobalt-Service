#ifndef __MANAGER_MIN_H_INCLUDED__
#define __MANAGER_MIN_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      template< class T, class U >
      T min( const T& a, const U& b ) {
         return std::min( a, b );
      }

      template< class T, class U, class ... R >
      T min( const T& a, const U& b, const R&... c ) {
         return std::min( a, Utility::min( b, c... ) );
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_MIN_H_INCLUDED__
