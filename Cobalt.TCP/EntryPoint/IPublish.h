#ifndef __TCP_I_PUBLISH_H_INCLUDED__
#define __TCP_I_PUBLISH_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace EntryPoint
   {
      class IPublish {
      public:
         typedef typename Utility::Traits< std::function< std::string() > >::const_rvalue_reference_t executor_type;

         virtual void publish( executor_type executor ) = 0;
         virtual void quit() = 0;
         virtual bool tryQuit() = 0;
         virtual bool isQuited() = 0;

         virtual ~IPublish() = default;
      };
   }
}

#pragma pack( pop )

#endif //__TCP_I_PUBLISH_H_INCLUDED__
