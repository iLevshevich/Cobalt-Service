#ifndef __MANAGER_REPOSITORY_H_INCLUDED__
#define __MANAGER_REPOSITORY_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Core
   {
      class Repository :
         private boost::noncopyable {
      public:
         typedef typename Utility::Traits< boost::shared_ptr< Handler::Dispatcher::IDispatcherHandler< std::string > > >::const_reference_t handler_type;
         typedef typename Utility::Traits< boost::shared_ptr< Handler::Dispatcher::IDispatcherHandler< std::string > > >::base_t handler_base_type;
         typedef typename Utility::Traits< std::string >::const_reference_t id_type;
         typedef typename Utility::Traits< std::string >::const_reference_t file_type;
         typedef typename Utility::Traits< std::string >::const_reference_t operation_type;
         typedef typename Utility::Traits< std::string >::const_reference_t message_type;
         typedef typename Utility::Traits< boost::property_tree::ptree >::const_reference_t property_type;
         typedef typename Utility::Traits< boost::property_tree::ptree >::base_t property_base_type;
         typedef typename Utility::Traits< boost::property_tree::ptree >::const_reference_t property_source_type;
         typedef typename Utility::Traits< boost::property_tree::ptree >::reference_t property_destination_type;
         typedef typename Utility::Traits< boost::property_tree::ptree::value_type >::const_reference_t property_value_type;
         typedef typename Utility::Traits< boost::shared_ptr< Handler::Repository::IRepositoryHandler< std::string > > >::base_t repository_base_type;
         typedef typename Utility::Traits< boost::shared_ptr< Chain::IConfigChain > >::const_reference_t chain_type;
         typedef typename Utility::Traits< boost::shared_ptr< Chain::IConfigChain > >::base_t chain_base_type;
         typedef typename Utility::Traits< boost::mutex >::base_t mutex_base_type;

         explicit Repository( chain_type chain ) :
            mutex_(),
            repository_( Utility::make_shared_pool< Handler::Repository::RepositoryHandler< std::string >, boost::default_user_allocator_malloc_free >() ),
            chain_( chain ) {
         }

         std::tuple< bool, std::string > __fastcall loadConfig( file_type filename ) {
            std::lock_guard< mutex_base_type > lock( mutex_ );
            try {
               boost::property_tree::ptree config;
               boost::property_tree::read_json( filename, config );
               for( boost::property_tree::ptree::const_iterator dispatchers( config.begin() );
                    dispatchers != config.end();
                    ++dispatchers ) {
                  for( boost::property_tree::ptree::const_iterator dispatcher( dispatchers->second.begin() );
                       dispatcher != dispatchers->second.end();
                       ++dispatcher ) {
                     const handler_base_type handler( chain_->getDispatcher( dispatcher ) );
                     if( handler.get() ) {
                        repository_->add( handler );
                     }
                  }
               }

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::loadConfig() [Configuration: %s] [Message: %s]" ) % filename % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::loadConfig() [Configuration: %s] [Message: %s]" ) % filename % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > __fastcall saveConfig( file_type filename ) {
            std::lock_guard< mutex_base_type > lock( mutex_ );
            try {
               boost::property_tree::ptree config;
               config.add_child( "dispatchers", *repository_->getProperties() );
               boost::property_tree::write_json( filename, config );

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::saveConfig() [Configuration: %s] [Message: %s]" ) % filename % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::saveConfig() [Configuration: %s] [Message: %s]" ) % filename % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > getStatuses() const {
            try {
               boost::property_tree::ptree statuses;
               statuses.add_child( "dispatchers", *repository_->getStatuses() );

               return success( statuses );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::getStatuses() [Message: %s]" ) % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::getStatuses() [Message: %s]" ) % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > cleanLastError() const {
            try {
               repository_->cleanLastError();

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::cleanLastError() [Message: %s]" ) % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::cleanLastError() [Message: %s]" ) % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > cleanLastError( id_type t ) const {
            try {
               repository_->cleanLastError( t );

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::cleanLastError() [DispatcherID: %s] [Message: %s]" ) % t % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::cleanLastError() [DispatcherID: %s] [Message: %s]" ) % t % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > start() const {
            try {
               repository_->start();

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::start() [Message: %s]" ) % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::start() [Message: %s]" ) % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > stop() const {
            try {
               repository_->stop();

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::stop() [Message: %s]" ) % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::stop() [Message: %s]" ) % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > abort() const {
            try {
               repository_->abort();

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::abort() [Message: %s]" ) % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::abort() [Message: %s]" ) % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > reset() const {
            try {
               repository_->reset();

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::reset() [Message: %s]" ) % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::reset() [Message: %s]" ) % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > __stdcall start( id_type t ) const {
            try {
               repository_->start( t );

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::start() [DispatcherID: %s] [Message: %s]" ) % t % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::start() [DispatcherID: %s] [Message: %s]" ) % t % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > __stdcall stop( id_type t ) const {
            try {
               repository_->stop( t );

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::stop() [DispatcherID: %s] [Message: %s]" ) % t % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::stop() [DispatcherID: %s] [Message: %s]" ) % t % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > __stdcall abort( id_type t ) const {
            try {
               repository_->abort( t );

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::abort() [DispatcherID: %s] [Message: %s]" ) % t % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::abort() [DispatcherID: %s] [Message: %s]" ) % t % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > __stdcall reset( id_type t ) const {
            try {
               repository_->reset( t );

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::reset() [DispatcherID: %s] [Message: %s]" ) % t % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::reset() [DispatcherID: %s] [Message: %s]" ) % t % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > __stdcall add( handler_type t ) {
            std::lock_guard< mutex_base_type > lock( mutex_ );
            try {
               repository_->add( t );

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::add() [DispatcherID: %s] [Message: %s]" ) % t->getId() % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::add() [DispatcherID: %s] [Message: %s]" ) % t->getId() % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > __fastcall add( operation_type operation ) {
            std::lock_guard< mutex_base_type > lock( mutex_ );
            try {
               boost::property_tree::ptree config;
               std::stringstream stream;
               stream << operation;
               boost::property_tree::read_json( stream, config );
               for( boost::property_tree::ptree::const_iterator dispatchers( config.begin() );
                    dispatchers != config.end();
                    ++dispatchers ) {
                  for( boost::property_tree::ptree::const_iterator dispatcher( dispatchers->second.begin() );
                       dispatcher != dispatchers->second.end();
                       ++dispatcher ) {
                     const handler_base_type handler( chain_->getDispatcher( dispatcher ) );
                     if( handler.get() ) {
                        repository_->add( handler );
                     }
                  }
               }

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::add() [Operation: %s] [Message: %s]" ) % operation % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::add() [Operation: %s] [Message: %s]" ) % operation % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > __stdcall remove( id_type t ) {
            std::lock_guard< mutex_base_type > lock( mutex_ );
            try {
               repository_->remove( t );

               return success( boost::property_tree::ptree() );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::remove() [DispatcherID: %s] [Message: %s]" ) % t % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::remove() [DispatcherID: %s] [Message: %s]" ) % t % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

         std::tuple< bool, std::string > getDispatcherTypes() const {
            try {
               boost::property_tree::ptree result;
               boost::property_tree::ptree types;
               boost::property_tree::ptree AmqpToAmqp;
               boost::property_tree::ptree AmqpToTcp;
               boost::property_tree::ptree TcpToAmqp;
               boost::property_tree::ptree TcpToTcp;

               AmqpToAmqp.put( "", Handler::Dispatcher::Type::DispatcherHandlerTypeToString( Handler::Dispatcher::Type::DispatcherHandlerType::AmqpToAmqp ) );
               AmqpToTcp.put( "", Handler::Dispatcher::Type::DispatcherHandlerTypeToString( Handler::Dispatcher::Type::DispatcherHandlerType::AmqpToTcp ) );
               TcpToAmqp.put( "", Handler::Dispatcher::Type::DispatcherHandlerTypeToString( Handler::Dispatcher::Type::DispatcherHandlerType::TcpToAmqp ) );
               TcpToTcp.put( "", Handler::Dispatcher::Type::DispatcherHandlerTypeToString( Handler::Dispatcher::Type::DispatcherHandlerType::TcpToTcp ) );

               types.push_back( std::make_pair( "", AmqpToAmqp ) );
               types.push_back( std::make_pair( "", AmqpToTcp ) );
               types.push_back( std::make_pair( "", TcpToAmqp ) );
               types.push_back( std::make_pair( "", TcpToTcp ) );

               result.add_child( "types", types );

               return success( result );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::getDispatcherTypes() [Message: %s]" ) % ex.what()).str() );

               return failed( ex.what() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Repository::getDispatcherTypes() [Message: %s]" ) % "Critical error!").str() );

               return failed( "Critical error!" );
            }
         }

      private:
         std::tuple< bool, std::string > __stdcall success( property_type t ) const {
            property_base_type status;
            status.put( "status", "success" );

            property_base_type result;
            merge( t, result );

            property_base_type success;
            merge( status, success );
            merge( result, success );

            return std::make_tuple( true, boost::lexical_cast< std::string >( success ) );
         }

         std::tuple< bool, std::string > __stdcall failed( message_type t ) const {
            property_base_type status;
            status.put( "status", "failed" );

            property_base_type reason;
            reason.put( "reason", t );

            property_base_type failed;
            merge( status, failed );
            merge( reason, failed );

            return std::make_tuple( false, boost::lexical_cast< std::string >( failed ) );
         }

         void __stdcall merge( property_source_type source, property_destination_type dest ) const {
            for( property_value_type item : source ) {
               dest.put_child( item.first, item.second );
            }
         }

         mutex_base_type mutex_;
         repository_base_type repository_;
         chain_base_type chain_;
      };
   }
}

#pragma pack( pop )

#endif //__MANAGER_REPOSITORY_H_INCLUDED__
