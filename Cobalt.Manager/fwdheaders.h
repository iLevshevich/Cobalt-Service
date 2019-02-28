#ifndef __MANAGER_FWDHEADERS_H_INCLUDED__
#define __MANAGER_FWDHEADERS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

namespace std
{
   template< class _Ty >
   class allocator;

   template< class _Ty = void >
   struct equal_to;

   template< class _Ty1, class _Ty2 >
   struct pair;

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

   template< class _Fty >
   class function;

   class exception;
   class runtime_error;

   template< class _Ty = void >
   struct less;
}

namespace boost
{
   namespace filesystem
   {
      class path;
   }

   namespace noncopyable_
   {
      class noncopyable;
   }

   namespace lockfree
   {
      template< size_t Size >
      struct capacity;

      template< typename T, typename ...Options >
      class spsc_queue;
   }

   typedef noncopyable_::noncopyable noncopyable;

   template< typename T >
   struct add_pointer;

   template< typename T >
   struct add_const;

   template< typename T >
   struct add_reference;

   template< class T >
   struct add_rvalue_reference;

   template< typename T >
   struct remove_const;

   template< typename T >
   struct remove_all_extents;

   template< class T >
   class shared_ptr;

   struct join_if_joinable;
   struct interrupt_and_join_if_joinable;

   class thread;

   template< class CallableThread = join_if_joinable, class Thread = thread >
   class scoped_thread;

   template< class Cond, class T = void >
   struct enable_if;

   template< class Cond, class T = void >
   struct disable_if;

   template< class T, class U >
   struct is_same;

   template< class T >
   struct decay;

   template< class From, class To >
   struct is_convertible;

   template< class Base, class Derived >
   struct is_base_of;

   template< typename T >
   class atomic;

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

   template< class T >
   struct hash;

   namespace unordered
   {
      template< class K, class T, class H, class P, class A >
      class unordered_map;
   }

   namespace property_tree
   {
      template< class Key, class Data, class KeyCompare = std::less< Key > >
      class basic_ptree;

      typedef basic_ptree< std::string, std::string > ptree;
   }

   namespace uuids {
	   namespace detail {
		   class sha1;
	   }
   }
}

namespace Cobalt
{
   namespace Import
   {
      enum ImportType;

      namespace Utility
      {
         enum FlagsType;
         enum ExchangeType;

         class IChannelSettings;
         class IConnectionSettings;
         class IExchangeSettings;
         class IHostSettings;
         class ILoginSettings;
         class IQueueSettings;

         template< ImportType _Type >
         class ISettings;

         template< ImportType _Type >
         class ISettingsBuilder;
      }

      template< ImportType _Type >
      class IConsume;

      template< ImportType _Type >
      class IPublish;
   }

   namespace Core
   {
      namespace Chain
      {
         class IConfigChain;
         class AmqpToAmqpConfigChain;
         class AmqpToTcpConfigChain;
         class TcpToAmqpConfigChain;
         class TcpToTcpConfigChain;

         enum class OperationType;
         class IOperationChain;
         class UnKnownOperationChain;
         class GetStatusesOperationChain;
         class SaveConfigurationOperationChain;
         class StartDispatchersOperationChain;
         class StopDispatchersOperationChain;
         class AbortDispatchersOperationChain;
         class ResetDispatchersOperationChain;
         class CleanLastErrorsOperationChain;
         class StartDispatcherOperationChain;
         class StopDispatcherOperationChain;
         class AbortDispatcherOperationChain;
         class ResetDispatcherOperationChain;
         class CleanLastErrorOperationChain;
      }

      class Session;
      class Server;
      class Repository;

      class Core;
   }

   namespace Utility
   {
      namespace Memmory
      {
         template< class T >
         class Singleton;

         template< class _Elem >
         class Buffer;
      }

      class Logger;
      class Options;

      template< typename Base >
      class enable_make;

      template< typename Base >
      class enable_make;

      template< class _Elem >
      class Traits;

      template< class _Destroy = boost::interrupt_and_join_if_joinable, class _Thread = boost::thread >
      class Async1st;

      template< class _Elem, class _Destroy = boost::interrupt_and_join_if_joinable, class _Thread = boost::thread >
      class Async;

      template< class Ptr, class F, class ...Args >
      inline constexpr boost::shared_ptr< Async< typename boost::shared_ptr< Ptr >::element_type > > make_async( const boost::shared_ptr< Ptr >& ptr, F&& f, Args&&... args ) noexcept;

      template< class Ptr, class F >
      inline constexpr boost::shared_ptr< Async< typename boost::shared_ptr< Ptr >::element_type > > make_async( const boost::shared_ptr< Ptr >& ptr, F&& f ) noexcept;

      template< class F, class ...Args >
      inline constexpr boost::shared_ptr< Async1st< > > make_async( F&& f, Args&&... args ) noexcept;

      template< class _Destroy, class F, class ...Args >
      inline constexpr boost::shared_ptr< Async1st< _Destroy > > make_async( F&& f, Args&&... args ) noexcept;

      template< class F >
      inline constexpr boost::shared_ptr< Async1st< > > make_async( F&& f ) noexcept;

      template< class _Destroy, class F >
      inline constexpr boost::shared_ptr< Async1st< _Destroy > > make_async( F&& f ) noexcept;

      template< class _Interface,
                class _Class,
                class _Allocator = boost::default_user_allocator_new_delete,
                class _Mutex = boost::details::pool::default_mutex,
                size_t _NextSize = 32,
                size_t _MaxSize = 0,
                class _Pool = boost::pool_allocator< _Class, _Allocator, _Mutex, _NextSize, _MaxSize >,
                class... Args >
      boost::shared_ptr< _Interface > make_shared_pool_enable( Args&& ... args );

      template< class _Class,
                class _Allocator = boost::default_user_allocator_new_delete,
                class _Mutex = boost::details::pool::default_mutex,
                size_t _NextSize = 32,
                size_t _MaxSize = 0,
                class _Pool = boost::pool_allocator< _Class, _Allocator, _Mutex, _NextSize, _MaxSize >,
                class... Args >
      boost::shared_ptr< _Class > make_shared_pool( Args&& ... args );
   }

   namespace Factory
   {
      template< Import::ImportType _Type >
      class IImportFactory;

      template< Import::ImportType _Type >
      class ImportFactory;

      template< class _Elem, size_t _Capacity = 4096 >
      class ObjectFactory;
   }

   namespace Handler
   {
      namespace Repository
      {
         template< class T >
         class IRepositoryHandler;

         template< class T >
         class RepositoryHandler;
      }

      namespace Dispatcher
      {
         namespace Type
         {
            enum class DispatcherHandlerType;
         }

         namespace Priority
         {
            enum DispatcherHandlerPriority;
         }

         template< class T >
         class IDispatcherHandler;

         class AmqpToAmqpDispatcherHandler;
         class AmqpToTcpDispatcherHandler;
         class TcpToAmqpDispatcherHandler;
         class TcpToTcpDispatcherHandler;

         template< class T >
         class IAmqpToAmqpDispatcherHandlerBuilder;

         template< class T, class U >
         class AmqpToAmqpDispatcherHandlerBuilder;

         template< class T >
         class ITcpToAmqpDispatcherHandlerBuilder;

         template< class T, class U >
         class TcpToAmqpDispatcherHandlerBuilder;

         template< class T >
         class IAmqpToTcpDispatcherHandlerBuilder;

         template< class T, class U >
         class AmqpToTcpDispatcherHandlerBuilder;

         template< class T >
         class ITcpToTcpDispatcherHandlerBuilder;

         template< class T, class U >
         class TcpToTcpDispatcherHandlerBuilder;
      }

      namespace Property
      {
         class IPropertyHandler;

         template< class _Type >
         class PropertyHandler;
      }

      namespace Meta
      {
         template< class T >
         class IMetaHandler;

         class MetaHandler;
      }

      namespace State
      {
         enum StateHandlerType;
         class IResetHandler;
         class IStateHandler;

         template< StateHandlerType T >
         class StateHandler;
      }

      namespace Queue
      {
         template< class T, class U >
         class IQueueHandler;

         template< class _Elem, std::size_t _Capacity = 4096, class _Meta = std::string >
         class QueueHandler;

         template< class _Elem, std::size_t _Capacity = 4096, class _Meta = std::string >
         class IQueueHandlerBuilder;

         template< class _Elem, std::size_t _Capacity = 4096, class _Meta = std::string >
         class QueueHandlerBuilder;

         template< class T >
         class BlockQueue;

         template< class _Elem, class _Meta = std::string >
         class BlockQueueHandler;

         template< class _Elem, class _Meta = std::string >
         class IBlockQueueHandlerBuilder;

         template< class _Elem, class _Meta = std::string >
         class BlockQueueHandlerBuilder;
      }

      namespace Monitor
      {
         template< class T >
         class IMonitorHandler;

         template< class T >
         class MonitorHandler;

         template<>
         class MonitorHandler< void >;

         template< class T >
         class IMonitorHandlerBuilder;

         template<>
         class IMonitorHandlerBuilder< void >;

         template< class T >
         class MonitorHandlerBuilder;

         template<>
         class MonitorHandlerBuilder< void >;

         template< class T >
         class IInputMonitorHandler;

         template< class T >
         class InputMonitorHandler;

         template<>
         class InputMonitorHandler< void >;

         template< class T >
         class IInputMonitorHandlerBuilder;

         template<>
         class IInputMonitorHandlerBuilder< void >;

         template< class T >
         class InputMonitorHandlerBuilder;

         template<>
         class InputMonitorHandlerBuilder< void >;

         template< class T >
         class IOutputMonitorHandler;

         template<>
         class IOutputMonitorHandler< void >;

         template< class T >
         class OutputMonitorHandler;

         template<>
         class OutputMonitorHandler< void >;

         template< class T >
         class IOutputMonitorHandlerBuilder;

         template<>
         class IOutputMonitorHandlerBuilder< void >;

         template< class T >
         class OutputMonitorHandlerBuilder;

         template<>
         class OutputMonitorHandlerBuilder< void >;
      }

      namespace Input
      {
         template< Import::ImportType _Type >
         class IInputHandlerAcknowledge;

         template< Import::ImportType _Type >
         class InputHandlerAcknowledge;

         template< Import::ImportType _Type >
         class InputHandlerNoAcknowledge;

         template< class T >
         class IInputHandler;

         template< class T, class U, Import::ImportType _Type >
         class IInputHandlerBuilder;

         template< class T, class U, Import::ImportType _Type >
         class InputHandlerBuilder;

         template< Import::ImportType _Type >
         class InputHandler;
      }

      namespace Output
      {
         template< Import::ImportType _Type >
         class IOutputHandlerAcknowledge;

         template< Import::ImportType _Type >
         class OutputHandlerAcknowledge;

         template< Import::ImportType _Type >
         class OutputHandlerNoAcknowledge;

         template< class T >
         class IOutputHandler;

         template< class T, class U, Import::ImportType _Type >
         class IOutputHandlerBuilder;

         template< class T, class U, Import::ImportType _Type >
         class OutputHandlerBuilder;

         template< Import::ImportType _Type >
         class OutputHandler;
      }

      namespace Error
      {
         template< class T >
         class ILastErrorHandler;

         template< class T >
         class LastErrorHandler;
      }

      namespace Performance
      {
         enum class PerformanceHandlerType;
         class IPerformanceHandler;

         template< PerformanceHandlerType _Ty >
         class PerformanceHandler;
      }
   }
}

#endif //__MANAGER_FWDHEADERS_H_INCLUDED__
