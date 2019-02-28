#ifndef __TCP_BLOCK_CLIENT_H_INCLUDED__
#define __TCP_BLOCK_CLIENT_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Tcp
   {
      class BlockClient {
      public:
         typedef typename Utility::Traits< std::function< std::string() > >::const_rvalue_reference_t executor_type;
         typedef typename Utility::Traits< std::string >::const_reference_t host_type;
         typedef typename Utility::Traits< std::string >::base_t port_type;

         explicit BlockClient( host_type host, port_type port );

         void run( executor_type executor );
         void stop();
         bool isStopped() const;

         void quit();
         bool isQuited() const;

         virtual ~BlockClient() = default;

      private:
         boost::shared_ptr< boost::asio::io_context > context_;
         std::string host_;
         std::string port_;

         boost::atomic_bool quit_;
      };
   }
}

#pragma pack( pop )

#endif //__TCP_BLOCK_CLIENT_H_INCLUDED__
