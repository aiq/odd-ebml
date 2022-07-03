#ifndef ODDEBML_INTERN_MISC_H
#define ODDEBML_INTERN_MISC_H

#include "clingo/io/FILE.h"
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

inline cBytes vint_fread_o( FILE* f, cVarBytes buf, cBytes checkBytes )
{
   must_exist_c_( f );

   int c = fgetc( f );
   uint8_t first;
   if ( not int64_to_uint8_c( c, &first ) ) return (cBytes)invalid_slice_c_();

   int64_t size = vint_scan_size_o( first, checkBytes );
   if ( not in_range_c_( 1, size, buf.s ) ) return (cBytes)invalid_slice_c_();

   buf.v[0] = first;
   buf.s = size;
   cBytes res = as_bytes_c( buf );
   if ( res.s == 1 ) return res;

   buf = mid_var_bytes_c( buf, 1 );
   if ( not fread_bytes_c( f, &buf ) ) return (cBytes)invalid_slice_c_();

   return res;
}

#endif