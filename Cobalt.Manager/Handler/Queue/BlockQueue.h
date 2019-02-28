#ifndef __MANAGER_BLOCK_QUEUE_H_INCLUDED__
#define __MANAGER_BLOCK_QUEUE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Queue
      {
         template< class T >
         class BlockQueue {
         public:
            typedef typename Utility::Traits< T >::base_t base_type;
            typedef typename Utility::Traits< base_type >::const_rvalue_reference_t arg_type;

            typedef typename Utility::Traits< std::queue< base_type > >::base_t queue_base_type;
            typedef typename Utility::Traits< boost::mutex >::base_t mutex_base_type;
            typedef typename Utility::Traits< boost::condition_variable >::base_t condition_base_type;

            BlockQueue() :
               queue_(),
               mutex_(),
               condition_() {
            }

            void __fastcall push( arg_type t ) {
               boost::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               {
                  queue_.push( std::move( t ) );
               }
               ///
               condition_.notify_one();
            }

            base_type pop() {
               boost::unique_lock< mutex_base_type > lock( mutex_ );
               ///
               while( queue_.empty() ) {
                  condition_.wait( lock );
               }
               const base_type val( queue_.front() );
               ///
               {
                  queue_.pop();
               }
               ///
               return val;
            }

            size_t size() {
               boost::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               return queue_.size();
            }

            bool isEmpty() {
               boost::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               return queue_.empty();
            }

         private:
            queue_base_type queue_;
            mutex_base_type mutex_;
            condition_base_type condition_;
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_BLOCK_QUEUE_H_INCLUDED__
