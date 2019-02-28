#include "../../stdafx.h"

#include "../../Poco/Exception/PocoException.h"

#include "Transaction.h"

namespace Cobalt
{
   namespace Utility
   {
      void Transaction::transaction( const std::function< void() >& executor,
                                     const std::function< void() >& success,
                                     AMQP::Channel& channel ) {
         try {
            channel
               .startTransaction();
            executor();
            channel
               .commitTransaction()
               .onSuccess( success );
         }
         catch( const AMQP::Exception& ex ) {
            channel
               .rollbackTransaction()
               .onSuccess( success );

            throw Poco::TransactionException( ex.what() );
         }
      }
   }
}
