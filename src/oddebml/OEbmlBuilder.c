#include "oddebml/OEbmlBuilder.h"

#include "_/error.h"
#include "clingo/container/pile.h"
#include "clingo/io/cRecorder.h"
#include "clingo/type/double.h"
#include "clingo/type/float.h"
#include "clingo/type/int8.h"
#include "clingo/type/int16.h"
#include "clingo/type/int32.h"
#include "clingo/type/int64.h"
#include "clingo/type/uint8.h"
#include "clingo/type/uint16.h"
#include "clingo/type/uint32.h"
#include "clingo/type/uint64.h"

/*******************************************************************************

*******************************************************************************/

struct oEbmlBuilderMarker {
   oEbmlId id;
   int64_t pos;
};
typedef struct oEbmlBuilderMarker oEbmlBuilderMarker;

static inline oEbmlBuilderMarker ebml_builder_marker_o( oEbmlId id, int64_t pos )
{
   return (oEbmlBuilderMarker){ .id=id, .pos=pos };
}

STATIC_VAL_PILE_IMPL_C_(
   __attribute__((unused)),   // Attr
   oEbmlBuilderMarker,        // Type
   oEbmlBuilderMarkerPile,    // PileType
   ebml_builder_marker_o      // FuncSuffix
)

static TAKE_C_(
   take_ebml_builder_marker_o,   // FuncName
   oEbmlBuilderMarkerPile,       // SliceType
   oEbmlBuilderMarker            // ValueType
)

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct OEbmlBuilder
{
   oEbmlBuilderMarkerPile pile;
   cRecorder ownRec;
   cRecorder* rec;
};

static inline void cleanup( void* instance )
{
   OEbmlBuilder* b = instance;
   if ( &b->ownRec == b->rec )
   {
      reset_recorder_c( b->rec );

      if ( b->rec->mem )
      {
         free( b->rec->mem );
      }
   }

   if ( b->pile.v )
   {
      free( b->pile.v );
   }
}

cMeta const O_EbmlBuilderMeta = {
   .desc = stringify_c_( OEbmlBuilder ),
   .cleanup = &cleanup
};

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

OEbmlBuilder* make_ebml_builder_o( int64_t cap )
{
   must_be_positive_c_( cap );

   cRecorder rec;
   if ( not alloc_recorder_mem_c( &rec, cap ) )
      return NULL;

   OEbmlBuilder* b = make_ebml_builder_shell_o( &rec );
   if ( b == NULL )
   {
      free_recorder_mem_c( &rec );
      return NULL;
   }

   b->ownRec = rec;
   b->rec = &b->ownRec;
   return b;
}

OEbmlBuilder* make_ebml_builder_shell_o( cRecorder rec[static 1] )
{
   OEbmlBuilder* b = new_object_c_( OEbmlBuilder, &O_EbmlBuilderMeta );
   if ( b == NULL )
   {
      return NULL;
   }

   if ( not alloc_pile_of_ebml_builder_marker_o( &(b->pile), 8 ) )
   {
      release_c( b );
      return NULL;
   }

   b->rec = rec;
   return b;
}

OEbmlBuilder* new_ebml_builder_o( void )
{
   return make_ebml_builder_o( 512 );
}

/*******************************************************************************

*******************************************************************************/

bool push_ebml_builder_error_o( cErrorStack es[static 1], OEbmlBuilder* b )
{
   must_exist_c_( b );

   return push_errno_error_c( es, ENOMEM ) ||
          push_ebml_lit_error_o( es, "OEbmlBuilder" );
}

/*******************************************************************************

*******************************************************************************/

cBytes built_ebml_o( OEbmlBuilder* b )
{
   must_exist_c_( b );
   return recorded_bytes_c( b->rec );
}

/*******************************************************************************

*******************************************************************************/

bool begin_ebml_master_o( OEbmlBuilder* b, oEbmlId id, oEbmlSize size )
{
   must_exist_c_( b );

   oEbmlBuilderMarker marker = ebml_builder_marker_o( id, b->rec->pos );
   if ( not put_ebml_builder_marker_o( &(b->pile), marker ) )
   {
      return false;
   }

   int64_t oldPos = b->rec->pos;
   if ( not record_ebml_id_o( b->rec, id ) or
        not record_ebml_size_o( b->rec, size ) )
   {
      oEbmlBuilderMarker marker;
      take_ebml_builder_marker_o( &(b->pile), b->pile.s-1, &marker );
      move_recorder_to_c( b->rec, oldPos );
      return false;
   }

   return true;
}

static cVarBytes recorder_sub_bytes( cRecorder rec[static 1],
                                     int64_t min,
                                     int64_t max )
{
   cVarBytes invalid = invalid_c_();
   int64_t initPos = rec->pos;

   if ( not move_recorder_to_c( rec, min ) )
   {
      move_recorder_to_c( rec, initPos );
      return invalid;
   }
   cByte* beg = rec->mem;

   if ( not move_recorder_to_c( rec, max ) )
   {
      move_recorder_to_c( rec, initPos );
      return invalid;
   }
   cByte* end = rec->mem;

   move_recorder_to_c( rec, initPos );
   return (cVarBytes)atween_c_( beg, end );
}

bool finish_ebml_master_o( OEbmlBuilder* b )
{
   must_exist_c_( b );

   oEbmlBuilderMarkerPile* pile = &(b->pile);
   cScanner* sca = &scanner_copy_c_( b->rec );
   cRange scope;

   scope.max = b->rec->pos;
   once_c_( xsdlfjk )
   {
      oEbmlBuilderMarker marker;
      if ( not take_ebml_builder_marker_o( pile, pile->s-1, &marker ) ) break;

      if ( not move_scanner_to_c( sca, marker.pos ) ) break;

      oEbmlId id;
      if ( not scan_ebml_id_o( sca, &id ) ) break;

      int64_t sizePos = sca->pos;
      oEbmlSize tmpSize;
      if ( not scan_ebml_size_o( sca, &tmpSize ) ) break;

      scope.min = sca->pos;
      int64_t valSize = scope.max - scope.min;
      oEbmlSize size = encode_ebml_size_o( valSize );

      int64_t sizeDiff = ebml_size_length_o( size ) - ebml_size_length_o( tmpSize );
      if ( sizeDiff < 0 )
      {
         cVarBytes bytes = recorder_sub_bytes( b->rec, scope.min+sizeDiff, scope.max );
         if ( is_invalid_c_( bytes ) ) break;
         shift_bytes_c( bytes, sizeDiff );
         scope.max += sizeDiff;
      }
      else if ( sizeDiff > 0 )
      {
         if ( sizeDiff > b->rec->space )
         {
            int64_t newCap = recorder_cap_c( b->rec ) * 2;
            if ( not realloc_recorder_mem_c( b->rec, newCap ) ) break;
         }
         cVarBytes bytes = recorder_sub_bytes( b->rec, scope.min, scope.max+sizeDiff );
         if ( is_invalid_c_( bytes ) ) break;
         shift_bytes_c( bytes, sizeDiff );
         scope.max += sizeDiff;
      }

      move_recorder_to_c( b->rec, sizePos );
      if ( not record_ebml_size_o( b->rec, size ) ) break;

      return move_recorder_to_c( b->rec, scope.max );
   }

   return false;
}

/*******************************************************************************
 append
*******************************************************************************/

static bool append( OEbmlBuilder* b, oEbmlId id, cBytes bytes )
{
   oEbmlSize size = encode_ebml_size_o( bytes.s );
   int64_t len = ebml_id_length_o( id ) + ebml_size_length_o( size ) + bytes.s;

   if ( not ensure_recorder_space_c( b->rec, len ) )
   {
      return false;
   }

   return record_ebml_id_o( b->rec, id ) and
      record_ebml_size_o( b->rec, size ) and
      record_bytes_c( b->rec, bytes );
}

bool append_ebml_element_o( OEbmlBuilder* b, oEbmlElement const elem[static 1] )
{
   must_exist_c_( b );
   return append( b, elem->id, elem->bytes );
}

bool append_embl_int_o( OEbmlBuilder* b, oEbmlId id, int64_t val )
{
   must_exist_c_( b );

   cRecorder* rec = &recorder_c_( 16 );
   {
      int8_t i8 = 0;
      int16_t i16 = 0;
      int32_t i32 = 0;
      if ( int64_to_int8_c( val, &i8 ) )
      {
         record_int8_c( rec, i8 );
      }
      else if ( int64_to_int16_c( val, &i16 ) )
      {
         record_int16_c( rec, swap_int16_to_c( i16, c_BigEndian ) );
      }
      else if ( int64_to_int32_c( val, &i32 ) )
      {
         record_int32_c( rec, swap_int32_to_c( i32, c_BigEndian ) );
      }
      else
      {
         record_int64_c( rec, swap_int64_to_c( val, c_BigEndian ) );
      }
   }

   return append( b, id, recorded_bytes_c( rec ) );
}

bool append_ebml_uint_o( OEbmlBuilder* b, oEbmlId id, uint64_t val )
{
   must_exist_c_( b );

   cRecorder* rec = &recorder_c_( 8 );
   {
      uint8_t u8 = 0;
      uint16_t u16 = 0;
      uint32_t u32 = 0;
      if ( uint64_to_uint8_c( val, &u8 ) )
      {
         record_uint8_c( rec, u8 );
      }
      else if ( uint64_to_uint16_c( val, &u16 ) )
      {
         record_uint16_c( rec, swap_uint16_to_c( u16, c_BigEndian ) );
      }
      else if ( uint64_to_uint32_c( val, &u32 ) )
      {
         record_uint32_c( rec, swap_uint32_to_c( u32, c_BigEndian ) );
      }
      else
      {
         record_uint64_c( rec, swap_uint64_to_c( val, c_BigEndian ) );
      }
   }

   return append( b, id, recorded_bytes_c( rec ) );
}

bool append_ebml_float_o( OEbmlBuilder* b, oEbmlId id, double val )
{
   must_exist_c_( b );

   cRecorder* rec = &recorder_c_( 8 );
   {
      float f;
      if ( double_to_float_c( val, &f ) )
      {
         record_float_c( rec, swap_float_to_c( f, c_BigEndian ) );
      }
      else
      {
         record_double_c( rec, swap_double_to_c( val, c_BigEndian ) );
      }
   }
   return append( b, id, recorded_bytes_c( rec ) );
}

bool append_ebml_string_o( OEbmlBuilder* b, oEbmlId id, cChars val )
{
   must_exist_c_( b );
   return append( b, id, (cBytes){ val.s, (cByte const*)val.v } );
}

bool append_ebml_utf8_o( OEbmlBuilder* b, oEbmlId id, cChars val )
{
   must_exist_c_( b );
   return append( b, id, (cBytes){ val.s, (cByte const*)val.v } );
}

bool append_ebml_date_o( OEbmlBuilder* b, oEbmlId id, oEbmlDate val )
{
   must_exist_c_( b );
   cRecorder* rec  = &recorder_c_( 8 );
   record_ebml_date_o( rec, val );
   return append( b, id, recorded_bytes_c( rec ) );
}

bool append_ebml_binary_o( OEbmlBuilder* b, oEbmlId id, cBytes val )
{
   must_exist_c_( b );
   return append( b, id, val );
}

bool append_empty_ebml_o( OEbmlBuilder* b, oEbmlId id )
{
   must_exist_c_( b );
   return append( b, id, (cBytes)empty_c_() );
}
