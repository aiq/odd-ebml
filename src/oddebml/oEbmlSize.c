#include "oddebml/oEbmlSize.h"

#include "_/misc.h"
#include "clingo/io/write.h"
#include "clingo/io/write_type.h"
#include "clingo/type/int8.h"
#include "clingo/type/int64.h"

static uint64_t const O_LenMasks[] = {
	0x80L,
   0x4000L,
   0x200000L,
   0x10000000L,
   0x0800000000L,
   0x040000000000L,
   0x02000000000000L,
   0x0100000000000000L
};

static uint64_t const O_ValMasks[] = {
	0x7fL,
   0x3fffL,
   0x1fffffL,
   0x0fffffffL,
   0x07ffffffffL,
   0x03ffffffffffL,
   0x01ffffffffffffL,
   0x00ffffffffffffffL
};

static uint64_t const O_UnknownValues[] = {
	0xffL,
   0x7fffL,
   0x3fffffL,
   0x1fffffffL,
   0x0fffffffffL,
   0x07ffffffffffL,
   0x03ffffffffffffL,
   0x01ffffffffffffffL
};

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

int64_t O_MaxEbmlSize = 0x00ffffffffffffffL;

/*******************************************************************************
 generated
*******************************************************************************/

SLICE_IMPL_C_(
   oEbmlSize,              // Type
   oEbmlSizeSlice,         // SliceType
   ebml_size_slice_o,      // FuncName
   oVarEbmlSizeSlice,      // VarSliceType
   var_ebml_size_slice_o   // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

extern inline oEbmlSize ebml_size_o( uint64_t raw );

oEbmlSize encode_ebml_size_o( int64_t val )
{
   uint64_t raw = uint64_c_( val );
   if ( not in_range_c_( 0, raw, O_MaxEbmlSize ) )
   {
      return invalid_ebml_size_o();
   }

   int8_t len = 1;
   while ( ( raw & O_ValMasks[ len-1 ] ) != raw )
   {
      len++;
   }

   return ebml_size_o( O_LenMasks[ len-1 ] | raw );
}

oEbmlSize invalid_ebml_size_o( void )
{
   return ebml_size_o( 0 );
}

oEbmlSize unknown_ebml_size_o( int8_t len )
{
   if ( not in_range_c_( 1, len, 8 ) )
   {
      return invalid_ebml_size_o();
   }
   uint64_t raw = O_UnknownValues[len-1];
   return ebml_size_o( raw );
}

/*******************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_ebml_size_o( oEbmlSize size, oEbmlSize oth );

int64_t decode_ebml_size_o( oEbmlSize size )
{
   int8_t len = ebml_size_length_o( size );
   return len > 0 ? int64_c_( size.raw & O_ValMasks[ len-1 ] )
                  : 0;
}

int8_t ebml_size_length_o( oEbmlSize size )
{
   int8_t len = 1;
   while ( len <= 8 and
      ( size.raw & O_ValMasks[ len-1] ) != ( size.raw ^ O_LenMasks[ len-1 ] )
   )
   {
      len++;
   }
   if ( len > 8 )
   {
      return 0;
   }
   return len;
}

bool ebml_size_is_unknown_o( oEbmlSize size )
{
   cUint64Slice unknowns = uint64_slice_c( 8, O_UnknownValues );
   for_each_c_( uint64_t const*, u, unknowns )
   {
      if ( size.raw == *u )
      {
         return true;
      }
   }
   return false;
}

/*******************************************************************************
 io
*******************************************************************************/

union vint64Mixer {
   cByte arr[8];
   uint64_t u;
};

bool record_ebml_size_o( cRecorder rec[static 1], oEbmlSize size )
{
   int8_t len = ebml_size_length_o( size );
   if ( len < 1 )
   {
      return false;
   }
   int8_t shift = 8 - len;

   union vint64Mixer mixer;
   mixer.u = swap_uint64_to_c( size.raw, c_BigEndian );
   return record_bytes_c( rec, bytes_c( len, mixer.arr + shift ) );
}

bool scan_ebml_size_o( cScanner sca[static 1], oEbmlSize size[static 1] )
{
   if ( sca->space == 0 )
   {
      return false;
   }

   cByte const* first = sca->mem;
   cBytes checkBytes = slice_c_( cByte,
      0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
   );
   cBytes idBytes = view_bytes_c( sca, vint_scan_size_o( *first, checkBytes ) );
   if ( is_empty_c_( idBytes) )
   {
      return false;
   }

   union vint64Mixer mixer;
   cRecorder* rec = &make_recorder_c_( 8, mixer.arr );
   record_pad_c( rec, 0x00, 8-idBytes.s );
   record_bytes_c( rec, idBytes );
   size->raw = swap_uint64_from_c( mixer.u, c_BigEndian );
   return true;
}

bool write_ebml_size_o( cRecorder rec[static 1],
                        oEbmlSize size,
                        char const fmt[static 1] )
{
   cScanner* sca = &cstr_scanner_c_( fmt );

   if ( sca->space == 0 )
   {
      cRecorder* tmpRec = &recorder_c_( 32 );
      record_ebml_size_o( tmpRec, size );
      return write_recorded_c( rec, tmpRec, "bs/X/32/8" );
   }

   if ( unscanned_is_c( sca, "dbg" ) )
   {
      cRecorder* tmpRec = &recorder_c_( 32 );
      record_ebml_size_o( tmpRec, size );
      return write_c_( rec,
         "{ .id={bs},", recorded_bytes_c( tmpRec ),
         " .val={i64}", decode_ebml_size_o( size ),
         " .len={i64} }", ebml_size_length_o( size )
      );
   }
   return false;
}