#include "clingo/io/print.h"
#include "oddebml/oEbmlDecl.h"
#include "oddebml/oEbmlTrav.h"
#include "oddebml/oEbmlMarker.h"

#include "loop.h"

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

   NaviCtx ctx;
   if ( not init_ctx( &ctx, filePath, es ) )
   {
      println_c_( "ERROR: {e}", es->err );
      return EXIT_FAILURE;
   }

   if ( not loop( &ctx ) )
   {
      println_c_( "we have a problem: {e}", es->err );
      close_file_c( ctx.file, es );
      return EXIT_FAILURE;
   }

   println_c_( "bye bye {cs:Q}", filePath );
   deref_ctx( &ctx, es );

   return EXIT_SUCCESS;
}
