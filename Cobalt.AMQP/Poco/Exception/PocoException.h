#ifndef __AMQP_POCO_EXCEPTION_H_INCLUDED__
#define __AMQP_POCO_EXCEPTION_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../../fwdheaders.h"

#define DECLARE_EXCEPTION(CLS, BASE)               \
   class CLS :                                     \
      public BASE {                                \
   public:                                         \
      explicit CLS(const std::string& _Message)    \
         : BASE(_Message.c_str()) {                \
      }                                            \
                                                   \
      explicit CLS(const char* _Message)           \
         : BASE(_Message) {                        \
      }                                            \
   };                                              

#pragma pack( push, 8 )

namespace Cobalt
{
   namespace Poco
   {
      DECLARE_EXCEPTION(PocoException, std::exception)

      DECLARE_EXCEPTION(LogicException, PocoException)
      DECLARE_EXCEPTION(AssertionViolationException, LogicException)
      DECLARE_EXCEPTION(NullPointerException, LogicException)
      DECLARE_EXCEPTION(NullValueException, LogicException)
      DECLARE_EXCEPTION(BugcheckException, LogicException)
      DECLARE_EXCEPTION(InvalidArgumentException, LogicException)
      DECLARE_EXCEPTION(NotImplementedException, LogicException)
      DECLARE_EXCEPTION(RangeException, LogicException)
      DECLARE_EXCEPTION(IllegalStateException, LogicException)
      DECLARE_EXCEPTION(InvalidAccessException, LogicException)
      DECLARE_EXCEPTION(SignalException, LogicException)
      DECLARE_EXCEPTION(UnhandledException, LogicException)

      DECLARE_EXCEPTION(RuntimeException, std::runtime_error)
      DECLARE_EXCEPTION(NotFoundException, RuntimeException)
      DECLARE_EXCEPTION(ExistsException, RuntimeException)
      DECLARE_EXCEPTION(TimeoutException, RuntimeException)
      DECLARE_EXCEPTION(SystemException, RuntimeException)
      DECLARE_EXCEPTION(RegularExpressionException, RuntimeException)
      DECLARE_EXCEPTION(LibraryLoadException, RuntimeException)
      DECLARE_EXCEPTION(LibraryAlreadyLoadedException, RuntimeException)
      DECLARE_EXCEPTION(NoThreadAvailableException, RuntimeException)
      DECLARE_EXCEPTION(PropertyNotSupportedException, RuntimeException)
      DECLARE_EXCEPTION(PoolOverflowException, RuntimeException)
      DECLARE_EXCEPTION(NoPermissionException, RuntimeException)
      DECLARE_EXCEPTION(OutOfMemoryException, RuntimeException)
      DECLARE_EXCEPTION(SocketException, RuntimeException)
      DECLARE_EXCEPTION(TransactionException, RuntimeException)
      DECLARE_EXCEPTION(DataException, RuntimeException)

      DECLARE_EXCEPTION(DataFormatException, DataException)
      DECLARE_EXCEPTION(SyntaxException, DataException)
      DECLARE_EXCEPTION(CircularReferenceException, DataException)
      DECLARE_EXCEPTION(PathSyntaxException, SyntaxException)
      DECLARE_EXCEPTION(IOException, RuntimeException)
      DECLARE_EXCEPTION(ProtocolException, IOException)
      DECLARE_EXCEPTION(FileException, IOException)
      DECLARE_EXCEPTION(FileExistsException, FileException)
      DECLARE_EXCEPTION(FileNotFoundException, FileException)
      DECLARE_EXCEPTION(PathNotFoundException, FileException)
      DECLARE_EXCEPTION(FileReadOnlyException, FileException)
      DECLARE_EXCEPTION(FileAccessDeniedException, FileException)
      DECLARE_EXCEPTION(CreateFileException, FileException)
      DECLARE_EXCEPTION(OpenFileException, FileException)
      DECLARE_EXCEPTION(WriteFileException, FileException)
      DECLARE_EXCEPTION(ReadFileException, FileException)
      DECLARE_EXCEPTION(DirectoryNotEmptyException, FileException)
      DECLARE_EXCEPTION(UnknownURISchemeException, RuntimeException)
      DECLARE_EXCEPTION(TooManyURIRedirectsException, RuntimeException)
      DECLARE_EXCEPTION(URISyntaxException, SyntaxException)

      DECLARE_EXCEPTION(ApplicationException, PocoException)
      DECLARE_EXCEPTION(BadCastException, RuntimeException)
   }
}

#pragma pack( pop )

#endif //__AMQP_POCO_EXCEPTION_H_INCLUDED__
