#include "../../stdafx.h"
#include "../../Utility/Traits.h"
#include "../../Memmory/Buffer.h"

#include "BlockClient.h"

namespace Cobalt
{
   namespace Tcp
   {
      BlockClient::BlockClient( host_type host, port_type port ) :
         context_( Utility::make_shared_pool< boost::asio::io_context >() ),
         host_( host ),
         port_( port ),
         quit_( false ) {
      }

      void BlockClient::run( executor_type executor ) {
         try {
            boost::asio::ip::tcp::socket socket( *context_ );
            boost::asio::ip::tcp::resolver resolver( *context_ );
            boost::asio::ip::tcp::resolver::results_type endpoints( resolver.resolve( host_, port_ ) );
            boost::asio::connect( socket, endpoints );
            boost::system::error_code error;

            boost::asio::write( socket,
                                boost::asio::buffer( executor() ),
                                boost::asio::transfer_all(),
                                error );
            if( error && error != boost::asio::error::eof ) {
               throw boost::system::system_error( error );
            }
         }
         catch( const std::exception& ex ) {
            throw std::logic_error( ex.what() );
         }
      }

      void BlockClient::stop() {
         context_->stop();
      }

      bool BlockClient::isStopped() const {
         return context_->stopped();
      }

      void BlockClient::quit() {
         quit_.store( true );
      }

      bool BlockClient::isQuited() const {
         return quit_.load() == true;
      }
   }
}
