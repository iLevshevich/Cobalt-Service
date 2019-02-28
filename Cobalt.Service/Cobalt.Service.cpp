#include "stdafx.h"

#include "LexicalCast.h"
#include "Options.h"
#include "Singleton.h"
#include "Core.h"
#include "ServiceModule.h"

Cobalt::ServiceModule _AtlModule;

extern "C" int WINAPI _tWinMain( HINSTANCE /*hInstance*/,
                                 HINSTANCE /*hPrevInstance*/,
                                 LPTSTR /*lpCmdLine*/,
                                 int nShowCmd ) throw() {
   try {
      Cobalt::Options& options( Cobalt::Singleton< Cobalt::Options >::instance() );
      ///
      {
         int argc( 0 );
         const boost::shared_ptr< char*[] > argv( Cobalt::Core::Core::commandLineToArgvA( GetCommandLineA(), &argc ), [](void* const ptr) {
                                                     if( ptr ) LocalFree( ptr );
                                                  } );
         if( !argv.get() ) {
            throw std::runtime_error( (boost::format( "Unable to parse command line %s" ) % boost::system::system_error( GetLastError(), boost::system::system_category() ).what()).str() );
         }

         options.init( argc, argv.get() );
      }
      ///
      const int result( _AtlModule.WinMain( nShowCmd ) );
      if( result != ERROR_SUCCESS ) {
         throw boost::system::system_error( GetLastError(), boost::system::system_category() );
      }
      return result;
   }
   catch( const std::exception& ex ) {
      Cobalt::Core::toErrorEventLog( boost::lexical_cast< std::wstring >( (boost::format( "_tWinMain()[Message: %s]" ) % ex.what()).str() ) );
   }
   catch( ... ) {
      Cobalt::Core::toErrorEventLog( boost::lexical_cast< std::wstring >( (boost::format( "_tWinMain()[Message: %s]" ) % "Critical error!").str() ) );
   }
   return 1;
}
