#ifndef __SERVICE_LEXICAL_CAST__H_INCLUDED__ 
#define __SERVICE_LEXICAL_CAST__H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#pragma pack( push, 8 )

namespace boost {

   template <>
   inline _bstr_t lexical_cast(const std::string& arg) {
      return _bstr_t(arg.c_str());
   }

   template <>
   inline _bstr_t lexical_cast(const std::wstring& arg) {
      return _bstr_t(arg.c_str());
   }

   template <>
   inline std::wstring lexical_cast(const std::string& arg) {
      return std::wstring(_bstr_t(arg.c_str()));
   }

   template <>
   inline std::string lexical_cast(const std::wstring& arg) {
      return std::string(_bstr_t(arg.c_str()));
   }

}

#pragma pack( pop )

#endif //__SERVICE_LEXICAL_CAST__H_INCLUDED__