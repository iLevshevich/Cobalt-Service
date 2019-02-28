#ifndef __MANAGER_CORE_H_INCLUDED__
#define __MANAGER_CORE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Core
   {
      class Core:
         private boost::noncopyable {
      public:
         typedef typename Utility::Traits< std::string >::const_reference_t port_type;
         typedef typename Utility::Traits< std::string >::const_reference_t path_type;

         typedef typename Utility::Traits< boost::shared_ptr< Chain::IConfigChain > >::base_t config_base_type;
         typedef typename Utility::Traits< boost::shared_ptr< Chain::IOperationChain > >::base_t operation_base_type;
         typedef typename Utility::Traits< boost::shared_ptr< Server > >::base_t server_base_type;
         typedef typename Utility::Traits< boost::shared_ptr< Repository > >::base_t repository_base_type;

         void __stdcall run( path_type dispatchers_path, port_type management_port ) {
            try {
               config_ =
                  Chain::AmqpToAmqpConfigChain::getInstance(
                     Chain::TcpToTcpConfigChain::getInstance(
                        Chain::AmqpToTcpConfigChain::getInstance(
                           Chain::TcpToAmqpConfigChain::getInstance() ) ) );
               repository_ = Utility::make_shared_pool< Repository, boost::default_user_allocator_malloc_free >( config_ );
               repository_->loadConfig( dispatchers_path );
               repository_->start();

               operation_ = Chain::SecurityClientOperationChain::getInstance(
                  Chain::GetStatusesOperationChain::getInstance(
                     Chain::StartDispatchersOperationChain::getInstance(
                        Chain::StopDispatchersOperationChain::getInstance(
                           Chain::AbortDispatchersOperationChain::getInstance(
                              Chain::ResetDispatchersOperationChain::getInstance(
                                 Chain::CleanLastErrorsOperationChain::getInstance(
                                    Chain::StartDispatcherOperationChain::getInstance(
                                       Chain::StopDispatcherOperationChain::getInstance(
                                          Chain::AbortDispatcherOperationChain::getInstance(
                                             Chain::ResetDispatcherOperationChain::getInstance(
                                                Chain::CleanLastErrorOperationChain::getInstance(
                                                   Chain::SaveConfigurationOperationChain::getInstance(
                                                      Chain::AddDispatcherOperationChain::getInstance(
                                                         Chain::RemoveDispatcherOperationChain::getInstance(
                                                            Chain::GetDispatcherTypesOperationChain::getInstance(
                                                               Chain::UnKnownOperationChain::getInstance(),
                                                               repository_ ),
                                                            repository_ ),
                                                         repository_ ),
                                                      repository_ ),
                                                   repository_ ),
                                                repository_ ),
                                             repository_ ),
                                          repository_ ),
                                       repository_ ),
                                    repository_ ),
                                 repository_ ),
                              repository_ ),
                           repository_ ),
                        repository_ ),
                     repository_ ),
                  Utility::Memmory::Singleton< Utility::Options >::instance().get( Utility::Options::SECURITY_WHITE_LIST ) );
               server_ = Utility::make_shared_pool< Server, boost::default_user_allocator_malloc_free >( management_port, operation_ );
               server_->run();
            }
            catch( const boost::thread_interrupted& ) {
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Core::run() [Configuration: %s] [Port: %s] [Message: %s]" ) % dispatchers_path % management_port % ex.what()).str() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Core::run() [Configuration: %s] [Port: %s] [Message: %s]" ) % dispatchers_path % management_port % "Critical error!").str() );
            }
         }

         void stop() {
            try {
               server_->stop();
               server_.reset();
               operation_.reset();

               repository_->abort();
               repository_->stop();
               repository_.reset();
               config_.reset();
            }
            catch( const boost::thread_interrupted& ) {
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Core::stop() [Message: %s]" ) % ex.what()).str() );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Core::stop() [Message: %s]" ) % "Critical error!").str() );
            }
         }

      private:
         config_base_type config_;
         repository_base_type repository_;
         operation_base_type operation_;
         server_base_type server_;
      };
   }
}

#pragma pack( pop )

#endif //__MANAGER_CORE_H_INCLUDED__
