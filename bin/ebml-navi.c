#include "clingo/container/map.h"
#include "clingo/io/FILE.h"
#include "clingo/io/print.h"
#include "oddebml/oEbmlDecl.h"
#include "oddebml/OEbmlDeclMap.h"
#include "oddebml/oEbmlMarker.h"

#include "mkvdecl.h"

static char const* commands = "[d]etails / [n]ext sibling / first [c]hild / [q]uit";

static cChars get_file_path_arg( int argc,
                                 char* argv[])
{
   if ( argc < 2 )
   {
      println_c_( "missing ebml file path" );
      return (cChars)invalid_slice_c_();
   } else if ( argc > 2 )
   {
      println_c_( "expect only one ebml file path" );
      return (cChars)invalid_slice_c_();
   }
   return c_c( argv[1] );
}

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

static bool navi( FILE* file, OEbmlDeclMap* map )
{
   println_c_( "\ncommands -> {s}\n", commands );

   oEbmlMarker marker;
   oEbmlDecl const* decl;
   if ( not fread_curr_ebml_marker_o( file, &marker ) ) return feof( file );
   if ( not handle_decl( map, &marker, &decl ) ) return false;

   cVarChars line = scalars_c_( 248, char );
   bool fin = true;
   while ( fread_line_c( stdin, 248, &line, &fin ) )
   {
      if ( not fin ) return false;

      cChars inp = as_chars_c( line );
      if ( chars_is_c( inp, "d" ) )
      {

      }
      else if ( chars_is_c( inp, "n" ) )
      {
         if ( not fread_ebml_sibling_marker_o( file, &marker, &marker ) ) return feof( file );
         if ( not handle_decl( map, &marker, &decl ) ) return false;
      }
      else if ( chars_is_c( inp, "c" ) )
      {
         if ( decl->type != o_EbmlMaster )
         {
            println_c_( "[c] works only on master elements" );
            continue;
         }
         if ( not fread_ebml_child_marker_o( file, &marker, &marker ) ) return feof( file );
         if ( not handle_decl( map, &marker, &decl ) ) return false;
      }
      else if ( chars_is_c( inp, "q" ) )
      {
         break;
      }
      else
      {
         println_c_( "unknown command {cs:Q}, use: {s}", inp, commands );
      }
   }

   return true;
}

#define EXIT_IF( Expr ) if ( Expr ) return EXIT_FAILURE;

int main( int argc, char* argv[] )
{
   cErrorStack* es = &error_stack_c_( 1024 );

   cChars filePath = get_file_path_arg( argc, argv );
   EXIT_IF( is_invalid_c_( filePath ) );

   OEbmlDeclMap* map = new_ebml_decl_map_o();
   EXIT_IF( map == NULL );

   oVarEbmlDeclSlice declBuf = structs_c_( 300, oEbmlDecl );
   fill_ebml_decl_map_o( map, get_ebml_header_decl_o( declBuf ) );
   fill_ebml_decl_map_o( map, get_ebml_mkv_decl( declBuf ) );

   FILE* file = ropen_file_c( filePath, es );
   if ( file == NULL )
   {
      println_c_( "not able to open file {cs:Q}: {e}", filePath, es->err );
      return EXIT_FAILURE;
   }

   if ( not navi( file, map ) )
   {
      push_file_error_and_close_c( es, file );
      println_c_( "we have a problem: {e}", es->err );
      return EXIT_FAILURE;
   }

   println_c_( "bye bye" );
   if ( not close_file_c( file, es ) )
   {
      println_c_( "not able to close file {cs:Q}: {e}", filePath, es->err );
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
