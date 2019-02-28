#ifndef __SERVICE_OPTIONS_H_INCLUDED__
#define __SERVICE_OPTIONS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#pragma pack( push, 8 )

namespace Cobalt
{
   class Options :
      private boost::noncopyable {
   public:
      const static std::string DLL_AMQP_PATH;
      const static std::string DLL_TCP_PATH;
      const static std::string DLL_MANAGER_PATH;
      const static std::string LOG_FILE_PATH;
      const static std::string LOG_MAX_FILES;
      const static std::string LOG_ROTATION_SIZE;
      const static std::string LOG_MIN_FREE_SPACE;
      const static std::string DISPATCHERS_FILE_PATH;
      const static std::string MANAGEMENT_SERVER_PORT;
      const static std::string SECURITY_WHITE_LIST;

      void __fastcall init( int argc, char* argv[] );
      std::string __fastcall get( const std::string& key ) const;

   private:
      boost::program_options::variables_map vm;
   };
}

#pragma pack( pop )

#endif //__SERVICE_OPTIONS_H_INCLUDED__
