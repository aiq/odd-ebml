#ifndef EBML_NAVI_LOOP_H
#define EBML_NAVI_LOOP_H

#include "show_details.h"

static char const* commands =
   " - show [d]etails\n"
   " - show [r]aw\n"
   " - [n]ext sibling\n"
   " - first [c]hild\n"
   " - [b]ack to master\n"
   " - [q]uit";

static bool handle_decl( OEbmlDeclMap* map,
                         oEbmlMarker const m[static 1],
                         oEbmlDecl const* declPtr[static 1] )
{
   *declPtr = NULL;
   oEbmlDecl const* decl = get_from_ebml_decl_map_o( map, m->id );
   if ( decl == NULL )
   {
      println_c_( "unknown id: {u32:x}", m->id.raw );
      return false;
   }

   println_c_( "    {s}[{u32:x}] @{i64} from type {s} with {u64} bytes",
               decl->name, decl->id.raw, m->pos, stringify_ebml_type_c( decl->type ), m->size );
   *declPtr = decl;
   return true;
}

static bool loop( FILE* file, OEbmlDeclMap* map )
{
   println_c_( "commands ->\n{s}\n", commands );

   oEbmlTrav* trav = &start_ebml_trav_o_( file );
   oEbmlDecl const* decl;
   if ( not visit_adj_ebml_marker_o( trav ) ) return feof( file );
   if ( not handle_decl( map, &(trav->marker), &decl ) ) return false;

   cVarChars line = scalars_c_( 248, char );
   bool fin = true;
   while ( fread_line_c( stdin, 248, &line, &fin ) )
   {
      if ( not fin ) return false;

      cChars inp = as_chars_c( line );
      if ( chars_is_c( inp, "b" ) )
      {
         
      }
      else if ( chars_is_c( inp, "d" ) )
      {
         if ( not show_details( trav, decl->type, map ) ) return false;
      }
      else if ( chars_is_c( inp, "n" ) )
      {
         if ( not visit_next_ebml_marker_o( trav ) ) return feof( file );
         if ( not handle_decl( map, &(trav->marker), &decl ) ) return false;
      }
      else if ( chars_is_c( inp, "c" ) )
      {
         if ( decl->type != o_EbmlMaster )
         {
            println_c_( "[c] works only on master elements" );
            continue;
         }
         if ( not visit_adj_ebml_marker_o( trav ) ) return feof( file );
         if ( not handle_decl( map, &(trav->marker), &decl ) ) return false;
      }
      else if ( chars_is_c( inp, "r" ) )
      {
         cVarBytes buf = heap_slice_c_( trav->marker.size, cByte );
         if ( buf.v == NULL ) return false;
      
         bool res = fread_ebml_bytes_o( trav, &buf ) and
                    println_c_( "r: {bs}", as_bytes_c( buf ) );
         free( buf.v );
         if ( not res ) return false;
      }
      else if ( chars_is_c( inp, "q" ) )
      {
         break;
      }
      else
      {
         println_c_( "unknown command {cs:Q}, use: \n{s}\n", inp, commands );
      }
   }

   return true;
}

#endif