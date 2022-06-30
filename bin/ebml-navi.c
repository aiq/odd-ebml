#include "clingo/container/map.h"
#include "clingo/io/FILE.h"
#include "clingo/io/print.h"
#include "oddebml/oEbmlDecl.h"
#include "oddebml/OEbmlDeclMap.h"

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

int main( int argc, char* argv[] )
{
   cErrorStack* es = &error_stack_c_( 1024 );

   cChars filePath = get_file_path_arg( argc, argv );
   must_be_c_( not is_invalid_c_( filePath ) );

   OEbmlDeclMap* map = new_ebml_decl_map_o();
   must_exist_c_( map );

   fill_ebml_decl_map_o( map, ebml_header_decl_o() );

   FILE* file = ropen_file_c( filePath, es );
   if ( file == NULL )
   {
      println_c_( "not able to open file {cs:Q}: {e}", filePath, es->err );
      return EXIT_FAILURE;
   }

   

   if ( not close_file_c( file, es ) )
   {
      println_c_( "not able to close file {cs:Q}: {e}", filePath, es->err );
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}