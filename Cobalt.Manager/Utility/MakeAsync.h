#ifndef __MANAGER_MAKE_ASYNC_H_INCLUDED__
#define __MANAGER_MAKE_ASYNC_H_INCLUDED__

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
      class Async1st;
#pragma warning(default:4348)

      template< class _Destroy, class _Thread >
      class Async1st :
         private boost::noncopyable {
      public:
         typedef boost::scoped_thread< _Destroy, _Thread > thread_type;

         template< class F, class ...Args, typename = typename boost::disable_if< boost::is_same< typename boost::decay< F >::type, _Thread >, void* >::type >
         explicit Async1st( F&& f, Args&&... args ) noexcept :
            thread_( boost::forward< F >( f ), boost::forward< Args >( args )... ) {
         }

         template< class F, typename = typename boost::enable_if< boost::is_same< typename boost::decay< F >::type, _Thread >, _Thread >::type >
         explicit Async1st( F&& f ) noexcept :
            thread_( boost::move( f ) ) {
         }

      private:
         thread_type thread_;
      };

#pragma warning(disable:4348) //C4348 переопределение параметра по умолчанию
      template< class _Elem, class _Destroy = boost::interrupt_and_join_if_joinable, class _Thread = boost::thread >
      class Async;
#pragma warning(default:4348)

      template< Import::ImportType _Type, class _Destroy, class _Thread >
      class Async< Import::IPublish< _Type >, _Destroy, _Thread > :
         private boost::noncopyable {
      public:
         typedef Import::IPublish< _Type > elem_type;
         typedef boost::shared_ptr< elem_type > ptr_type;
         typedef boost::scoped_thread< _Destroy, _Thread > thread_type;

         template< class F, class ...Args, typename = typename boost::disable_if< boost::is_same< typename boost::decay< F >::type, _Thread >, void* >::type >
         explicit Async( const ptr_type& ptr, F&& f, Args&&... args ) noexcept :
            ptr_( ptr ),
            thread_( boost::forward< F >( f ), boost::forward< Args >( args )... ) {
         }

         template< class F, typename = typename boost::enable_if< boost::is_same< typename boost::decay< F >::type, _Thread >, _Thread >::type >
         explicit Async( const ptr_type& ptr, F&& f ) noexcept :
            ptr_( ptr ),
            thread_( boost::move( f ) ) {
         }

         void close() const noexcept {
            ptr_->quit();
         }

         bool completeClose() const noexcept {
            return ptr_->tryQuit();
         }

         bool isClosed() const noexcept {
            return ptr_->isQuited();
         }

         ~Async() {
            close();
         }

      private:
         ptr_type ptr_;
         thread_type thread_;
      };

      template< Import::ImportType _Type, class _Destroy, class _Thread >
      class Async< Import::IConsume< _Type >, _Destroy, _Thread > :
         private boost::noncopyable {
      public:
         typedef Import::IConsume< _Type > elem_type;
         typedef boost::shared_ptr< elem_type > ptr_type;
         typedef boost::scoped_thread< _Destroy, _Thread > thread_type;

         template< class F, class ...Args, typename = typename boost::disable_if< boost::is_same< typename boost::decay< F >::type, _Thread >, void* >::type >
         explicit Async( const ptr_type& ptr, F&& f, Args&&... args ) noexcept :
            ptr_( ptr ),
            thread_( boost::forward< F >( f ), boost::forward< Args >( args )... ) {
         }

         template< class F, typename = typename boost::enable_if< boost::is_same< typename boost::decay< F >::type, _Thread >, _Thread >::type >
         explicit Async( const ptr_type& ptr, F&& f ) noexcept :
            ptr_( ptr ),
            thread_( boost::move( f ) ) {
         }

         void close() const noexcept {
            ptr_->quit();
         }

         bool completeClose() const noexcept {
            return ptr_->tryQuit();
         }

         bool isClosed() const noexcept {
            return ptr_->isQuited();
         }

         ~Async() {
            close();
         }

      private:
         ptr_type ptr_;
         thread_type thread_;
      };

      template< class Ptr, class F, class ...Args >
      inline constexpr boost::shared_ptr< Async< typename boost::shared_ptr< Ptr >::element_type > > make_async( const boost::shared_ptr< Ptr >& ptr, F&& f, Args&&... args ) noexcept {
         return Utility::make_shared_pool< Async< typename boost::shared_ptr< Ptr >::element_type > >( boost::move( ptr ), boost::move( f ), boost::move( args )... );
      }

      template< class Ptr, class F >
      inline constexpr boost::shared_ptr< Async< typename boost::shared_ptr< Ptr >::element_type > > make_async( const boost::shared_ptr< Ptr >& ptr, F&& f ) noexcept {
         return Utility::make_shared_pool< Async< typename boost::shared_ptr< Ptr >::element_type > >( boost::move( ptr ), boost::move( f ) );
      }

      template< class F, class ...Args >
      inline constexpr boost::shared_ptr< Async1st< > > make_async( F&& f, Args&&... args ) noexcept {
         return Utility::make_shared_pool< Async1st< > >( boost::move( f ), boost::move( args )... );
      }

      template< class _Destroy, class F, class ...Args >
      inline constexpr boost::shared_ptr< Async1st< _Destroy > > make_async( F&& f, Args&&... args ) noexcept {
         return Utility::make_shared_pool< Async1st< _Destroy > >( boost::move( f ), boost::move( args )... );
      }

      template< class F >
      inline constexpr boost::shared_ptr< Async1st< > > make_async( F&& f ) noexcept {
         return Utility::make_shared_pool< Async1st< > >( boost::move( f ) );
      }

      template< class _Destroy, class F >
      inline constexpr boost::shared_ptr< Async1st< _Destroy > > make_async( F&& f ) noexcept {
         return Utility::make_shared_pool< Async1st< _Destroy > >( boost::move( f ) );
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_MAKE_ASYNC_H_INCLUDED__
