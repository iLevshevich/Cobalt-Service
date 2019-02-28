#ifndef __MANAGER_PERFORMANCE_HANDLER_H_INCLUDED__
#define __MANAGER_PERFORMANCE_HANDLER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Handler
   {
      namespace Performance
      {
         template< PerformanceHandlerType _Ty >
         class PerformanceHandler:
            public IPerformanceHandler {
         public:
			typedef typename IPerformanceHandler::hash_arg_type hash_arg_type;
            typedef typename IPerformanceHandler::property_tree_base_type property_tree_base_type;

            typedef typename Utility::Traits< boost::mutex >::base_t mutex_base_type;
            typedef typename Utility::Traits< std::list< std::pair< std::string, boost::posix_time::ptime > > >::base_t container_base_type;
            typedef typename Utility::Traits< boost::posix_time::time_duration >::base_t counter_base_type;
			typedef typename Utility::Traits< std::string >::base_t hash_return_type;

            static boost::shared_ptr< IPerformanceHandler > getInstance() {
               return Utility::make_shared_pool_enable< IPerformanceHandler, PerformanceHandler< _Ty >, boost::default_user_allocator_malloc_free >();
            }

			virtual void __fastcall begin(hash_arg_type s) override {
				std::lock_guard< mutex_base_type > lock(mutex_);
				///
				const std::string hash = getHash(s);
				container_.emplace_front(std::move(std::make_pair(hash, boost::posix_time::microsec_clock::local_time())));
			}

			virtual void __fastcall end(hash_arg_type s) override {
				std::lock_guard< mutex_base_type > lock(mutex_);
				///
				const std::string hash = getHash(s);
				const std::list< std::pair< std::string, boost::posix_time::ptime > >::const_iterator iter =
					std::find_if(std::begin(container_), std::end(container_), [&](const std::pair< std::string, boost::posix_time::ptime >& v) { return hash == v.first; });
				if (iter != std::end(container_)) {
					counter_ = boost::posix_time::microsec_clock::local_time() - iter->second;
					{
						container_.erase(iter);
					}
				}
			}

            virtual property_tree_base_type getLastPerform() override {
               return getPerform< _Ty >();
            }

			virtual void __fastcall cleanLastPerform(hash_arg_type s) override {
				std::lock_guard< mutex_base_type > lock(mutex_);
				///
				{
					const boost::posix_time::ptime now(boost::posix_time::microsec_clock::local_time());
					counter_ = now - now;
				}
				///
				const std::string hash = getHash(s);
				const std::list< std::pair< std::string, boost::posix_time::ptime > >::const_iterator iter =
					std::find_if(std::begin(container_), std::end(container_), [&](const std::pair< std::string, boost::posix_time::ptime >& v) { return hash == v.first; });
				if (iter != std::end(container_)) {
					container_.erase(iter);
				}
			}

            virtual ~PerformanceHandler() = default;

         protected:
            PerformanceHandler():
               mutex_(),
               counter_(),
               container_() {
            }

            template< PerformanceHandlerType _Type, typename std::enable_if< _Type == PerformanceHandlerType::seconds >::type * = nullptr >
            property_tree_base_type getPerform() {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               boost::property_tree::ptree result;
               ///
               result.put( "performance.total", counter_.total_seconds() );
               result.put( "performance.type", PerformanceHandlerTypeToString( PerformanceHandlerType::seconds ) );
               ///
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

            template< PerformanceHandlerType _Type, typename std::enable_if< _Type == PerformanceHandlerType::milliseconds >::type * = nullptr >
            property_tree_base_type getPerform() {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               boost::property_tree::ptree result;
               ///
               result.put( "performance.total", counter_.total_milliseconds() );
               result.put( "performance.type", PerformanceHandlerTypeToString( PerformanceHandlerType::milliseconds ) );
               ///
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

            template< PerformanceHandlerType _Type, typename std::enable_if< _Type == PerformanceHandlerType::microseconds >::type * = nullptr >
            property_tree_base_type getPerform() {
               std::lock_guard< mutex_base_type > lock( mutex_ );
               ///
               boost::property_tree::ptree result;
               ///
               result.put( "performance.total", counter_.total_microseconds() );
               result.put( "performance.type", PerformanceHandlerTypeToString( PerformanceHandlerType::microseconds ) );
               ///
               return Utility::make_shared_pool< boost::property_tree::ptree, boost::default_user_allocator_malloc_free >( result );
            }

         private:
            mutex_base_type mutex_;
            counter_base_type counter_;
            container_base_type container_;

			hash_return_type __fastcall getHash(hash_arg_type s) {
				boost::uuids::detail::sha1 algorithm;
				{
					algorithm.process_bytes(s.c_str(), s.size());
				}

				unsigned int digest[5];
				{
					algorithm.get_digest(digest);
				}

				std::ostringstream result;
				{
					for (int i = 0; i < 5; ++i) {
						result
							<< std::hex
							<< std::setfill('0')
							<< std::setw(8)
							<< digest[i];
					}
				}
				return result.str();
			}
         };
      }
   }
}

#pragma pack( pop )

#endif //__MANAGER_PERFORMANCE_HANDLER_H_INCLUDED__
