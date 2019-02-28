#ifndef __TCP_CONSUME_H_INCLUDED__
#define __TCP_CONSUME_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace EntryPoint
   {
      class Consume :
         public IConsume,
         private boost::noncopyable {
      public:
         typedef typename IConsume::executor_type executor_type;

         static boost::shared_ptr< IConsume > getInstance( const boost::shared_ptr< Utility::ISettings >& settings );

         virtual void consume( executor_type executor ) override;
         virtual void quit() override;
         virtual bool tryQuit() override;
         virtual bool isQuited() override;

         virtual ~Consume() = default;

      protected:
         explicit Consume( const boost::shared_ptr< Utility::ISettings >& settings );

         enum { TRY_QUIT_TIMEOUT = 10 };
         void __fastcall wait( size_t ) const;
      private:
         boost::shared_ptr< Utility::ISettings > settings_;
         boost::shared_ptr< Tcp::BlockServer > handler_;
      };
   }
}

#pragma pack( pop )

#endif //__TCP_CONSUME_H_INCLUDED__
