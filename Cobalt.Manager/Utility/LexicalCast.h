#ifndef __LEXICAL_CAST_H_INCLUDED__
#define __LEXICAL_CAST_H_INCLUDED__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#	pragma once
#endif

#include "../fwdheaders.h"

#pragma pack( push, 8 )

namespace boost
{
   template<>
   inline std::string __stdcall lexical_cast( Cobalt::Utility::Traits< property_tree::ptree >::const_reference_t t ) {
      std::ostringstream stream;
#if defined(__MANAGER_JSON_PRETTY__)
      write_json( stream, t );
#else
      write_json(stream, t, false);
#endif
      return stream.str();
   }

   template<>
   inline property_tree::ptree __stdcall lexical_cast( Cobalt::Utility::Traits< std::string >::const_reference_t t ) {
      std::istringstream stream;
      stream.str( t );

      property_tree::ptree result;
      read_json( stream, result );
      return result;
   }
}

#pragma pack( pop )

#endif //__LEXICAL_CAST_H_INCLUDED__
