#ifndef __AMQP_POCO_BUFFER_H_INCLUDED__
#define __AMQP_POCO_BUFFER_H_INCLUDED__

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
         class PocoBuffer:
            public ICharPocoBuffer,
            private boost::noncopyable {
         public:
            PocoBuffer();

            virtual size_t __stdcall setDataInput( pointer_const_t data, const size_t size ) override;
            virtual size_t __stdcall setDataOutput( pointer_const_t data, const size_t size ) override;

            virtual void __stdcall cutDataInput( const size_t count ) override;
            virtual void __stdcall cutDataOutput( const size_t count ) override;

            virtual pointer_const_t getDataInput() override;
            virtual pointer_const_t getDataOutput() override;

            virtual void resetInput() override;
            virtual void resetOutput() override;

            virtual size_t getAvailableInput() const override;
            virtual size_t getAvailableOutput() const override;

            virtual bool isAvailableInput() const override;
            virtual bool isAvailableOutput() const override;

            virtual ~PocoBuffer() = default;

         private:
            enum { INPUT_BUFFER_SIZE = 1024 * 1024 }; //recomendation -> 8Mb
            enum { OUTPUT_BUFFER_SIZE = 2 * 1024 * 1024 }; //recomendation -> 8Mb

            boost::shared_ptr< Cobalt::Memmory::CharBuffer > inputBuffer;
            boost::shared_ptr< Cobalt::Memmory::CharBuffer > outputBuffer;
         };
      }
   }
}
#pragma pack( pop )

#endif //__AMQP_POCO_BUFFER_H_INCLUDED__
