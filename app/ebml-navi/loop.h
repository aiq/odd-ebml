#ifndef EBML_NAVI_LOOP_H
#define EBML_NAVI_LOOP_H

#include "dfs.h"
#include "show_details.h"
#include "clingo/io/read.h"

static char const* commands =
   " - go [b]ack\n"
   " - show [d]etails\n"
   " - show [h]istory\n"
   " - show [r]aw\n"
   " - [s]earch for {ID}"
   " - [n]ext sibling\n"
   " - first [c]hild\n"
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

   println_c_( "{s}[{u32:x}] @{i64} from type {s} with {i64} bytes",
               decl->name, decl->id.raw, m->pos, stringify_ebml_type_c( decl->type ), m->size );
   *declPtr = decl;
   return true;
}

static bool loop( NaviCtx ctx[static 1] )
{
   println_c_( "commands ->\n{s}\n", commands );

   oEbmlTrav* trav = &start_ebml_trav_o_( ctx->file );
   oEbmlDecl const* decl;
   if ( not visit_adj_ebml_marker_o( trav, ctx->es ) ) return ctx->es->err->type == &C_Eof;
   if ( not handle_decl( ctx->declMap, &(trav->marker), &decl ) ) return false;
   print_c_( "> " );

   cVarChars line = scalars_c_( 248, char );
   bool fin = true;
   while ( fget_line_c( stdin, 248, &line, &fin ) )
   {
      if ( not fin )
      {
         println_c_( "to much input" );
         continue;
      }

      cChars inp = as_c_( cChars, line );
      if ( chars_is_c( inp, "b" ) ) //------------------------------------------
      {
         if ( is_empty_c_( ctx->history ) )
         {
            println_c_( "no history where you can go back" );
            continue;
         }
         trav->marker = last_c_( ctx->history );
         ctx->history.s -= 1;
         if ( not handle_decl( ctx->declMap, &(trav->marker), &decl ) )
            return false;
      }
      else if ( chars_is_c( inp, "h" ) ) //-------------------------------------
      {
         if ( is_empty_c_( ctx->history ) )
         {
            println_c_( "no history to show" );
            continue;
         }
         println_c_( "history with {i64} elements", ctx->history.s );
         for_each_c_( i, oEbmlMarker const*, m, ctx->history )
         {
            oEbmlDecl const* decl = get_from_ebml_decl_map_o( ctx->declMap,
                                                              m->id );
            times_c_( i, n ) { print_c_( " " ); };
            println_c_(
               "- {u32:x} {s} @ {i64}",
               m->id.raw, decl->name, m->pos
            );
         }
      }
      else if ( chars_is_c( inp, "d" ) ) //-------------------------------------
      {
         if ( not show_details( trav, decl->type, ctx ) ) return false;
      }
      else if ( chars_is_c( inp, "n" ) ) //-------------------------------------
      {
         oEbmlMarker prev = trav->marker;
         if ( not visit_next_ebml_marker_o( trav, ctx->es ) )
         {
            if ( feof( trav->file ) )
            {
               println_c_( "we reached the end of file" );
               continue;
            }
            else
            {
               push_file_error_c( ctx->es, trav->file );
               return false;
            }
         }
         if ( not handle_decl( ctx->declMap, &(trav->marker), &decl ) )
            return false;

         put_ebml_marker_o( &(ctx->history), prev );
      }
      else if ( chars_is_c( inp, "c" ) ) //-------------------------------------
      {
         if ( decl->type != o_EbmlMaster )
         {
            println_c_( "[c] works only on master elements" );
            continue;
         }
         oEbmlMarker prev = trav->marker;
         if ( not visit_adj_ebml_marker_o( trav, ctx->es ) )
         {
            if ( feof( trav->file ) )
            {
               println_c_( "we reached the end of file" );
               continue;
            }
            else
            {
               push_file_error_c( ctx->es, trav->file );
               return false;
            }
         }
         if ( not handle_decl( ctx->declMap, &(trav->marker), &decl ) )
            return false;

         put_ebml_marker_o( &(ctx->history), prev );
      }
      else if ( chars_is_c( inp, "r" ) ) //-------------------------------------
      {
         cVarBytes buf = heap_slice_c_( trav->marker.size, cByte );
         if ( buf.v == NULL ) return false;
      
         bool ok = fget_ebml_bytes_o( trav, &buf );
         if ( ok ) println_c_( "r: {bs}", as_c_( cBytes, buf ) );
         free( buf.v );
         if ( not ok ) return push_ebml_trav_error_o( ctx->es, trav );
      }
      else if ( chars_starts_with_c_( inp, "s " ) ) //--------------------------
      {
         cScanner* sca = &make_scanner_c_( inp.s, inp.v );
         oEbmlId id;
         if ( not read_c_( sca, "s {u32:x}", &(id.raw) ) )
         {
            println_c_(
               "not able to parse ID from {cs:Q}",
               mid_c_( cChars, inp, 2 )
            );
            continue;
         }
         println_c_( "search for ID: {u32:x}", id.raw );
         bool found = false;
         oEbmlMarker prev = trav->marker;
         while ( visit_next_dfs( trav, ctx ) )
         {
            if ( eq_ebml_id_o( trav->marker.id, id ) )
            {
               found = true;
               if ( not handle_decl( ctx->declMap, &(trav->marker), &decl ) )
                  return false;

               put_ebml_marker_o( &(ctx->history), prev );
               break;
            }
         }
         if ( not found )
         {
            println_c_( "not able to find ID: {u32:x}", id.raw );
            if ( feof( trav->file ) )
            {
               println_c_( "we reached the end of file" );
               continue;
            }
            else if ( ferror( trav->file ) )
            {
               push_file_error_c( ctx->es, trav->file );
               return false;
            }
         }
      }
      else if ( chars_is_c( inp, "q" ) ) //-------------------------------------
      {
         break;
      }
      else
      {
         println_c_( "unknown command {cs:Q}, use: \n{s}\n", inp, commands );
      }
      print_c_( "> " );
   }

   return true;
}

#endif