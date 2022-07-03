#include "oddebml/oEbmlMarker.h"

#include "_/misc.h"
#include "clingo/io/FILE.h"
#include "oddebml/oEbmlElement.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool fread_curr_ebml_marker_o( FILE* f, oEbmlMarker marker[static 1] )
{
   must_exist_c_( f );

   oEbmlId id;
   if ( not fread_ebml_id_o( f, &id ) ) return false;

   oEbmlSize size;
   if ( not fread_ebml_size_o( f, &size ) ) return false;

   fpos_t pos;
   if ( fgetpos( f, &pos ) != 0 ) return false;

   marker->id = id;
   marker->size = decode_ebml_size_o( size );
   marker->pos = pos;

   return true;
}

bool fread_next_ebml_marker_o( FILE* f,
                               int64_t delta,
                               oEbmlMarker marker[static 1] )
{
   fpos_t curr;
   if ( fgetpos( f, &curr ) != 0 ) return false;

   fpos_t next = curr + delta;
   if ( fsetpos( f, &next ) != 0 ) return false;

   return fread_curr_ebml_marker_o( f, marker );
}

bool fread_ebml_child_marker_o( FILE* f,
                                oEbmlMarker const from[static 1],
                                oEbmlMarker marker[static 1] )
{
   must_exist_c_( f );

   if ( fsetpos( f, &(from->pos) ) != 0 ) return false;

   return fread_curr_ebml_marker_o( f, marker );
}

bool fread_ebml_sibling_marker_o( FILE* f,
                                  oEbmlMarker const from[static 1],
                                  oEbmlMarker marker[static 1] )
{
   must_exist_c_( f );

   fpos_t next = from->pos + from->size;
   if ( fsetpos( f, &next ) != 0 ) return false;

   return fread_curr_ebml_marker_o( f, marker );
}

bool fread_ebml_bytes_o( FILE* f,
                         oEbmlMarker const from[static 1],
                         cVarBytes buf[static 1] )
{
   must_exist_c_( f );

   if ( from->size == 0 )
   {
      buf->s = 0;
      return true;
   }

   if ( fsetpos( f, &(from->pos) ) != 0 ) return false;

   if ( buf->s < from->size ) return false;

   buf->s = from->size;
   return fread_bytes_c( f, buf );
}

/*******************************************************************************

*******************************************************************************/

bool fread_ebml_int_o( FILE* f,
                       oEbmlMarker const from[static 1],
                       int64_t val[static 1] )
{
   must_exist_c_( f );

   if ( not in_range_c_( 0, from->size, 8 ) ) return false;

   cVarBytes buf = scalars_c_( 8, cByte );
   if ( not fread_ebml_bytes_o( f, from, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( from->id, as_bytes_c( buf ) );
   return ebml_as_int_o( &elem, val );
}

bool fread_ebml_uint_o( FILE* f,
                        oEbmlMarker const from[static 1],
                        uint64_t val[static 1] )
{
   must_exist_c_( f );

   if ( not in_range_c_( 0, from->size, 8 ) ) return false;

   cVarBytes buf = scalars_c_( 8, cByte );
   if ( not fread_ebml_bytes_o( f, from, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( from->id, as_bytes_c( buf ) );
   return ebml_as_uint_o( &elem, val );
}

bool fread_ebml_float_o( FILE* f,
                         oEbmlMarker const from[static 1],
                         double val[static 1] )
{
   must_exist_c_( f );

   if ( not in_range_c_( 0, from->size, 8 ) ) return false;

   cVarBytes buf = scalars_c_( 8, cByte );
   if ( not fread_ebml_bytes_o( f, from, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( from->id, as_bytes_c( buf ) );
   return ebml_as_float_o( &elem, val );
}

bool fread_ebml_string_o( FILE* f,
                          oEbmlMarker const from[static 1],
                          cVarChars val[static 1] )
{
   must_exist_c_( f );

   cVarBytes buf = var_bytes_c( val->s, (void*)val->v );
   if ( not fread_ebml_bytes_o( f, from, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( from->id, as_bytes_c( buf ) );
   cChars chars;
   bool res = ebml_as_string_o( &elem, &chars );
   if ( res )
   {
      val->s = chars.s;
   }
   return res;
}

bool fread_ebml_utf8_o( FILE* f,
                        oEbmlMarker const from[static 1],
                        cVarChars val[static 1] )
{
   must_exist_c_( f );

   cVarBytes buf = var_bytes_c( val->s, (void*)val->v );
   if ( not fread_ebml_bytes_o( f, from, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( from->id, as_bytes_c( buf ) );
   cChars chars;
   bool res = ebml_as_utf8_o( &elem, &chars );
   if ( res )
   {
      val->s = chars.s;
   }
   return res;
}

bool fread_ebml_date_o( FILE* f,
                        oEbmlMarker const from[static 1],
                        oEbmlDate val[static 1] )
{
   must_exist_c_( f );

   if ( not in_range_c_( 0, from->size, 8 ) ) return false;

   cVarBytes buf = scalars_c_( 8, cByte );
   if ( not fread_ebml_bytes_o( f, from, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( from->id, as_bytes_c( buf ) );
   return ebml_as_date_o( &elem, val );
}