#ifndef __TCP_MAKE_ASYNC_H_INCLUDED__
#define __TCP_MAKE_ASYNC_H_INCLUDED__

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
      template< class _Destroy = boost::interrupt_and_join_if_joinable, class _Thread = boost::thread >
      class Async;
#pragma warning(default:4348)

      template< class _Destroy, class _Thread >
      class Async :
         private boost::noncopyable {
      public:
         typedef boost::scoped_thread< _Destroy, _Thread > thread_type;

         template< class F, class ...Args, typename = typename boost::disable_if< boost::is_same< typename boost::decay< F >::type, _Thread >, void* >::type >
         explicit Async( F&& f, Args&&... args ) noexcept :
            thread_( boost::forward< F >( f ), boost::forward< Args >( args )... ) {
         }

         template< class F, typename = typename boost::enable_if< boost::is_same< typename boost::decay< F >::type, _Thread >, _Thread >::type >
         explicit Async( F&& f ) noexcept :
            thread_( boost::move( f ) ) {
         }

      private:
         thread_type thread_;
      };

      template< class F, class ...Args >
      inline constexpr boost::shared_ptr< Async< > > make_async( F&& f, Args&&... args ) noexcept {
         return Utility::make_shared_pool< Async< > >( boost::move( f ), boost::move( args )... );
      }

      template< class F >
      inline constexpr boost::shared_ptr< Async< > > make_async( F&& f ) noexcept {
         return Utility::make_shared_pool< Async< > >( boost::move( f ) );
      }
   }
}

#pragma pack( pop )

#endif //__TCP_MAKE_ASYNC_H_INCLUDED__
