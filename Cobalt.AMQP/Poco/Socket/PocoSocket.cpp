#include "../../stdafx.h"

#include "../../Utility/MakeObject.h"

#include "ISocket.h"
#include "IPocoSocket.h"
#include "PocoSocket.h"

namespace Cobalt
{
   namespace Poco
   {
      namespace Socket
      {
         PocoSocket::PocoSocket() :
            socket_( Utility::make_shared_pool< ::Poco::Net::StreamSocket >() ) {
         }

         void PocoSocket::connect( const std::string& host, const uint16_t port ) {
            socket_->connect( ::Poco::Net::SocketAddress( host, port ) );
         }

         int PocoSocket::receiveBytes( void* buffer, int length, int flags ) {
            return socket_->receiveBytes( buffer, length, flags );
         }

         int PocoSocket::sendBytes( const void* buffer, int length, int flags ) {
            return socket_->sendBytes( buffer, length, flags );
         }

         void PocoSocket::setLinger( bool on, int seconds ) {
            socket_->setLinger( on, seconds );
         }

         void PocoSocket::setNoDelay( bool flag ) {
            socket_->setNoDelay( flag );
         }

         void PocoSocket::setKeepAlive( bool flag ) {
            socket_->setKeepAlive( flag );
         }

         void PocoSocket::setReuseAddress( bool flag ) {
            socket_->setReuseAddress( flag );
         }

         void PocoSocket::setReusePort( bool flag ) {
            socket_->setReusePort( flag );
         }

         void PocoSocket::setOOBInline( bool flag ) {
            socket_->setOOBInline( flag );
         }

         void PocoSocket::setBlocking( bool flag ) {
            socket_->setBlocking( flag );
         }

         int PocoSocket::getAvailable() const {
            return socket_->available();
         }

         bool PocoSocket::isAvailable() const {
            return socket_->available() > 0;
         }

         bool PocoSocket::isValid() const {
            return !isInvalid();
         }

         bool PocoSocket::isInvalid() const {
            return socket_->available() < 0;
         }

         void PocoSocket::close() {
            socket_->close();
         }
      }
   }
}
