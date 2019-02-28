#ifndef __MANAGER_MACROSES_H_INCLUDED__
#define __MANAGER_MACROSES_H_INCLUDED__

#define COBALT_MONITOR_IF_EXIST_HANDLER(PTR) \
   if(PTR.get()) { \
      (*PTR)(); \
   } \
///

#define COBALT_MONITOR_IF_EXIST_HANDLER_1_ARG(PTR, ARG) \
   if(PTR.get()) { \
      (*PTR)(ARG); \
   } \
///

#define COBALT_MONITOR_IF_EXIST_HANDLER_2_ARG(PTR, ARG1, ARG2) \
   if(PTR.get()) { \
      (*PTR)((ARG1), (ARG2)); \
   } \
///

#define COBALT_HANDLER_STATE_GUARD(STATE) \
   if(STATE) { \
      return; \
   } \
///

#define COBALT_HANDLER_ERROR_GUARD_ \
    try { \
///

#define COBALT_HANDLER_ERROR_GUARD(MONITOR, ID) \
   } \
   catch( const boost::thread_interrupted& ) { \
   } \
   catch( const std::exception& ex ) { \
      (MONITOR)->onError( ex.what(), (ID) ); \
   } \
   catch(...) { \
      (MONITOR)->onError( "Critical error", (ID) ); \
   } \
///

#define COBALT_FACTORY_GUARD(PTR, CTX) \
   if(PTR != nullptr){ \
      CTX \
   } \
///

#define X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE(r, data,  elem) \
    case data::elem : return BOOST_PP_STRINGIZE(elem); \
///

#define X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOENUM_IF(r, data, elem) \
    if (BOOST_PP_SEQ_TAIL(data) ==  \
            BOOST_PP_STRINGIZE(elem)) return \
            static_cast<std::size_t>(BOOST_PP_SEQ_HEAD(data)::elem); else \
///

#define DEFINE_ENUM_WITH_STRING_CONVERSIONS(name, enumerators) \
    enum class name { \
        BOOST_PP_SEQ_ENUM(enumerators) \
    }; \
 \
    inline const char* __stdcall name##ToString( name v ) \
    { \
        switch (v) \
        { \
            BOOST_PP_SEQ_FOR_EACH( \
                X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE, \
                name, \
                enumerators \
            ) \
            default: \
               throw std::invalid_argument( ( boost::format( "Invalid argument: %d" ) % static_cast<std::size_t>(v) ).str() ); \
        } \
    } \
 \
    inline std::size_t __stdcall StringTo##name##Helper( const std::string& s ) \
    { \
        BOOST_PP_SEQ_FOR_EACH( \
                X_DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOENUM_IF, \
                (name)(s), \
                enumerators \
            ) \
        throw std::invalid_argument( ( boost::format( "Invalid argument: %s" ) % s ).str() ); \
    } \
 \
    inline name __stdcall StringTo##name( const std::string& s ) \
    { \
         return static_cast<name>(StringTo##name##Helper(s)); \
    } \
///

#endif //__MANAGER_MACROSES_H_INCLUDED__
