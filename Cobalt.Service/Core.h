#ifndef __SERVICE_CORE_H_INCLUDED__
#define __SERVICE_CORE_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#pragma pack( push, 8 )

namespace Cobalt
{
   class Core :
      private boost::noncopyable {
   public:
      typedef void (init)( int argc, boost::shared_ptr< char*[] > argv );
      typedef void (run)();
      typedef void (stop)();

      static PCHAR* __fastcall commandLineToArgvA( PCHAR CmdLine, int* _argc );
      static void __fastcall toErrorEventLog( const std::wstring& error_message );

      Core();

      void Run() noexcept;
      void Stop() noexcept;

      virtual ~Core();
   private:
      boost::filesystem::path lib_;

      boost::function< init > init_;
      boost::function< run > run_;
      boost::function< stop > stop_;

      boost::thread_group guard_;
   };
}

#pragma pack( pop )

#endif //__SERVICE_CORE_H_INCLUDED__
