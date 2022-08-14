#ifndef EBML_NAVI_SHOW_DETAILS_H
#define EBML_NAVI_SHOW_DETAILS_H

#include "ctx.h"

static bool show_details( oEbmlTrav trav[static 1],
                          o_EbmlType type,
                          NaviCtx ctx[static 1] )
{
   oEbmlDecl const* decl = get_from_ebml_decl_map_o( ctx->declMap, trav->marker.id );
   if ( decl == NULL )
   {
      push_lit_error_c( ctx->es, "not able to resolve ebml id" );
   }
   if ( type == o_EbmlInt )
   {
      int64_t i64;
      if ( not fget_ebml_int_o( trav, &i64 ) )
         return push_ebml_trav_error_o( ctx->es, trav ); 

      return println_c_( "d: {i64}", i64 );
   }
   else if ( type == o_EbmlUint )
   {
      uint64_t u64;
      if ( not fget_ebml_uint_o( trav, &u64 ) )
         return push_ebml_trav_error_o( ctx->es, trav ); 

      return println_c_( "d: {u64}", u64 );
   }
   else if ( type == o_EbmlFloat )
   {
      double d;
      if ( not fget_ebml_float_o( trav, &d ) )
         return push_ebml_trav_error_o( ctx->es, trav );

      return println_c_( "d: {d}", d );
   }
   else if ( type == o_EbmlString )
   {
      cVarChars buf = heap_slice_c_( trav->marker.size, char );
      if ( buf.v == NULL ) return false;
      
      bool ok = fget_ebml_string_o( trav, &buf );
      println_c_( "d: {cs}", as_chars_c( buf ) );
      free( buf.v );
      return ok ? true
                : push_ebml_trav_error_o( ctx->es, trav );
   }
   else if ( type == o_EbmlUtf8 )
   {
      cVarChars buf = heap_slice_c_( trav->marker.size, char );
      if ( buf.v != NULL ) return false;
      
      bool ok = fget_ebml_utf8_o( trav, &buf );
      println_c_( "d: {cs}", as_chars_c( buf ) );
      free( buf.v );
      return ok ? true
                : push_ebml_trav_error_o( ctx->es, trav );
   }
   else if ( type == o_EbmlDate )
   {
      oEbmlDate date;
      if ( fget_ebml_date_o( trav, &date ) )
         return push_ebml_trav_error_o( ctx->es, trav );
   
      println_scope_c_( rec, 248 )
      {
         record_chars_c_( rec, "d: " );
         write_ebml_date_o_( rec, date );
      }
      return true;
   }
   else if ( type == o_EbmlMaster )
   {
      oEbmlTrav subTrav = *trav;
      int64_t i = 1;
      while ( visit_ebml_child_o( trav, &subTrav, ctx->es ) )
      {
         oEbmlDecl const* decl = get_from_ebml_decl_map_o( ctx->declMap, subTrav.marker.id );
         if ( decl == NULL )
         {
            println_c_( "{i64:(8r )}. {u32:x} is unknown", i, subTrav.marker.id );
         }
         else
         {
            println_c_( "{i64:(8r )}. {u32:x} {s} / {s}",
               i, subTrav.marker.id, decl->name, stringify_ebml_type_c( decl->type )
            );
         }
         ++i;
      }
      return ferror( subTrav.file ) == 0;
   }
   else if ( type == o_EbmlBinary )
   {
      return println_c_( "no details for binaries" );
   }

   return false;
}

#endif