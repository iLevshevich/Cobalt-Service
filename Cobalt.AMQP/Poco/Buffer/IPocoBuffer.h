#ifndef __AMQP_I_POCO_BUFFER_H_INCLUDED__
#define __AMQP_I_POCO_BUFFER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Poco
   {
      namespace Buffer
      {
#pragma warning(disable:4348) //C4348 переопределение параметра по умолчанию
         template< class _Elem = char, class _Traits = Cobalt::Utility::CharTraits< _Elem > >
         class IPocoBuffer {
         public:
            typedef typename _Traits::pointer_const_t pointer_const_t;

            virtual size_t __stdcall setDataInput( pointer_const_t data, const size_t size ) = 0;
            virtual size_t __stdcall setDataOutput( pointer_const_t data, const size_t size ) = 0;

            virtual void __stdcall cutDataInput( const size_t count ) = 0;
            virtual void __stdcall cutDataOutput( const size_t count ) = 0;

            virtual pointer_const_t getDataInput() = 0;
            virtual pointer_const_t getDataOutput() = 0;

            virtual void resetInput() = 0;
            virtual void resetOutput() = 0;

            virtual size_t getAvailableInput() const = 0;
            virtual size_t getAvailableOutput() const = 0;

            virtual bool isAvailableInput() const = 0;
            virtual bool isAvailableOutput() const = 0;

            virtual ~IPocoBuffer() = default;
         };
#pragma warning(default:4348)

         typedef IPocoBuffer< > ICharPocoBuffer;
      }
   }
}
#pragma pack( pop )

#endif //__AMQP_I_POCO_BUFFER_H_INCLUDED__
