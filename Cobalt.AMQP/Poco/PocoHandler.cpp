#include "../stdafx.h"

#include "../Utility/Traits.h"
#include "../Utility/EnableMake.h"
#include "../Utility/Settings/Extra/IHostSettings.h"
#include "../Utility/Settings/Extra/HostSettings.h"
#include "../Utility/MakeObject.h"

#include "../Memmory/Buffer.h"

#include "Exception/PocoException.h"

#include "Socket/ISocket.h"
#include "Socket/IPocoSocket.h"
#include "Socket/PocoSocket.h"

#include "Buffer/IPocoBuffer.h"
#include "Buffer/PocoBuffer.h"

#include "Connection/IConnection.h"
#include "Connection/Connection.h"

#include "PocoHandler.h"

namespace Cobalt
{
   namespace Poco
   {
      PocoHandler::PocoHandler( const std::string& host, const uint16_t port ) :
         connection_( Utility::make_shared_pool< Connection::Connection, boost::default_user_allocator_malloc_free >() ),
         socket_( Utility::make_shared_pool< Socket::PocoSocket, boost::default_user_allocator_malloc_free >() ),
         buffer_( Utility::make_shared_pool< Buffer::PocoBuffer, boost::default_user_allocator_malloc_free >() ),
         temp_buffer_( TEMP_BUFFER_SIZE ),
         quit_( false ) {
         socket_->connect( host, port );
         socket_->setKeepAlive();
      }

      PocoHandler::PocoHandler( const boost::shared_ptr< Utility::IHostSettings >& host ) :
         connection_( Utility::make_shared_pool< Connection::Connection, boost::default_user_allocator_malloc_free >() ),
         socket_( Utility::make_shared_pool< Socket::PocoSocket, boost::default_user_allocator_malloc_free >() ),
         buffer_( Utility::make_shared_pool< Buffer::PocoBuffer, boost::default_user_allocator_malloc_free >() ),
         temp_buffer_( TEMP_BUFFER_SIZE ),
         quit_( false ) {
         socket_->connect( host->getHost(), host->getPort() );
         socket_->setKeepAlive();
      }

      PocoHandler::~PocoHandler() {
         close();
      }

      void PocoHandler::close() const {
		  closeSocket();
      }

	  void PocoHandler::closeSocket() const {
		  socket_->close();
	  }

	  void PocoHandler::closeConnection() const {
		  if (connected()) {
			  connection_->setConnected(false);
			  connection_->closeConnection();
		  }
	  }

      void PocoHandler::loop( const std::function< void() >& receiveData,
                              const std::function< void() >& checkData,
                              const std::function< void() >& prepareData,
                              const std::function< void() >& sendData,
                              const std::function< void() >& completeData ) const {
         try {
            while( !isQuited() ) {
               receiveData();
               checkData();
               prepareData();
               sendData();
               loopSleep();
            }
            completeData();
         }
         catch( const ::Poco::Exception& ex ) {
            throw SystemException( ex.message() );
         }
      }

      void PocoHandler::loop() {
         loop( std::bind( &PocoHandler::receiveData, this ),
               std::bind( &PocoHandler::checkData, this ),
               std::bind( &PocoHandler::prepareData, this ),
               std::bind( &PocoHandler::sendData, this ),
               std::bind( &PocoHandler::completeData, this ) );
      }

      void PocoHandler::loopSleep() const {
         if( !isDataAvailable() ) {
            std::this_thread::sleep_for( std::chrono::milliseconds( LOOP_SLEEP_TIMEOUT ) );
         }
      }

      void PocoHandler::receiveData() {
         if( socket_->isAvailable() ) {
            const size_t available = socket_->getAvailable();
            if( temp_buffer_.size() < available ) {
               temp_buffer_.resize( available, 0 );
            }

            socket_->receiveBytes( &temp_buffer_[0], available );
            buffer_->setDataInput( temp_buffer_.data(), available );
         }
      }

      void PocoHandler::checkData() const {
         if( socket_->isInvalid() ) {
            throw SocketException( "Invalid socket state" );
         }
      }

      void PocoHandler::prepareData() const {
         if( connection_->isAvailable() && buffer_->isAvailableInput() ) {
            const size_t count = connection_->parseDate( buffer_->getDataInput(), buffer_->getAvailableInput() );

            if( count == buffer_->getAvailableInput() ) {
               buffer_->resetInput();
            }
            else if( count > 0 ) {
               buffer_->cutDataInput( count );
            }
         }
      }

      void PocoHandler::sendData() const {
         if( buffer_->isAvailableOutput() ) {
            socket_->sendBytes( buffer_->getDataOutput(), buffer_->getAvailableOutput() );
            buffer_->resetOutput();
         }
      }

      void PocoHandler::completeData() const {
         if( isQuited() && buffer_->isAvailableOutput() ) {
            sendData();
         }
      }

      bool PocoHandler::tryQuit() const {
         return (!isQuited()) &&
            (!socket_->isAvailable()) &&
            (!buffer_->isAvailableInput()) &&
            (!buffer_->isAvailableOutput());
      }

      bool PocoHandler::isDataAvailable() const {
         return buffer_->isAvailableInput() ||
            buffer_->isAvailableOutput();
      }

      void PocoHandler::quit() {
         quit_.store( true );
      }

      bool PocoHandler::isQuited() const {
         return quit_.load() == true;
      }

      void PocoHandler::onData( AMQP::Connection* connection, const char* data, size_t size ) {
         connection_->setConnection( connection );

         const size_t writen = buffer_->setDataOutput( data, size );
         if( writen != size ) {
            ///
            {
               sendData();
            }
            ///
            buffer_->setDataOutput( data + writen, size - writen );
         }
      }

      void PocoHandler::onConnected( AMQP::Connection* connection ) {
         connection_->setConnected( true );
      }

      void PocoHandler::onError( AMQP::Connection* connection, const char* message ) {
         throw ::Poco::LogicException( message );
      }

      void PocoHandler::onClosed( AMQP::Connection* connection ) {
         quit();
      }

      bool PocoHandler::connected() const {
         return connection_->isConnected();
      }
   }
}
