#include "../../stdafx.h"

#include "../../Utility/Traits.h"
#include "../../Utility/MakeAsync.h"
#include "../../Utility/MakeObject.h"

#include "../../Memmory/Buffer.h"

#include "BlockServer.h"

namespace Cobalt
{
   namespace Tcp
   {
      BlockServer::BlockServer( port_type port ) :
         context_( Utility::make_shared_pool< boost::asio::io_context >() ),
         acceptor_( Utility::make_shared_pool< boost::asio::ip::tcp::acceptor >( *context_, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), boost::lexical_cast< unsigned short >( port ) ) ) ),
         quit_( false ) {
         acceptor_->set_option( boost::asio::socket_base::keep_alive( true ) );
         acceptor_->set_option( boost::asio::socket_base::reuse_address( true ) );
         acceptor_->set_option( boost::asio::socket_base::enable_connection_aborted( true ) );
      }

      void BlockServer::run( executor_type executor ) {
         try {
            COBALT_HANDLER_STATE_GUARD( isQuited() )

            while( !isQuited() ) {
               socket_base_type socket( Utility::make_shared_pool< boost::asio::ip::tcp::socket, boost::default_user_allocator_malloc_free >( acceptor_->accept() ) );
               Utility::make_async( [socket, &executor]() {
                     const buffer_base_type buffer( BUFFER_LENGTH );
                     boost::system::error_code error;

                     socket->read_some( boost::asio::buffer( buffer.get(), buffer.size() ), error );
                     if( error && error != boost::asio::error::eof ) {
                        throw boost::system::system_error( error );
                     }

                     executor( std::move( std::string( buffer.get(), std::min( strlen( buffer.get() ), buffer.size() ) ) ) );
                  } );
            }
         }
         catch( const boost::system::system_error& se ) {
            if( se.code() != boost::asio::error::interrupted ) {
               throw std::logic_error( se.what() );
            }
         }
         catch( const std::exception& ex ) {
            throw std::logic_error( ex.what() );
         }
      }

      void BlockServer::stop() {
         acceptor_->cancel();
         context_->stop();
      }

      bool BlockServer::isStopped() const {
         return context_->stopped();
      }

      void BlockServer::quit() {
         quit_.store( true );
      }

      bool BlockServer::isQuited() const {
         return quit_.load() == true;
      }

      BlockServer::~BlockServer() {
      }
   }
}
