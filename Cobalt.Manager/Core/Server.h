#ifndef __MANAGER_SERVER_H_INCLUDED__
#define __MANAGER_SERVER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Core
   {
      class Session :
         public boost::enable_shared_from_this< Session > {
      public:
         typedef typename Utility::Traits< boost::shared_ptr< Session > >::base_t session_base_type;
         typedef typename Utility::Traits< boost::shared_ptr< boost::asio::ip::tcp::socket > >::base_t socket_base_type;
         typedef typename Utility::Traits< Utility::Memmory::Buffer< char > >::base_t buffer_base_type;
         typedef typename Utility::Traits< boost::asio::ip::tcp::socket >::reference_t socket_type;
         typedef typename Utility::Traits< boost::asio::io_context >::reference_t context_type;
         typedef typename Utility::Traits< std::string >::const_reference_t convert_type;
         typedef typename Utility::Traits< std::string >::const_reference_t data_type;
         typedef typename Utility::Traits< std::string >::const_reference_t message_type;
         typedef typename Utility::Traits< boost::property_tree::ptree >::base_t property_base_type;
         typedef typename Utility::Traits< boost::property_tree::ptree >::const_reference_t property_source_type;
         typedef typename Utility::Traits< boost::property_tree::ptree >::reference_t property_destination_type;
         typedef typename Utility::Traits< boost::property_tree::ptree::value_type >::const_reference_t property_value_type;
         typedef typename Utility::Traits< boost::shared_ptr< Chain::IOperationChain > >::const_reference_t chain_type;
         typedef typename Utility::Traits< boost::shared_ptr< Chain::IOperationChain > >::base_t chain_base_type;

         static session_base_type getInstance( context_type io_context, chain_type chain ) {
            return Utility::make_shared_pool_enable< Session, Session, boost::default_user_allocator_malloc_free >( io_context, chain );
         }

         socket_type socket() const {
            return *socket_;
         }

         void start() {
            doRead();
         }

      protected:
         explicit Session( context_type io_context, chain_type chain ) :
            socket_( Utility::make_shared_pool< boost::asio::ip::tcp::socket, boost::default_user_allocator_malloc_free >( io_context ) ),
            buffer_( BUFFER_LENGTH ),
            chain_( chain ) {
         }

         void doRead() {
            boost::shared_ptr< Session > self( shared_from_this() );
            socket_->async_read_some( boost::asio::buffer( buffer_.get(), buffer_.size()),
                                      [this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
                                         if( !ec ) {
                                            doWrite( bytes_transferred );
                                         }
                                         else {
                                            Utility::Memmory::Singleton< Utility::Logger >::instance()
                                               .error( (boost::format( "Server::Session::do_read() [Category: %s] [Message: %s]" ) % ec.category().name() % ec.value()).str() );
                                         }
                                      } );
         }

		 void doWrite( std::size_t bytes_transferred ) {
			 prepare();
			 ///
			 boost::shared_ptr< Session > self(shared_from_this());
			 socket_->async_write_some( boost::asio::buffer(buffer_.get(), Utility::min(strlen(buffer_.get()), buffer_.size())),
									    [this, self](boost::system::error_code ec, std::size_t bytes_transferred) {
										   if (ec) {
											   Utility::Memmory::Singleton< Utility::Logger >::instance()
												   .error((boost::format("Server::Session::do_write() [Category: %s] [Message: %s]") % ec.category().name() % ec.value()).str());
										   }
										});
		 }

		 void __stdcall setBuffer( data_type responce ) {
			 buffer_.clean();
			 ///
			 {
				 checkBufferSize( responce.size() );
			 }
			 ///
			 memcpy_s( buffer_.get(), buffer_.size(), responce.c_str(), responce.size() );
		 }

		 inline void __stdcall checkBufferSize( const size_t size ) {
			 if ( size > buffer_.size() ) {
				 buffer_.reset( size + 1 );
			 }
		 }

         void prepare() {
            try {
               const std::tuple< bool, std::string > result( chain_->execute( boost::lexical_cast< boost::property_tree::ptree, std::string >( buffer_.get() ) ) );

               setBuffer( std::get< 1 >( result ) );
            }
            catch( const std::exception& ex ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Session::prepare() [Message: %s]" ) % ex.what()).str() );

               setBuffer( failed( ex.what() ) );
            }
            catch( ... ) {
               Utility::Memmory::Singleton< Utility::Logger >::instance()
                  .error( (boost::format( "Session::prepare() [Message: %s]" ) % "Critical error!").str() );

               setBuffer( failed( "Critical error!" ) );
            }
         }

         std::string __stdcall failed( message_type t ) const {
            property_base_type status;
            status.put( "status", "failed" );

            property_base_type reason;
            reason.put( "reason", t );

            property_base_type failed;
            merge( status, failed );
            merge( reason, failed );

            return boost::lexical_cast< std::string >( failed );
         }

         void __stdcall merge( property_source_type source, property_destination_type dest ) const {
            for( property_value_type item : source ) {
               dest.put_child( item.first, item.second );
            }
         }

      private:
         enum { BUFFER_LENGTH = 64 * 1024 };

         socket_base_type socket_;
         buffer_base_type buffer_;
         chain_base_type chain_;
      };

      class Server:
         private boost::noncopyable {
      public:
         typedef typename Utility::Traits< std::string >::base_t port_type;
         typedef typename Utility::Traits< Session::session_base_type >::const_reference_t session_type;

         typedef typename Utility::Traits< boost::shared_ptr< boost::asio::io_context > >::base_t context_base_type;
         typedef typename Utility::Traits< boost::shared_ptr< boost::asio::ip::tcp::acceptor > >::base_t acceptor_base_type;

         typedef typename Utility::Traits< boost::shared_ptr< Chain::IOperationChain > >::const_reference_t chain_type;
         typedef typename Utility::Traits< boost::shared_ptr< Chain::IOperationChain > >::base_t chain_base_type;

         explicit Server( port_type port, chain_type chain ) :
            context_( Utility::make_shared_pool< boost::asio::io_context, boost::default_user_allocator_malloc_free >() ),
            acceptor_( Utility::make_shared_pool< boost::asio::ip::tcp::acceptor, boost::default_user_allocator_malloc_free >( *context_, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), boost::lexical_cast< unsigned short >( port ) ) ) ),
            chain_( chain ) {
            acceptor_->set_option( boost::asio::socket_base::keep_alive( true ) );
            acceptor_->set_option( boost::asio::socket_base::reuse_address( true ) );
            acceptor_->set_option( boost::asio::socket_base::enable_connection_aborted( true ) );

            start_accept();
         }

         void start_accept() {
            Session::session_base_type connection( Session::getInstance( acceptor_->get_executor().context(), chain_ ) );
            acceptor_->async_accept( connection->socket(),
                                     boost::bind( &Server::handle_accept,
                                                  this,
                                                  connection,
                                                  boost::asio::placeholders::error ) );
         }

         void handle_accept( session_type connection, const boost::system::error_code& error ) {
            if( !error ) {
               connection->start();
            }

            start_accept();
         }

         void run() const {
            context_->run();
         }

         void stop() const {
            acceptor_->cancel();
            context_->stop();
         }

      private:
         context_base_type context_;
         acceptor_base_type acceptor_;
         chain_base_type chain_;
      };
   }
}

#pragma pack( pop )

#endif //__MANAGER_SERVER_H_INCLUDED__
