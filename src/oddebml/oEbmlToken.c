#include "oddebml/oEbmlToken.h"

#include "clingo/type/double.h"
#include "clingo/type/float.h"
#include "oddebml/oEbmlSize.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

bool get_ebml_int_o( oEbmlToken const tok[static 1], int64_t val[static 1] )
{
   cBytes bin = tok->bytes;
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
	return true;
}

bool get_ebml_uint_o( oEbmlToken const tok[static 1], uint64_t val[static 1] )
{
   cBytes bin = tok->bytes;
   if ( not in_range_c_( 0, bin.s, 8 ) ) return false;

   if ( is_empty_c_( bin ) )
   {
      *val = 0;
      return true;
   }

   cRecorder* rec = &recorder_c_( 8 );
   record_pad_c( rec, 0x00, 8 - bin.s );
   record_bytes_c( rec, bin );
	return true;
}

bool get_ebml_float_o( oEbmlToken const tok[static 1], double val[static 1] )
{
   if ( is_empty_c_( tok->bytes ) )
   {
      *val = 0.0;
      return true;
   }

   cScanner* sca = &make_scanner_c_( tok->bytes.s, tok->bytes.v );
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

bool get_ebml_string_o( oEbmlToken const tok[static 1], cChars val[static 1] )
{
   cBytes bin = tok->bytes;
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

bool get_ebml_utf8_o( oEbmlToken const tok[static 1], cChars val[static 1] )
{
   cBytes bin = tok->bytes;
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

bool get_ebml_date_o( oEbmlToken const tok[static 1], oEbmlDate val[static 1] )
{
   if ( is_empty_c_( tok->bytes ) )
   {
      *val = default_ebml_date_o();
      return true;
   }

   cScanner* sca = &make_scanner_c_( tok->bytes.s, tok->bytes.v );
   return scan_ebml_date_o( sca, val );
}

/*******************************************************************************
 io
*******************************************************************************/

bool record_ebml_token_o( cRecorder rec[static 1],
                          oEbmlToken const tok[static 1] )
{
   oEbmlSize size = encode_ebml_size_o( tok->bytes.s );
   int64_t len = ebml_id_length_o( tok->id ) + ebml_size_length_o( size ) + tok->bytes.s;
   if ( rec->space < len ) return false;

   int64_t oldPos = rec->pos;
   if ( record_ebml_id_o( rec, tok->id ) and
        record_ebml_size_o( rec, size ) and
        record_bytes_c( rec, tok->bytes ) )
   {
      return true;
   }
   move_recorder_to_c( rec, oldPos );
   return false;
}

bool scan_ebml_token_o( cScanner sca[static 1], oEbmlToken tok[static 1] )
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

      tok->id = eid;
      tok->bytes = bytes;
      return true;
   }
   move_scanner_to_c( sca, oldPos );
   return false;
}