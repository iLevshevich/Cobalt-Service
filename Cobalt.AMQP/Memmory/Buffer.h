#ifndef __AMQP_BUFFER_H_INCLUDED__
#define __AMQP_BUFFER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Memmory
   {
#pragma warning(disable:4348) //C4348 переопределение параметра по умолчанию
      template< class _Elem = char, class _Traits = Cobalt::Utility::CharTraits< _Elem > >
      class Buffer :
         private boost::noncopyable {
      public:
         explicit Buffer( const size_t size ) :
            use_( 0 ),
            data_( size, 0 ) {
         }

         size_t __stdcall setData( typename _Traits::pointer_const_t data, const size_t size ) {
            if( use_ == data_.size() ) {
               return 0;
            }

            const size_t length = (size + use_);
            const size_t write = length < data_.size() ? size : data_.size() - use_; {
               memcpy( data_.data() + use_, data, write );
            }
            use_ += write;
            return write;
         }

         void __stdcall cutData(const size_t count) {
            const size_t diff = use_ - count;
            memmove(data_.data(), data_.data() + count, diff);
            use_ = use_ - count;
         }

         typename _Traits::pointer_const_t getData() const {
            return data_.data();
         }

         void reset() {
            use_ = 0;
         }

         size_t getAvailable() const {
            return use_;
         }

         bool isAvailable() const {
            return use_ != 0;
         }
      private:
         size_t use_;
         std::vector< typename _Traits::base_t > data_;
      };
#pragma warning(default:4348)

      typedef Buffer< > CharBuffer;
   }
}

#pragma pack( pop )

#endif //__AMQP_BUFFER_H_INCLUDED__
