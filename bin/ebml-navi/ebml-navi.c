#include "clingo/container/map.h"
#include "clingo/io/FILE.h"
#include "clingo/io/print.h"
#include "oddebml/oEbmlDecl.h"
#include "oddebml/OEbmlDeclMap.h"
#include "oddebml/oEbmlTrav.h"
#include "oddebml/oEbmlMarker.h"

#include "loop.h"
#include "mkv_decl.h"

static uint64_t hash_ebml_marker_o( oEbmlMarker const m[static 1] )
{
   return uint64_c_( m->pos );
}

VAL_VAL_MAP_IMPL_C_(
   static __attribute__((unused)),                    // Static
   ParentMarkerMap,     // MapType
   ParentMarkerMapRow,  // RowType
   oEbmlMarker,         // KeyType
   oEbmlMarker,         // ValType
   parent_marker_map_o, // FuncName
   ParentMarkerMapMeta, // Meta
   hash_ebml_marker_o,  // HashFunc
   cmp_ebml_marker_o,   // CmpFunc
   do_ref_c_            // DoRef
)

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

   if ( not loop( file, map ) )
   {
      push_file_error_and_close_c( es, file );
      println_c_( "we have a problem: {e}", es->err );
      return EXIT_FAILURE;
   }

   println_c_( "bye bye {cs:Q}", filePath );
   if ( not close_file_c( file, es ) )
   {
      println_c_( "not able to close file {cs:Q}: {e}", filePath, es->err );
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
