#ifndef __AMQP_POCO_HANDLER_H_INCLUDED__
#define __AMQP_POCO_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Poco
   {
      class PocoHandler :
         public AMQP::ConnectionHandler,
         private boost::noncopyable {
      public:
         explicit PocoHandler( const std::string& host, const uint16_t port );
         explicit PocoHandler( const boost::shared_ptr< Utility::IHostSettings >& host );
         virtual ~PocoHandler();

         void loop();
         void quit();
         bool tryQuit() const;
         bool isQuited() const;
         bool connected() const;
      private:
         virtual void onData( AMQP::Connection* connection, const char* buffer, size_t size ) override;
         virtual void onConnected( AMQP::Connection* connection ) override;
         virtual void onError( AMQP::Connection* connection, const char* message ) override;
         virtual void onClosed( AMQP::Connection* connection ) override;

         void __stdcall loop( const std::function< void() >& receiveData,
                              const std::function< void() >& checkData,
                              const std::function< void() >& prepareData,
                              const std::function< void() >& sendData,
                              const std::function< void() >& completeData ) const;

         enum { LOOP_SLEEP_TIMEOUT = 10 }; //milliseconds
         inline void loopSleep() const;
         inline void receiveData();
         inline void checkData() const;
         inline void prepareData() const;
         inline void sendData() const;
         inline void completeData() const;
         inline void close() const;
		 inline void closeSocket() const;
		 inline void closeConnection() const;
         inline bool isDataAvailable() const;

         boost::shared_ptr< Cobalt::Poco::Connection::IConnection > connection_;
         boost::shared_ptr< Cobalt::Poco::Socket::IPocoSocket > socket_;
         boost::shared_ptr< Cobalt::Poco::Buffer::IPocoBuffer< > > buffer_;

         enum { TEMP_BUFFER_SIZE = 1024 * 1024 }; //1Mb
         std::vector< char > temp_buffer_;

         boost::atomic_bool quit_;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_POCO_HANDLER_H_INCLUDED__
