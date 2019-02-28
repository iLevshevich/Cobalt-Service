#ifndef __SERVICE_SINGLETON_H_INCLUDED__
#define __SERVICE_SINGLETON_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#pragma pack( push, 8 )

namespace Cobalt
{
   template< class T >
   class Singleton :
      private boost::noncopyable {
   public:
      static T& instance() {
         static T instance;
         return instance;
      }
   };
}

#pragma pack( pop )

#endif //__SERVICE_SINGLETON_H_INCLUDED__
