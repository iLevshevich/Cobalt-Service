#include "../stdafx.h"

#include "../Utility/Traits.h"
#include "../Utility/EnableMake.h"
#include "../Utility/MakeAsync.h"
#include "../Utility/MakeObject.h"

#include "../Memmory/Buffer.h"

#include "../Utility/Settings/ISettings.h"
#include "../Utility/Settings/Settings.h"

#include "../Tcp/Server/BlockServer.h"

#include "IConsume.h"
#include "Consume.h"

namespace Cobalt
{
   namespace EntryPoint
   {
      void Consume::consume( executor_type executor ) {
         handler_->run( std::move( executor ) );
      }

      void Consume::quit() {
         handler_->quit();
      }

      bool Consume::tryQuit() {
         handler_->stop();
		 ///
		 {
			 wait(TRY_QUIT_TIMEOUT);
		 }
		 ///
         return handler_->isStopped();
      }

      bool Consume::isQuited() {
         return handler_->isQuited();
      }

      void __fastcall Consume::wait( size_t timeout ) const {
         while( handler_ && handler_.get() && !handler_->isStopped() ) {
            std::this_thread::sleep_for( std::chrono::milliseconds( timeout ) );
         }
      }

      Consume::Consume( const boost::shared_ptr< Utility::ISettings >& settings ):
         settings_( settings ),
         handler_( Utility::make_shared_pool< Tcp::BlockServer, boost::default_user_allocator_malloc_free >( settings->getPort() ) ) {
      }

      boost::shared_ptr< IConsume > Consume::getInstance( const boost::shared_ptr< Utility::ISettings >& settings ) {
         return Utility::make_shared_pool_enable< IConsume, Consume, boost::default_user_allocator_malloc_free >( settings );
      }
   }
}
