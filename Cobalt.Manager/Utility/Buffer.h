#ifndef __MANAGER_BUFFER_H_INCLUDED__
#define __MANAGER_BUFFER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      namespace Memmory
      {
         template< class _Elem >
         class Buffer :
            private boost::noncopyable {
         public:
            typedef typename Utility::Traits< _Elem >::base_t base_type;
            typedef typename Utility::Traits< _Elem >::pointer_t pointer_type;

            explicit Buffer( const size_t size ) :
               buffer_( new base_type[size] ),
               size_( size ) {
               clean();
            }

            pointer_type get() const {
               return buffer_.get();
            }

            size_t size() const {
               return size_;
            }

            void clean() {
               memset( buffer_.get(), 0, size_ );
            }

			void __stdcall reset( const size_t size ) {
				buffer_.reset( new base_type[size] );
				///
				{
					size_ = size;
				}
				///
				clean();
			}

         private:
            boost::shared_array< base_type > buffer_;
            size_t size_;
         };
      }
   }
}
#pragma pack( pop )

#endif //__MANAGER_BUFFER_H_INCLUDED__
