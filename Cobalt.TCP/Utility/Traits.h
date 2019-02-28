#ifndef __TCP_TRAITS_H_INCLUDED__
#define __TCP_TRAITS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      template< class _Elem >
      class Traits {
      public:
         typedef typename boost::decay< _Elem >::type base_t;

         typedef base_t* pointer_t;
         typedef const base_t* const_pointer_t;
         typedef base_t* const pointer_const_t;

         typedef base_t& reference_t;
         typedef const base_t& const_reference_t;

         typedef base_t&& rvalue_reference_t;
         typedef const base_t&& const_rvalue_reference_t;
      };

      template<>
      class Traits< void > {
      public:
         typedef void* pointer_t;
         typedef const void* const_pointer_t;
         typedef void* const pointer_const_t;
      };
   }
}

#pragma pack( pop )

#endif //__TCP_TRAITS_H_INCLUDED__
