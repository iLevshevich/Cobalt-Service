#include "stdafx.h"

#include "Options.h"

namespace Cobalt
{
   const std::string Options::DLL_AMQP_PATH = {"dll.amqp-path"};
   const std::string Options::DLL_TCP_PATH = {"dll.tcp-path"};
   const std::string Options::DLL_MANAGER_PATH = {"dll.manager-path"};
   const std::string Options::LOG_FILE_PATH = {"log.file-path"};
   const std::string Options::LOG_MAX_FILES = {"log.max-files"};
   const std::string Options::LOG_ROTATION_SIZE = {"log.rotation-size"};
   const std::string Options::LOG_MIN_FREE_SPACE = {"log.min-free-space"};
   const std::string Options::DISPATCHERS_FILE_PATH = {"dispatchers.file-path"};
   const std::string Options::MANAGEMENT_SERVER_PORT = {"management.server-port"};
   const std::string Options::SECURITY_WHITE_LIST = {"security.white-list"};

   void __fastcall Options::init( int argc, char* argv[] ) {
      boost::program_options::options_description desc( "Cobalt.Service options" );
      desc.add_options()
         ( "settings-file,O", boost::program_options::value< std::string >()->required() )
         ( DLL_AMQP_PATH.c_str(), boost::program_options::value< std::string >()->required() )
         ( DLL_TCP_PATH.c_str(), boost::program_options::value< std::string >()->required() )
         ( DLL_MANAGER_PATH.c_str(), boost::program_options::value< std::string >()->required() )
         ( LOG_FILE_PATH.c_str(), boost::program_options::value< std::string >()->required() )
         ( LOG_MAX_FILES.c_str(), boost::program_options::value< std::string >()->required()->default_value( "10" ) )
         ( LOG_ROTATION_SIZE.c_str(), boost::program_options::value< std::string >()->required()->default_value( "10485760" ) ) //10 * 1024 * 1024
         ( LOG_MIN_FREE_SPACE.c_str(), boost::program_options::value< std::string >()->required()->default_value( "104857600" ) ) //100 * 1024 * 1024
         ( MANAGEMENT_SERVER_PORT.c_str(), boost::program_options::value< std::string >()->required()->default_value( "15000" ) )
         ( SECURITY_WHITE_LIST.c_str(), boost::program_options::value< std::string >()->required() )
         ( DISPATCHERS_FILE_PATH.c_str(), boost::program_options::value< std::string >()->required() );

      boost::program_options::store( boost::program_options::parse_command_line( argc, argv, desc ), vm );
      boost::program_options::store( boost::program_options::parse_config_file< char >( get( "settings-file" ).c_str(), desc ), vm );
      boost::program_options::notify( vm );
   }

   std::string __fastcall Options::get( const std::string& key ) const {
      return vm[key].as< std::string >();
   }
}
