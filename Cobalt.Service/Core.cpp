#include "stdafx.h"

#include "LexicalCast.h"
#include "Options.h"
#include "Singleton.h"
#include "Core.h"

namespace Cobalt
{
   Core::Core():
      lib_( Singleton< Options >::instance().get( Options::DLL_MANAGER_PATH ) ),
      init_( boost::dll::import_alias< init >( lib_, "init", boost::dll::load_mode::append_decorations ) ),
      run_( boost::dll::import_alias< run >( lib_, "run", boost::dll::load_mode::append_decorations ) ),
      stop_( boost::dll::import_alias< stop >( lib_, "stop", boost::dll::load_mode::append_decorations ) ) {
      try {
         int argc( 0 );
         const boost::shared_ptr< char*[] > argv( commandLineToArgvA( GetCommandLineA(), &argc ), [](void* const ptr) {
                                                     if( ptr ) LocalFree( ptr );
                                                  } );
         if( !argv.get() ) {
            throw std::runtime_error( (boost::format( "Unable to parse command line %s" ) % boost::system::system_error( GetLastError(), boost::system::system_category() ).what()).str() );
         }

         init_( argc, argv );
      }
      catch( const std::exception& ex ) {
         toErrorEventLog( boost::lexical_cast< std::wstring, std::string >( (boost::format( "Core::Core()[Message: %s]" ) % ex.what()).str() ) );
      }
      catch( ... ) {
         toErrorEventLog( boost::lexical_cast< std::wstring, std::string >( (boost::format( "Core::Core()[Message: %s]" ) % "Critical error!").str() ) );
      }
   }

   void Core::Run() noexcept {
      try {
         guard_.create_thread( run_ )->detach();
      }
      catch( const std::exception& ex ) {
         toErrorEventLog( boost::lexical_cast< std::wstring, std::string >( (boost::format( "Core::Run()[Message: %s]" ) % ex.what()).str() ) );
      }
      catch( ... ) {
         toErrorEventLog( boost::lexical_cast< std::wstring, std::string >( (boost::format( "Core::Run()[Message: %s]" ) % "Critical error!").str() ) );
      }
   }

   void Core::Stop() noexcept {
      try {
         stop_();
      }
      catch( const std::exception& ex ) {
         toErrorEventLog( boost::lexical_cast< std::wstring, std::string >( (boost::format( "Core::Stop()[Message: %s]" ) % ex.what()).str() ) );
      }
      catch( ... ) {
         toErrorEventLog( boost::lexical_cast< std::wstring, std::string >( (boost::format( "Core::Stop()[Message: %s]" ) % "Critical error!").str() ) );
      }
   }

   Core::~Core() {
      try {
         guard_.interrupt_all();
         guard_.join_all();
      }
      catch( const std::exception& ex ) {
         toErrorEventLog( boost::lexical_cast< std::wstring, std::string >( (boost::format( "Core::~Core()[Message: %s]" ) % ex.what()).str() ) );
      }
      catch( ... ) {
         toErrorEventLog( boost::lexical_cast< std::wstring, std::string >( (boost::format( "Core::~Core()[Message: %s]" ) % "Critical error!").str() ) );
      }
   }

   PCHAR* __fastcall Core::commandLineToArgvA( PCHAR CmdLine, int* _argc ) {
      PCHAR* argv;
      PCHAR _argv;
      ULONG len;
      ULONG argc;
      CHAR a;
      ULONG i, j;

      BOOLEAN in_QM;
      BOOLEAN in_TEXT;
      BOOLEAN in_SPACE;

      len = strlen( CmdLine );
      i = ((len + 2) / 2) * sizeof(PVOID) + sizeof(PVOID);

      argv = (PCHAR*)GlobalAlloc( GMEM_FIXED, i + (len + 2) * sizeof(CHAR) );
      _argv = (PCHAR)(((PUCHAR)argv) + i);

      argc = 0;
      argv[argc] = _argv;
      in_QM = FALSE;
      in_TEXT = FALSE;
      in_SPACE = TRUE;
      i = 0;
      j = 0;

      while( a = CmdLine[i] ) {
         if( in_QM ) {
            if( a == '\"' ) {
               in_QM = FALSE;
            }
            else {
               _argv[j] = a;
               j++;
            }
         }
         else {
            switch( a ) {
            case '\"':
               in_QM = TRUE;
               in_TEXT = TRUE;
               if( in_SPACE ) {
                  argv[argc] = _argv + j;
                  argc++;
               }
               in_SPACE = FALSE;
               break;
            case ' ':
            case '\t':
            case '\n':
            case '\r':
               if( in_TEXT ) {
                  _argv[j] = '\0';
                  j++;
               }
               in_TEXT = FALSE;
               in_SPACE = TRUE;
               break;
            default:
               in_TEXT = TRUE;
               if( in_SPACE ) {
                  argv[argc] = _argv + j;
                  argc++;
               }
               _argv[j] = a;
               j++;
               in_SPACE = FALSE;
               break;
            }
         }
         i++;
      }
      _argv[j] = '\0';
      argv[argc] = NULL;

      (*_argc) = argc;
      return argv;
   }

   void __fastcall Core::toErrorEventLog( const std::wstring& error_message ) {
      LPWSTR message[1] = {const_cast< LPWSTR >(error_message.c_str())};
      const std::size_t count_strings( 1 );

      boost::shared_ptr< void > event_log( RegisterEventSource( NULL, __MODULE_NAME__ ), [](void* const ptr) {
                                                                 if( ptr ) DeregisterEventSource( ptr );
                                                              } );
      if( !event_log.get() ) {
         throw std::runtime_error( (boost::format( "RegisterEventSource failed with %s" ) % boost::system::system_error( GetLastError(), boost::system::system_category() ).what()).str() );
      }

      if( !ReportEvent( event_log.get(),
                        EVENTLOG_ERROR_TYPE,
                        NULL,
                        NULL,
                        NULL,
                        count_strings,
                        0,
                        reinterpret_cast< LPCWSTR* >(const_cast< LPCWSTR* >(message)),
                        NULL ) ) {
         throw std::runtime_error( (boost::format( "ReportEvent failed with %s" ) % boost::system::system_error( GetLastError(), boost::system::system_category() ).what()).str() );
      }
   }
}
