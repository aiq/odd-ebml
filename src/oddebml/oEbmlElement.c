#include "oddebml/oEbmlElement.h"

#include "clingo/type/double.h"
#include "clingo/type/float.h"
#include "oddebml/oEbmlSize.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

bool ebml_as_int_o( oEbmlElement const elem[static 1],
                    int64_t val[static 1] )
{
   cBytes bin = elem->bytes;
   if ( not in_range_c_( 0, bin.s, 8 ) ) return false;

   if ( is_empty_c_( bin ) )
   {
      *val = 0;
      return true;
   }

   cByte fillByte = ( get_bytes_bit_c( bin, 0 ) == 1 ) ? 0xff
                                                       : 0x00;
   cRecorder* rec = &recorder_c_( 8 );
   record_pad_c( rec, char_c_( fillByte ), 8 - bin.s );
   record_bytes_c( rec, bin );
   reset_recorder_c( rec );

   int64_t const* beVal = rec->mem;
   *val = swap_int64_from_c( *beVal, c_BigEndian );
	return true;
}

bool ebml_as_uint_o( oEbmlElement const elem[static 1],
                     uint64_t val[static 1] )
{
   cBytes bin = elem->bytes;
   if ( not in_range_c_( 0, bin.s, 8 ) ) return false;

   if ( is_empty_c_( bin ) )
   {
      *val = 0;
      return true;
   }

   cRecorder* rec = &recorder_c_( 8 );
   record_pad_c( rec, 0x00, 8 - bin.s );
   record_bytes_c( rec, bin );
   reset_recorder_c( rec );

   uint64_t const* beVal = rec->mem;
   *val = swap_uint64_from_c( *beVal, c_BigEndian );
	return true;
}

bool ebml_as_float_o( oEbmlElement const elem[static 1], double val[static 1] )
{
   if ( is_empty_c_( elem->bytes ) )
   {
      *val = 0.0;
      return true;
   }

   cScanner* sca = &make_scanner_c_( elem->bytes.s, elem->bytes.v );
   double d;
   if ( scan_double_c( sca, &d ) )
   {
      *val = swap_double_from_c( d, c_BigEndian );
      return true;
   }

   float f;
   if ( scan_float_c( sca, &f ) )
   {
      *val = swap_float_from_c( f, c_BigEndian );
      return true;
   }

   return false;
}

bool ebml_as_string_o( oEbmlElement const elem[static 1],
                       cChars val[static 1] )
{
   cBytes bin = elem->bytes;
   if ( is_empty_c_( bin ) )
   {
      *val = empty_chars_c();
      return true;
   }
   if ( last_c_( bin ) == 0x00 )
   {
      bin.s--;
   }

   for_each_c_( cByte const*, b, bin )
   {
      if ( not in_range_c_( 0x20, *b, 0x7E ) ) return false;;
   }

   *val = chars_c( bin.s, (char const*) bin.v );
   return true;
}

bool ebml_as_utf8_o( oEbmlElement const elem[static 1],
                     cChars val[static 1] )
{
   cBytes bin = elem->bytes;
   if ( is_empty_c_( bin ) )
   {
      *val = empty_chars_c();
      return true;
   }
   if ( last_c_( bin ) == 0x00 )
   {
      bin.s--;
   }

   cChars c = chars_c( bin.s, (char const*) bin.v );
   if ( count_runes_c( c ) == -1 ) return false;

   *val = c;
   return true;
}

bool ebml_as_date_o( oEbmlElement const elem[static 1],
                     oEbmlDate val[static 1] )
{
   if ( is_empty_c_( elem->bytes ) )
   {
      *val = default_ebml_date_o();
      return true;
   }

   cScanner* sca = &make_scanner_c_( elem->bytes.s, elem->bytes.v );
   return scan_ebml_date_o( sca, val );
}

/*******************************************************************************
 io
*******************************************************************************/

bool record_ebml_element_o( cRecorder rec[static 1],
                            oEbmlElement const elem[static 1] )
{
   if is_invalid_c_( elem->bytes ) return false;

   oEbmlSize size = encode_ebml_size_o( elem->bytes.s );
   int64_t len = ebml_id_length_o( elem->id ) +
                 ebml_size_length_o( size ) +
                 elem->bytes.s;
   if ( rec->space < len ) return false;

   int64_t oldPos = rec->pos;
   if ( record_ebml_id_o( rec, elem->id ) and
        record_ebml_size_o( rec, size ) and
        record_bytes_c( rec, elem->bytes ) )
   {
      return true;
   }
   move_recorder_to_c( rec, oldPos );
   return false;
}

bool view_ebml_element_o( cScanner sca[static 1], oEbmlElement elem[static 1] )
{
   int64_t oldPos = sca->pos;
   once_c_( xyz )
   {
      oEbmlId eid;
      if ( not scan_ebml_id_o( sca, &eid ) ) break;

      oEbmlSize esize;
      if ( not scan_ebml_size_o( sca, &esize ) ) break;

      int64_t size = decode_ebml_size_o( esize );
      if ( size < 0 ) break;

      cBytes bytes = unscanned_bytes_c( sca, size );
      if ( bytes.s != size ) break;

      elem->id = eid;
      elem->bytes = bytes;
      return true;
   }
   move_scanner_to_c( sca, oldPos );
   return false;
}

/*******************************************************************************

*******************************************************************************/

#define SCAN_EBML_VAL_( FuncName, Type, AsFunc )                               \
bool FuncName( cScanner sca[static 1], Type val[static 1] )                    \
{                                                                              \
   int64_t oldPos = sca->pos;                                                  \
   once_c_( xyz )                                                              \
   {                                                                           \
      oEbmlElement elem;                                                       \
      if ( not view_ebml_element_o( sca, &elem ) ) break;                      \
      if ( not AsFunc( &elem, val ) ) break;                                   \
      return true;                                                             \
   }                                                                           \
                                                                               \
   move_scanner_to_c( sca, oldPos );                                           \
   return false;                                                               \
}

SCAN_EBML_VAL_( scan_ebml_int_element_o,     int64_t,    ebml_as_int_o )
SCAN_EBML_VAL_( scan_ebml_uint_element_o,    uint64_t,   ebml_as_uint_o )
SCAN_EBML_VAL_( scan_ebml_float_element_o,   double,     ebml_as_float_o )
SCAN_EBML_VAL_( scan_ebml_date_element_o,    oEbmlDate,  ebml_as_date_o )
SCAN_EBML_VAL_( view_ebml_string_element_o,  cChars,     ebml_as_string_o )
SCAN_EBML_VAL_( view_ebml_utf8_element_o,    cChars,     ebml_as_utf8_o )
