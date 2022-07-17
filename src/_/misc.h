#ifndef ODDEBML_INTERN_MISC_H
#define ODDEBML_INTERN_MISC_H

#include "clingo/io/FILE.h"
#include "clingo/type/cBytes.h"

static inline int64_t vint_scan_size_o( cByte first, cBytes checkBytes )
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

static inline cBytes fscan_vint_o( FILE* f,
                                   cVarBytes buf,
                                   cBytes checkBytes,
                                   cErrorStack es[static 1] )
{
   must_exist_c_( f );

   int c = fgetc( f );
   if ( c == EOF )
   {
      push_error_c_( es, &C_Eof );
      return (cBytes)invalid_slice_c_();
   }
   uint8_t first;
   if ( not int64_to_uint8_c( c, &first ) )
   {
      push_lit_str_error_c( es, "invalid first byte" );
      return (cBytes)invalid_slice_c_();
   }

   int64_t size = vint_scan_size_o( first, checkBytes );
   if ( not in_range_c_( 1, size, buf.s ) )
   {
      push_lit_str_error_c( es, "not enough buffer space" );
      return (cBytes)invalid_slice_c_();
   }

   buf.v[0] = first;
   buf.s = size;
   cBytes res = as_bytes_c( buf );
   if ( res.s == 1 ) return res;

   buf = mid_var_bytes_c( buf, 1 );
   if ( not fget_bytes_c( f, &buf ) ) 
   {
      if ( feof( f ) != 0 )
      {
         push_error_c_( es, &C_UnexpectedEof );
      }
      else
      {
         push_file_error_c( es, f );
      }
      return (cBytes)invalid_slice_c_();
   }

   return res;
}

#endif