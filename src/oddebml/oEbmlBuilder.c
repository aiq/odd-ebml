#include "oddebml/oEbmlBuilder.h"

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
#include "oddebml/oEbmlSize.h"

/*******************************************************************************
 internal
*******************************************************************************/



/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct OEbmlBuilder
{
   cRecorder rec;
   int64_t len;
};

static inline void cleanup( void* instance )
{
   OEbmlBuilder* b = instance;
   reset_recorder_c( &(b->rec) );

   if ( b->rec.mem )
   {
      free( b->rec.mem );
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

   cObjectInfo const info = default_object_info_c_( &O_EbmlBuilderMeta );
   OEbmlBuilder* result = alloc_object_c_( OEbmlBuilder, &info );
   if ( result == NULL )
   {
      return NULL;
   }

   if ( not alloc_recorder_mem_c( &(result->rec), cap ) )
   {
      release_c( result );
      return NULL;
   }
   result->len = 0;

   return result;
}

OEbmlBuilder* new_ebml_builder_o( void )
{
   return make_ebml_builder_o( 512 );
}

/*******************************************************************************

*******************************************************************************/

bool begin_ebml_master_o( OEbmlBuilder* b, oEbmlId id )
{
   must_exist_c_( b );
   return false;
}

bool finish_ebml_master_o( OEbmlBuilder* b )
{
   must_exist_c_( b );
   return false;
}

/*******************************************************************************
 append
*******************************************************************************/

static bool append( OEbmlBuilder* b, oEbmlId id, cBytes bytes )
{
   cRecorder* rec = &(b->rec);

   oEbmlSize size = encode_ebml_size_o( bytes.s );
   int64_t len = ebml_id_length_o( id ) + ebml_size_length_o( size ) + bytes.s;

   if ( rec->space < len )
   {
      int64_t oldSize = max_c_( recorder_cap_c( rec ), bytes.s );
      int64_t const newSize = oldSize * 2;
      if ( not realloc_recorder_mem_c( rec, newSize ) )
      {
         return false;
      }
   }

   return record_ebml_id_o( rec, id ) and
      record_ebml_size_o( rec, size ) and
      record_bytes_c( rec, bytes );
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
   return append( b, id, bytes_c( val.s, (cByte const*)val.v ) );
}

bool append_ebml_utf8_o( OEbmlBuilder* b, oEbmlId id, cChars val )
{
   must_exist_c_( b );
   return append( b, id, bytes_c( val.s, (cByte const*)val.v ) );
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