#ifndef ODDEBML_INTERN_MISC_H
#define ODDEBML_INTERN_MISC_H

#include "clingo/type/cBytes.h"

inline int64_t vint_scan_size_o( cByte first, cBytes checkBytes )
{
   for_each_c_( cByte const*, check, checkBytes )
   {
      if ( first >= *check )
      {
         return index_of_c_( checkBytes, check ) + 1;
      }
   }
   return 0;
}

#endif