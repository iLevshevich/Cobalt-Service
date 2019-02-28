#ifndef __LOGGER_H_INCLUDED__
#define __LOGGER_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class Logger :
         private boost::noncopyable {
      public:
         typedef typename Utility::Traits< boost::shared_ptr< boost::log::sources::severity_logger< boost::log::trivial::severity_level > > >::base_t logger_type;
         typedef typename Utility::Traits< std::string >::const_reference_t message_type;

         Logger():
            logger_( Utility::make_shared_pool< boost::log::sources::severity_logger< boost::log::trivial::severity_level >, boost::default_user_allocator_malloc_free >() ) {
         }

         void __fastcall init() const {
            const Options& options( Memmory::Singleton< Options >::instance() );
            boost::log::add_file_log
            (
               boost::log::keywords::file_name = (options.get( Options::LOG_FILE_PATH )),
               boost::log::keywords::open_mode = (std::ios::out | std::ios::app),
               boost::log::keywords::max_files = boost::lexical_cast< long >( options.get( Options::LOG_MAX_FILES ) ),
               boost::log::keywords::rotation_size = boost::lexical_cast< long >( options.get( Options::LOG_ROTATION_SIZE ) ),
               boost::log::keywords::min_free_space = boost::lexical_cast< long >( options.get( Options::LOG_MIN_FREE_SPACE ) ),
               // rotate at midnight every day
               boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point( 0, 0, 0 ),
               boost::log::keywords::auto_flush = true,
               boost::log::keywords::format =
               (
                  boost::log::expressions::stream
                  << boost::log::expressions::format_date_time< boost::posix_time::ptime >( "TimeStamp", "%d.%m.%Y %H:%M:%S.%f" )
                  << " [" << boost::log::trivial::severity << "]"
                  << " [PID:" << boost::log::expressions::attr< boost::log::attributes::current_process_id::value_type >( "ProcessID" ) << "]"
                  << " [TID:" << boost::log::expressions::attr< boost::log::attributes::current_thread_id::value_type >( "ThreadID" ) << "] "
                  << boost::log::expressions::smessage
               )
            );
            boost::log::add_common_attributes();
         }

         void __fastcall trace( message_type message ) const {
            BOOST_LOG_SEV(*logger_, boost::log::trivial::trace) << message.c_str();
         }

         void __fastcall debug( message_type message ) const {
            BOOST_LOG_SEV(*logger_, boost::log::trivial::debug) << message.c_str();
         }

         void __fastcall info( message_type message ) const {
            BOOST_LOG_SEV(*logger_, boost::log::trivial::info) << message.c_str();
         }

         void __fastcall warning( message_type message ) const {
            BOOST_LOG_SEV(*logger_, boost::log::trivial::warning) << message.c_str();
         }

         void __fastcall error( message_type message ) const {
            BOOST_LOG_SEV(*logger_, boost::log::trivial::error) << message.c_str();
         }

         void __fastcall fatal( message_type message ) const {
            BOOST_LOG_SEV(*logger_, boost::log::trivial::fatal) << message.c_str();
         }

      private:
         logger_type logger_;
      };
   }
}

#pragma pack( pop )

#endif //__LOGGER_H_INCLUDED__
