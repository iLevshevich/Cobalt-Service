#ifndef __MANAGER_REPOSITORY_HANDLER_H_INCLUDED__
#define __MANAGER_REPOSITORY_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Repository
      {
         template< class T >
         class RepositoryHandler:
            public IRepositoryHandler< T > {
         public:
            typedef typename RepositoryHandler< T >::base_type base_type;
            typedef typename RepositoryHandler< T >::handler_type handler_type;
            typedef typename RepositoryHandler< T >::id_type id_type;
            typedef typename RepositoryHandler< T >::property_tree_base_type property_tree_base_type;

            typedef typename Utility::Traits< boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > >::const_reference_t container_item_type;
            typedef typename Utility::Traits< typename boost::unordered_map< base_type, boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > >::value_type >::const_reference_t container_value_type;
            typedef typename Utility::Traits< boost::unordered_map< base_type, boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > > >::base_t container_base_type;
            typedef typename Utility::Traits< boost::mutex >::base_t mutex_base_type;

            RepositoryHandler():
               mutex_(),
               container_() {
            }

            virtual property_tree_base_type getStatuses() override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               std::vector< boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > > container;
               container.reserve( container_.size() );

               std::transform( container_.begin(),
                               container_.end(),
                               std::back_inserter( container ),
                               [](typename boost::unordered_map< base_type, boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > >::const_reference ref) {
                                  return ref.second;
                               } );

               std::sort( container.begin(),
                          container.end(),
                          [](container_item_type lh, container_item_type rh) {
                             return lh->getPriority() > rh->getPriority();
                          } );

               boost::property_tree::ptree result;
               for( container_item_type item : container ) {
                  result.push_back( std::make_pair( "", *item->getStatus() ) );
               }
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

            virtual property_tree_base_type getProperties() override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               std::vector< boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > > container;
               container.reserve( container_.size() );

               std::transform( container_.begin(),
                               container_.end(),
                               std::back_inserter( container ),
                               [](typename boost::unordered_map< base_type, boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > >::const_reference ref) {
                                  return ref.second;
                               } );

               std::sort( container.begin(),
                          container.end(),
                          [](container_item_type lh, container_item_type rh) {
                             return lh->getPriority() > rh->getPriority();
                          } );

               boost::property_tree::ptree result;
               for( container_item_type item : container ) {
                  result.push_back( std::make_pair( "", *item->getProperty() ) );
               }
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

            virtual void cleanLastError() override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               for( container_value_type item : container_ ) {
                  item.second->cleanLastError();
               }
            }

            virtual void __stdcall cleanLastError( id_type t ) override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               const typename container_base_type::const_iterator item( container_.find( t ) );
               if( item != container_.end() ) {
                  item->second->cleanLastError();
               }
            }

            virtual void start() override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               std::vector< boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > > container;
               container.reserve( container_.size() );

               std::transform( container_.begin(),
                               container_.end(),
                               std::back_inserter( container ),
                               [](typename boost::unordered_map< base_type, boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > >::const_reference ref) {
                                  return ref.second;
                               } );

               std::sort( container.begin(),
                          container.end(),
                          [](container_item_type lh, container_item_type rh) {
                             return lh->getPriority() > rh->getPriority();
                          } );

               for( container_item_type item: container ) {
                  item->start();
               }
            }

            virtual void stop() override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               std::vector< boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > > container;
               container.reserve( container_.size() );

               std::transform( container_.begin(),
                               container_.end(),
                               std::back_inserter( container ),
                               [](typename boost::unordered_map< base_type, boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > >::const_reference ref) {
                                  return ref.second;
                               } );

               std::sort( container.begin(),
                          container.end(),
                          [](container_item_type lh, container_item_type rh) {
                             return lh->getPriority() < rh->getPriority();
                          } );

               for( container_item_type item : container ) {
                  item->stop();
               }
            }

            virtual void abort() override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               std::vector< boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > > container;
               container.reserve( container_.size() );

               std::transform( container_.begin(),
                               container_.end(),
                               std::back_inserter( container ),
                               [](typename boost::unordered_map< base_type, boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > >::const_reference ref) {
                                  return ref.second;
                               } );

               std::sort( container.begin(),
                          container.end(),
                          [](container_item_type lh, container_item_type rh) {
                             return lh->getPriority() < rh->getPriority();
                          } );

               for( container_item_type item : container ) {
                  item->abort();
               }
            }

            virtual void reset() override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               std::vector< boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > > container;
               container.reserve( container_.size() );

               std::transform( container_.begin(),
                               container_.end(),
                               std::back_inserter( container ),
                               [](typename boost::unordered_map< base_type, boost::shared_ptr< Dispatcher::IDispatcherHandler< base_type > > >::const_reference ref) {
                                  return ref.second;
                               } );

               std::sort( container.begin(),
                          container.end(),
                          [](container_item_type lh, container_item_type rh) {
                             return lh->getPriority() > rh->getPriority();
                          } );

               for( container_item_type item : container ) {
                  item->reset();
               }
            }

            virtual void __stdcall start( id_type t ) override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               const typename container_base_type::const_iterator item( container_.find( t ) );
               if( item != container_.end() ) {
                  item->second->start();
               }
            }

            virtual void __stdcall stop( id_type t ) override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               const typename container_base_type::const_iterator item( container_.find( t ) );
               if( item != container_.end() ) {
                  item->second->stop();
               }
            }

            virtual void __stdcall abort( id_type t ) override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               const typename container_base_type::const_iterator item( container_.find( t ) );
               if( item != container_.end() ) {
                  item->second->abort();
               }
            }

            virtual void __stdcall reset( id_type t ) override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               const typename container_base_type::const_iterator item( container_.find( t ) );
               if( item != container_.end() ) {
                  item->second->reset();
               }
            }

            virtual void __stdcall add( handler_type t ) override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               container_.insert( std::make_pair( t->getId(), std::move( t ) ) );
            }

            virtual void __stdcall remove( id_type t ) override {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               const typename container_base_type::const_iterator item( container_.find( t ) );
               if( item != container_.end() ) {
                  container_.erase( item );
               }
            }

            virtual ~RepositoryHandler() = default;

         private:
            mutex_base_type mutex_;
            container_base_type container_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_REPOSITORY_HANDLER_H_INCLUDED__
