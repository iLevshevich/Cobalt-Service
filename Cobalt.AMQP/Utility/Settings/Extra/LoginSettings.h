#ifndef __AMQP_LOGIN_SETTINGS_H_INCLUDED__
#define __AMQP_LOGIN_SETTINGS_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../../fwdheaders.h"

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Utility
   {
      class LoginSettings :
         public ILoginSettings,
         private boost::noncopyable {
      public:
         static boost::shared_ptr< ILoginSettings > __stdcall getInstance( const std::string& user, const std::string& password ) {
            return make_shared_pool_enable< ILoginSettings, LoginSettings, boost::default_user_allocator_malloc_free >( user, password );
         }

         std::string getUser() const override {
            return user_;
         }

         std::string getPassword() const override {
            return password_;
         }

         virtual ~LoginSettings() = default;

      protected:
         LoginSettings( const std::string& user, const std::string& password ) :
            user_( user ),
            password_( password ) {
         }

      private:
         std::string user_;
         std::string password_;
      };
   }
}

#pragma pack( pop )

#endif //__AMQP_LOGIN_SETTINGS_H_INCLUDED__
