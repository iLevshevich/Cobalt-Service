#ifndef __TCP_PUBLISH_H_INCLUDED__
#define __TCP_PUBLISH_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace EntryPoint
   {
      class Publish :
         public IPublish,
         private boost::noncopyable {
      public:
         typedef typename IPublish::executor_type executor_type;

         static boost::shared_ptr< IPublish > getInstance( const boost::shared_ptr< Utility::ISettings >& settings );

         virtual void publish( executor_type executor ) override;
         virtual void quit() override;
         virtual bool tryQuit() override;
         virtual bool isQuited() override;

         virtual ~Publish() = default;
      protected:
         explicit Publish( const boost::shared_ptr< Utility::ISettings >& settings );

         enum { TRY_QUIT_TIMEOUT = 10 };
         void __fastcall wait( size_t ) const;
      private:
         boost::shared_ptr< Utility::ISettings > settings_;
         boost::shared_ptr< Tcp::BlockClient > handler_;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_PUBLISH_H_INCLUDED__
