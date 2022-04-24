#ifndef ODDEBML_APIDECL_H
#define ODDEBML_APIDECL_H

#ifdef ODDEBML_STATIC_DEFINE
#  define ODDEBML_API
#  define ODDEBML_NO_EXPORT
#else
#  ifdef _WIN32
#    ifndef ODDEBML_API
#      ifdef oddebml_EXPORTS
#        define ODDEBML_API __declspec(dllexport)
#      else
#        define ODDEBML_API __declspec(dllimport)
#      endif
#    endif
#  else
#    define ODDEBML_API
#    define ODDEBML_NO_EXPORT
#  endif
#
#  ifndef ODDEBML_NO_EXPORT
#    define ODDEBML_NO_EXPORT 
#  endif
#endif

#endif