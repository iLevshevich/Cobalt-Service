#include "../../stdafx.h"

#include "IConnection.h"
#include "Connection.h"

namespace Cobalt
{
   namespace Poco
   {
      namespace Connection
      {
         Connection::Connection():
            connected_( false ),
            connection_( nullptr ) {
         }

         bool Connection::isAvailable() const {
            return connection_ != nullptr;
         }

         bool Connection::isConnected() const {
            return connected_;
         }

         void __stdcall Connection::setConnected(const bool connected) {
            connected_ = connected;
         }

#pragma warning(disable:4244) //C4244 преобразование "uint64_t" в "std::size_t", возможна потеря данных
         size_t __stdcall Connection::parseDate( const char* buffer, const size_t size ) {
            return connection_->parse( buffer, size );
         }
#pragma warning(default:4244)

         void Connection::setConnection( AMQP::Connection* const connection ) {
            connection_ = connection;
         }

		 bool Connection::closeConnection() {
			return connection_->close();
		 }
      }
   }
}
