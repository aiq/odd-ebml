#include "oddebml/oEbmlTrav.h"

#include "clingo/io/FILE.h"
#include "oddebml/oEbmlElement.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool visit_adj_ebml_marker_o( oEbmlTrav trav[static 1] )
{
   if ( fsetpos( trav->file, &(trav->marker.pos) ) != 0 ) return false;

   return fread_ebml_marker_o( trav->file, &(trav->marker) );
}

bool visit_next_ebml_marker_o( oEbmlTrav trav[static 1] )
{
   fpos_t next = trav->marker.pos + trav->marker.size;
   if ( fsetpos( trav->file, &next ) != 0 ) return false;

   return fread_ebml_marker_o( trav->file, &(trav->marker) );
}

/*******************************************************************************

*******************************************************************************/

bool visit_ebml_child_o( oEbmlTrav const master[static 1],
                         oEbmlTrav child[static 1] )
{
   must_be_c_( master->file == child->file );

   if ( not ebml_marker_covers_o( &(master->marker), &(child->marker) ) )
      return false;

   if ( master->marker.pos == child->marker.pos )
   {
      return visit_adj_ebml_marker_o( child ) and
             ebml_marker_covers_o( &(master->marker), &(child->marker) );
   }

   return visit_next_ebml_marker_o( child ) and
          ebml_marker_covers_o( &(master->marker), &(child->marker) );
}

/*******************************************************************************

*******************************************************************************/

bool fread_ebml_bytes_o( oEbmlTrav trav[static 1],
                         cVarBytes buf[static 1] )
{
   if ( trav->marker.size == 0 )
   {
      buf->s = 0;
      return true;
   }

   if ( fsetpos( trav->file, &(trav->marker.pos) ) != 0 ) return false;

   if ( buf->s < trav->marker.size ) return false;

   buf->s = trav->marker.size;
   return fread_bytes_c( trav->file, buf );
}

bool fread_ebml_int_o( oEbmlTrav trav[static 1],
                       int64_t val[static 1] )
{
   if ( not in_range_c_( 0, trav->marker.size, 8 ) ) return false;

   cVarBytes buf = scalars_c_( 8, cByte );
   if ( not fread_ebml_bytes_o( trav, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( trav->marker.id, as_bytes_c( buf ) );
   return ebml_as_int_o( &elem, val );
}

bool fread_ebml_uint_o( oEbmlTrav trav[static 1],
                        uint64_t val[static 1] )
{
   if ( not in_range_c_( 0, trav->marker.size, 8 ) ) return false;

   cVarBytes buf = scalars_c_( 8, cByte );
   if ( not fread_ebml_bytes_o( trav, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( trav->marker.id, as_bytes_c( buf ) );
   return ebml_as_uint_o( &elem, val );
}

bool fread_ebml_float_o( oEbmlTrav trav[static 1],
                         double val[static 1] )
{
   if ( not in_range_c_( 0, trav->marker.size, 8 ) ) return false;

   cVarBytes buf = scalars_c_( 8, cByte );
   if ( not fread_ebml_bytes_o( trav, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( trav->marker.id, as_bytes_c( buf ) );
   return ebml_as_float_o( &elem, val );
}

bool fread_ebml_string_o( oEbmlTrav trav[static 1],
                          cVarChars val[static 1] )
{
   cVarBytes buf = var_bytes_c( val->s, (void*)val->v );
   if ( not fread_ebml_bytes_o( trav, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( trav->marker.id, as_bytes_c( buf ) );
   cChars chars;
   bool res = ebml_as_string_o( &elem, &chars );
   if ( res )
   {
      val->s = chars.s;
   }
   return res;
}

bool fread_ebml_utf8_o( oEbmlTrav trav[static 1],
                        cVarChars val[static 1] )
{
   cVarBytes buf = var_bytes_c( val->s, (void*)val->v );
   if ( not fread_ebml_bytes_o( trav, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( trav->marker.id, as_bytes_c( buf ) );
   cChars chars;
   bool res = ebml_as_utf8_o( &elem, &chars );
   if ( res )
   {
      val->s = chars.s;
   }
   return res;
}

bool fread_ebml_date_o( oEbmlTrav trav[static 1],
                        oEbmlDate val[static 1] )
{
   if ( not in_range_c_( 0, trav->marker.size, 8 ) ) return false;

   cVarBytes buf = scalars_c_( 8, cByte );
   if ( not fread_ebml_bytes_o( trav, &buf ) ) return false;

   oEbmlElement elem = ebml_element_o_( trav->marker.id, as_bytes_c( buf ) );
   return ebml_as_date_o( &elem, val );
}