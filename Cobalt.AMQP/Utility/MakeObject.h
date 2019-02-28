#ifndef __AMQP_MAKE_OBJECT_H_INCLUDED__
#define __AMQP_MAKE_OBJECT_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
#pragma warning(disable:4348) //C4348 переопределение параметра по умолчанию
      template< class _Interface,
                class _Class,
                class _Allocator = boost::default_user_allocator_new_delete,
                class _Mutex = boost::details::pool::default_mutex,
                size_t _NextSize = 32,
                size_t _MaxSize = 0,
                class _Pool = boost::pool_allocator< _Class, _Allocator, _Mutex, _NextSize, _MaxSize >,
                class... Args >
      boost::shared_ptr< _Interface > make_shared_pool_enable( Args&& ... args ) {
         BOOST_STATIC_ASSERT(boost::is_base_of< _Interface, _Class >::value);

         static _Pool pool;
         while( true ) {
            const boost::shared_ptr< _Interface > ptr( boost::allocate_shared< enable_make< _Class > >( pool, std::forward< Args >( args ) ... ) );
            if( ptr.get() ) {
               return ptr;
            }
         }
      }
#pragma warning(default:4348)

#pragma warning(disable:4348) //C4348 переопределение параметра по умолчанию
      template< class _Class,
                class _Allocator = boost::default_user_allocator_new_delete,
                class _Mutex = boost::details::pool::default_mutex,
                size_t _NextSize = 32,
                size_t _MaxSize = 0,
                class _Pool = boost::pool_allocator< _Class, _Allocator, _Mutex, _NextSize, _MaxSize >,
                class... Args >
      boost::shared_ptr< _Class > make_shared_pool( Args&& ... args ) {
         static _Pool pool;
         while( true ) {
            const boost::shared_ptr< _Class > ptr( boost::allocate_shared< _Class >( pool, std::forward< Args >( args ) ... ) );
            if( ptr.get() ) {
               return ptr;
            }
         }
      }
   }
}
#pragma warning(default:4348)

#pragma pack( pop )

#endif //__AMQP_MAKE_OBJECT_H_INCLUDED__
