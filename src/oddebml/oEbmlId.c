#include "oddebml/oEbmlId.h"

#include "_/misc.h"
#include "clingo/io/write.h"
#include "clingo/type/int32.h"

static uint32_t const O_LenMasks[] = {
	0x80L,
   0x4000L,
   0x200000L,
   0x10000000L
};

static uint32_t const O_ValMasks[] = {
	0x7fL,
	0x3fffL,
	0x1fffffL,
	0x0fffffffL,
};
/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICE_IMPL_C_(
   oEbmlId,             // Type
   oEbmlIdSlice,        // SliceType
   ebml_id_slice_o,     // FuncName
   oVarEbmlIdSlice,     // VarSliceType
   var_ebml_id_slice_o  // VarFuncName
)

/*******************************************************************************

*******************************************************************************/

int32_t const O_MaxEbmlId = 0x0ffffffe;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

extern inline oEbmlId ebml_id_o( uint32_t raw );

oEbmlId encode_ebml_id_o( int32_t val )
{
   uint32_t raw = uint32_c_( val );
   if ( not in_range_c_( 1, raw, O_MaxEbmlId ) )
   {
      return invalid_ebml_id_o();
   }
	
   int8_t len = 1;
   while ( ( raw & O_ValMasks[ len-1 ] ) != raw ) 
	{
      len++;
   }

   if ( ( raw & O_ValMasks[ len-1 ] ) == O_ValMasks[ len-1 ] ) 
	{
      len++;
   }

   return ebml_id_o( O_LenMasks[ len-1 ] | raw );
}

/*******************************************************************************
 overall
*******************************************************************************/

extern inline int cmp_ebml_id_o( oEbmlId id, oEbmlId oth );

int32_t decode_ebml_id_o( oEbmlId id )
{
   int8_t len = ebml_id_length_o( id );
   return len > 0 ? int32_c_( id.raw & O_ValMasks[ len-1 ] )
                  : 0;
}

int8_t ebml_id_length_o( oEbmlId id )
{
	int8_t len = 1;
   while ( len <= 4 and
      ( id.raw & O_ValMasks[ len-1 ] ) != ( id.raw ^ O_LenMasks[ len-1 ] )
   )
   {
      len++;
   }
   if ( len > 4 )
   {
      return -1;
   }
   return len;
}

bool ebml_id_is_valid_o( oEbmlId id )
{
   int32_t val = decode_ebml_id_o( id );
   if ( val == 0 )
   {
      return false;
   }

   oEbmlId oth = encode_ebml_id_o( val );
   return eq_c( cmp_ebml_id_o( id, oth ) );
}

oEbmlId invalid_ebml_id_o( void )
{
   return ebml_id_o( 0 );
}

/*******************************************************************************
 io
*******************************************************************************/

union vint32Mixer {
   cByte arr[4];
   uint32_t u;
};

bool record_ebml_id_o( cRecorder rec[static 1], oEbmlId id )
{
   int8_t len = ebml_id_length_o( id );
   if ( len < 1 )
   {
      return false;
   }
   int8_t shift = 4 - len;

   union vint32Mixer mixer;
   mixer.u = swap_uint32_to_c( id.raw, c_BigEndian );
   return record_bytes_c( rec, bytes_c( len, mixer.arr + shift ) );
}

bool scan_ebml_id_o( cScanner sca[static 1], oEbmlId id[static 1] )
{
   if ( sca->space == 0 )
   {
      return false;
   }

   cByte const* first = sca->mem;
   cBytes checkBytes = slice_c_( cByte, 0x80, 0x40, 0x20, 0x10 );
   cBytes idBytes = view_bytes_c( sca, vint_scan_size_o( *first, checkBytes ) );
   if ( is_empty_c_( idBytes ) )
   {
      return false;
   }

   union vint32Mixer mixer;
   cRecorder* rec = &make_recorder_c_( 4, mixer.arr );
   record_pad_c( rec, 0x00, 4-idBytes.s );
   record_bytes_c( rec, idBytes );
   id->raw = swap_uint32_from_c( mixer.u, c_BigEndian );
   return true;
}

bool write_ebml_id_o( cRecorder rec[static 1],
                      oEbmlId id,
                      char const fmt[static 1] )
{
   cScanner* sca = &cstr_scanner_c_( fmt );

   if ( unscanned_is_c( sca, "dbg" ) )
   {
      cRecorder* tmpRec = &recorder_c_( 32 );
      record_ebml_id_o( tmpRec, id );
      return write_c_( rec,
         "{ .id={bs//8},", recorded_bytes_c( tmpRec ),
         " .val={i64}", decode_ebml_id_o( id ),
         " .len={i64} }", ebml_id_length_o( id )
      );
   }
   return false;
}