#include "../stdafx.h"

#include "../Utility/Traits.h"
#include "../Utility/EnableMake.h"
#include "../Utility/MakeObject.h"

#include "../Memmory/Buffer.h"

#include "../Utility/Settings/ISettings.h"
#include "../Utility/Settings/Settings.h"

#include "../Tcp/Client/BlockClient.h"

#include "IPublish.h"
#include "Publish.h"

namespace Cobalt
{
   namespace EntryPoint
   {
      void Publish::publish( executor_type executor ) {
         handler_->run( std::move( executor ) );
      }

      void Publish::quit() {
         handler_->quit();
      }

      bool Publish::tryQuit() {
         handler_->stop();
         wait( TRY_QUIT_TIMEOUT );
         return handler_->isStopped();
      }

      bool Publish::isQuited() {
         return handler_->isQuited();
      }

      void __fastcall Publish::wait( size_t timeout ) const {
         while( handler_ && handler_.get() && !handler_->isStopped() ) {
            std::this_thread::sleep_for( std::chrono::milliseconds( timeout ) );
         }
      }

      Publish::Publish( const boost::shared_ptr< Utility::ISettings >& settings ) :
         settings_( settings ),
         handler_( Utility::make_shared_pool< Tcp::BlockClient, boost::default_user_allocator_malloc_free >( settings->getHost(), settings->getPort() ) ) {
      }

      boost::shared_ptr< IPublish > Publish::getInstance( const boost::shared_ptr< Utility::ISettings >& settings ) {
         return Utility::make_shared_pool_enable< IPublish, Publish, boost::default_user_allocator_malloc_free, boost::details::pool::default_mutex >( settings );
      }
   }
}
