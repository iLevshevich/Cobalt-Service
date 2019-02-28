#ifndef __AMQP_TRAITS_H_INCLUDED__
#define __AMQP_TRAITS_H_INCLUDED__

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
         typedef typename boost::add_pointer< _Elem >::type pointer_t;
         typedef typename boost::add_const< typename boost::add_pointer< _Elem >::type >::type const_pointer_t;
         typedef typename boost::add_pointer< typename boost::add_const< _Elem >::type >::type pointer_const_t;

         typedef typename boost::add_reference< _Elem >::type reference_t;
         typedef typename boost::add_const< typename boost::add_reference< _Elem >::type >::type const_reference_t;

         typedef typename boost::decay< _Elem >::type base_t;
      };

      template< class _Elem >
      class CharTraits : public Traits< _Elem > {
      };

      template<>
      class CharTraits< char > : public Traits< char > {
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_TRAITS_H_INCLUDED__
