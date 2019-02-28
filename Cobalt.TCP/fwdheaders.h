#ifndef __TCP_FWDHEADERS_H_INCLUDED__
#define __TCP_FWDHEADERS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

namespace std
{
   template< class _Ty >
   class allocator;

   template< class _Elem >
   struct char_traits;

   template< class _Elem, class _Traits, class _Alloc >
   class basic_string;

   typedef basic_string< char, char_traits< char >, allocator< char > > string;

   template< class _Ty, class _Alloc = allocator< _Ty > >
   class vector;

   template< class _Ty >
   class enable_shared_from_this;

   template< class _Ty >
   class shared_ptr;

   template< class _Ty, class... _Types >
   inline shared_ptr< _Ty > make_shared( _Types&&... _Args );

   template< class _Fty >
   class function;

   class exception;
   class runtime_error;
}

namespace boost
{
   namespace noncopyable_
   {
      class noncopyable;
   }

   typedef noncopyable_::noncopyable noncopyable;

   template< typename T >
   struct add_pointer;

   template< typename T >
   struct add_const;

   template< typename T >
   struct add_reference;

   template< typename T >
   struct remove_const;

   template< typename T >
   struct remove_all_extents;

   template< class Base, class Derived >
   struct is_base_of;

   struct default_user_allocator_new_delete;
   struct default_user_allocator_malloc_free;

   template< typename UserAllocator = default_user_allocator_new_delete >
   class pool;

   /*
   * UserAllocator: Defines the method that the underlying Pool will use to allocate memory from the system(default = boost::default_user_allocator_new_delete).
   * Mutex: Allows the user to determine the type of synchronization to be used on the underlying singleton_pool(default = boost::details::pool::default_mutex).
   * NextSize: The value of this parameter is passed to the underlying Pool when it is created and specifies the number of chunks to allocate in the first allocation request (default = 32).
   * MaxSize: The value of this parameter is passed to the underlying Pool when it is created and specifies the maximum number of chunks to allocate in any single allocation request (default = 0).
   */
   template< typename T,
             typename UserAllocator = default_user_allocator_new_delete,
             typename Mutex = details::pool::default_mutex,
             unsigned NextSize = 32, unsigned MaxSize = 0 >
   class pool_allocator;

   template< typename T,
             typename UserAllocator = default_user_allocator_new_delete,
             typename Mutex = details::pool::default_mutex,
             unsigned NextSize = 32, unsigned MaxSize = 0 >
   class fast_pool_allocator;
}

namespace Cobalt
{
   namespace Utility
   {
      template< class _Elem >
      class Traits;

      template< typename Base >
      class enable_make;

      class ISettingsBuilder;
      class SettingsBuilder;

      class ISettings;
      class Settings;

      template< class _Interface,
                class _Class,
                class _Allocator = boost::default_user_allocator_new_delete,
                class _Mutex = boost::details::pool::default_mutex,
                size_t _NextSize = 32,
                size_t _MaxSize = 0,
                class _Pool = boost::pool_allocator< _Class, _Allocator, _Mutex, _NextSize, _MaxSize >,
                class... Args >
      boost::shared_ptr< _Interface > make_shared_pool_enable( Args&& ... args );

      template< class _Interface,
                class _Class,
                class _Allocator = boost::default_user_allocator_new_delete,
                class _Mutex = boost::details::pool::default_mutex,
                size_t _NextSize = 32,
                size_t _MaxSize = 0,
                class _Pool = boost::pool_allocator< _Class, _Allocator, _Mutex, _NextSize, _MaxSize >,
                class... Args >
      boost::shared_ptr< _Interface > make_shared_pool_enable2( Args&& ... args );

      template< class _Class,
                class _Allocator = boost::default_user_allocator_new_delete,
                class _Mutex = boost::details::pool::default_mutex,
                size_t _NextSize = 32,
                size_t _MaxSize = 0,
                class _Pool = boost::pool_allocator< _Class, _Allocator, _Mutex, _NextSize, _MaxSize >,
                class... Args >
      boost::shared_ptr< _Class > make_shared_pool( Args&& ... args );

      template< class _Class,
                class _Allocator = boost::default_user_allocator_new_delete,
                class _Mutex = boost::details::pool::default_mutex,
                size_t _NextSize = 32,
                size_t _MaxSize = 0,
                class _Pool = boost::pool_allocator< _Class, _Allocator, _Mutex, _NextSize, _MaxSize >,
                class... Args >
      boost::shared_ptr< _Class > make_shared_pool2( Args&& ... args );

      template< class _Destroy = boost::interrupt_and_join_if_joinable, class _Thread = boost::thread >
      class Async;

      template< class F, class ...Args >
      inline constexpr boost::shared_ptr< Async< > > make_async( F&& f, Args&&... args ) noexcept;

      template< class F >
      inline constexpr boost::shared_ptr< Async< > > make_async( F&& f ) noexcept;
   }

   namespace EntryPoint
   {
      class IConsume;
      class Consume;

      class IPublish;
      class Publish;
   }

   namespace Memmory
   {
      template< class _Elem >
      class Buffer;
   }

   namespace Tcp
   {
      class BlockClient;
      class BlockServer;
   }
}

#endif //__TCP_FWDHEADERS_H_INCLUDED__
