#include "oddebml/oEbmlTrav.h"

#include "clingo/io/c_ImpExpError.h"
#include "clingo/io/FILE.h"
#include "oddebml/oEbmlElement.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool visit_adj_ebml_marker_o( oEbmlTrav trav[static 1],
                              cErrorStack es[static 1] )
{
   if ( fsetpos( trav->file, &(trav->marker.pos) ) != 0 )
   {
      return push_file_error_c( es, trav->file );
   }

   return fscan_ebml_marker_o( trav->file, &(trav->marker), es );
}

bool visit_next_ebml_marker_o( oEbmlTrav trav[static 1],
                               cErrorStack es[static 1] )
{
   fpos_t next = trav->marker.pos + trav->marker.size;
   if ( fsetpos( trav->file, &next ) != 0 )
   {
      return push_file_error_c( es, trav->file );
   }

   return fscan_ebml_marker_o( trav->file, &(trav->marker), es );
}

/*******************************************************************************

*******************************************************************************/

bool visit_ebml_child_o( oEbmlTrav const master[static 1],
                         oEbmlTrav child[static 1],
                         cErrorStack es[static 1] )
{
   must_be_c_( master->file == child->file );

   if ( not ebml_marker_covers_o( &(master->marker), &(child->marker) ) )
      return false;

   if ( master->marker.pos == child->marker.pos )
   {
      return visit_adj_ebml_marker_o( child, es ) and
             ebml_marker_covers_o( &(master->marker), &(child->marker) );
   }

   return visit_next_ebml_marker_o( child, es ) and
          ebml_marker_covers_o( &(master->marker), &(child->marker) );
}

/*******************************************************************************

*******************************************************************************/

#define NotEnoughSpaceErrorCode_ (c_CustomImpExpError+1)
#define FileErrorCode_ (c_CustomImpExpError+2)
static inline bool set_error( oEbmlTrav trav[static 1], int err )
{
   trav->err = err;
   return false;
}

bool fget_ebml_bytes_o( oEbmlTrav trav[static 1], cVarBytes buf[static 1] )
{
   if ( trav->marker.size == 0 )
   {
      buf->s = 0;
      return true;
   }

   if ( fsetpos( trav->file, &(trav->marker.pos) ) != 0 )
   {
      return set_error( trav, FileErrorCode_ );
   }

   if ( buf->s < trav->marker.size )
   {
      return set_error( trav, NotEnoughSpaceErrorCode_ );
   }

   buf->s = trav->marker.size;
   if ( not fget_bytes_c( trav->file, buf ) )
   {
      return set_error( trav, FileErrorCode_ );
   }

   return true;
}

bool fget_ebml_int_o( oEbmlTrav trav[static 1], int64_t val[static 1] )
{
   if ( not in_range_c_( 0, trav->marker.size, 8 ) )
   {
      return set_error( trav, c_NotAbleToScanValue );
   }

   cVarBytes buf = scalars_c_( 8, cByte );
   if ( not fget_ebml_bytes_o( trav, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( trav->marker.id, as_c_( cBytes, buf ) );
   return ebml_as_int_o( &elem, val );
}

bool fget_ebml_uint_o( oEbmlTrav trav[static 1], uint64_t val[static 1] )
{
   if ( not in_range_c_( 0, trav->marker.size, 8 ) )
   {
      return set_error( trav, c_NotAbleToScanValue );
   }

   cVarBytes buf = scalars_c_( 8, cByte );
   if ( not fget_ebml_bytes_o( trav, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( trav->marker.id, as_c_( cBytes, buf ) );
   return ebml_as_uint_o( &elem, val );
}

bool fget_ebml_float_o( oEbmlTrav trav[static 1], double val[static 1] )
{
   if ( trav->marker.size != 0 and
        trav->marker.size != 4 and
        trav->marker.size != 8 )
   {
      return set_error( trav, c_NotAbleToScanValue );
   }

   cVarBytes buf = scalars_c_( 8, cByte );
   if ( not fget_ebml_bytes_o( trav, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( trav->marker.id, as_c_( cBytes, buf ) );
   return ebml_as_float_o( &elem, val );
}

bool fget_ebml_string_o( oEbmlTrav trav[static 1], cVarChars val[static 1] )
{
   cVarBytes buf = { val->s, (void*)val->v };
   if ( not fget_ebml_bytes_o( trav, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( trav->marker.id, as_c_( cBytes, buf ) );
   cChars chars;
   if ( not ebml_as_string_o( &elem, &chars ) ) return false;

   val->s = chars.s;
   return true;
}

bool fget_ebml_utf8_o( oEbmlTrav trav[static 1], cVarChars val[static 1] )
{
   cVarBytes buf = { val->s, (void*)val->v };
   if ( not fget_ebml_bytes_o( trav, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( trav->marker.id, as_c_( cBytes, buf ) );
   cChars chars;
   if ( not ebml_as_utf8_o( &elem, &chars ) ) return false;

   val->s = chars.s;
   return true;
}

bool fget_ebml_date_o( oEbmlTrav trav[static 1], oEbmlDate val[static 1] )
{
   if ( trav->marker.size != 0 and trav->marker.size != 8 )
   {
      return set_error( trav, c_NotAbleToScanValue );
   }

   cVarBytes buf = scalars_c_( 8, cByte );
   if ( not fget_ebml_bytes_o( trav, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( trav->marker.id, as_c_( cBytes, buf ) );
   return ebml_as_date_o( &elem, val );
}

/*******************************************************************************

*******************************************************************************/

bool push_ebml_trav_error_o( cErrorStack es[static 1],
                             oEbmlTrav trav[static 1] )
{
   if ( trav->err <= c_CustomImpExpError )
   {
      return push_imp_exp_error_c( es, trav->err );
   }
   else if ( trav->err == NotEnoughSpaceErrorCode_ )
   {
      return push_error_c_( es, &C_NotEnoughBufferError );
   }
   else if ( trav->err == FileErrorCode_)
   {
      return push_file_error_c( es, trav->file );
   }

   return push_lit_error_c( es, "unkown error code" );
}