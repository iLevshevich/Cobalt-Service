#ifndef __TCP_BLOCK_SERVER_H_INCLUDED__
#define __TCP_BLOCK_SERVER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Tcp
   {
      class BlockServer {
      public:
         typedef typename Utility::Traits< std::function< void( const std::string&& ) > >::const_rvalue_reference_t executor_type;
         typedef typename Utility::Traits< std::string >::base_t port_type;
         typedef typename Utility::Traits< Memmory::Buffer< char > >::base_t buffer_base_type;
         typedef typename Utility::Traits< boost::shared_ptr< boost::asio::ip::tcp::socket > >::base_t socket_base_type;

         explicit BlockServer( port_type port );

         void run( executor_type executor );
         void stop();
         bool isStopped() const;

         void quit();
         bool isQuited() const;

         virtual ~BlockServer();

      private:
         enum { BUFFER_LENGTH = 64 * 1024 };
         enum { TIMEOUT = 1000 }; //millisec

         boost::shared_ptr< boost::asio::io_context > context_;
         boost::shared_ptr< boost::asio::ip::tcp::acceptor > acceptor_;

         boost::atomic_bool quit_;
      };
   }
}

#pragma pack( pop )

#endif //__TCP_BLOCK_SERVER_H_INCLUDED__
