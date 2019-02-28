#ifndef __AMQP_FWDHEADERS_H_INCLUDED__
#define __AMQP_FWDHEADERS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

namespace Cobalt
{
   namespace Utility
   {
      template< class _Elem >
      class Traits;

      template< class _Elem >
      class CharTraits;

      template< typename Base >
      class enable_make;

      enum FlagsType;
      enum ExchangeType;

      class IHostSettings;
      class HostSettings;

      class IChannelSettings;
      class ChannelSettings;

      class IExchangeSettings;
      class ExchangeSettings;

      class ILoginSettings;
      class LoginSettings;

      class IQueueSettings;
      class QueueSettings;

      class IConnectionSettings;
      class ConnectionSettings;

      class ISettings;
      class Settings;

      class ISettingsBuilder;
      class SettingsBuilder;

      class Transaction;

      template< class _Interface,
         class _Class,
         class _Allocator = boost::default_user_allocator_new_delete,
         class _Mutex = boost::details::pool::default_mutex,
         size_t _NextSize = 32,
         size_t _MaxSize = 0,
         class _Pool = boost::pool_allocator< _Class, _Allocator, _Mutex, _NextSize, _MaxSize >,
         class... Args >
         boost::shared_ptr< _Interface > make_shared_pool_enable(Args&& ... args);

      template< class _Class,
         class _Allocator = boost::default_user_allocator_new_delete,
         class _Mutex = boost::details::pool::default_mutex,
         size_t _NextSize = 32,
         size_t _MaxSize = 0,
         class _Pool = boost::pool_allocator< _Class, _Allocator, _Mutex, _NextSize, _MaxSize >,
         class... Args >
         boost::shared_ptr< _Class > make_shared_pool(Args&& ... args);
   }

   namespace Memmory
   {
      template< class _Elem = char, class _Traits = Utility::CharTraits< _Elem > >
      class Buffer;

      typedef Buffer< > CharBuffer;
   }

   namespace Poco
   {
      namespace Socket
      {
         class ISocket;
         class IPocoSocket;
         class PocoSocket;
      }

      namespace Buffer
      {
         template< class _Elem = char, class _Traits = Cobalt::Utility::CharTraits< _Elem > >
         class IPocoBuffer;

         typedef IPocoBuffer< > ICharPocoBuffer;

         class PocoBuffer;
      }

      namespace Connection
      {
         class IConnection;
         class Connection;
      }

      class PocoHandler;
   }

   namespace EntryPoint
   {
      class IConsume;
      class Consume;

      class IPublish;
      class Publish;
   }
}

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
   class shared_ptr;

   template< class _Ty, class... _Types >
   inline shared_ptr< _Ty > make_shared( _Types&&... _Args );

   template<class _Fty>
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

   template< typename T >
   class atomic;

   typedef atomic< bool > atomic_bool;

   struct default_user_allocator_new_delete;
   struct default_user_allocator_malloc_free;

   template<typename UserAllocator = default_user_allocator_new_delete>
   class pool;

   /*
    * UserAllocator: Defines the method that the underlying Pool will use to allocate memory from the system(default = boost::default_user_allocator_new_delete).
    * Mutex: Allows the user to determine the type of synchronization to be used on the underlying singleton_pool(default = boost::details::pool::default_mutex).
    * NextSize: The value of this parameter is passed to the underlying Pool when it is created and specifies the number of chunks to allocate in the first allocation request (default = 32).
    * MaxSize: The value of this parameter is passed to the underlying Pool when it is created and specifies the maximum number of chunks to allocate in any single allocation request (default = 0).
    */
   template<typename T,
      typename UserAllocator = default_user_allocator_new_delete,
      typename Mutex = details::pool::default_mutex,
      unsigned NextSize = 32, unsigned MaxSize = 0>
      class pool_allocator;

   template<typename T,
      typename UserAllocator = default_user_allocator_new_delete,
      typename Mutex = details::pool::default_mutex,
      unsigned NextSize = 32, unsigned MaxSize = 0>
      class fast_pool_allocator;
}

namespace Poco
{
   namespace Net
   {
      class StreamSocket;
      class SocketAddress;
   }

   class Exception;
}

namespace AMQP
{
   class Connection;
   class ConnectionHandler;
   class Channel;
}

#endif //__AMQP_FWDHEADERS_H_INCLUDED__
