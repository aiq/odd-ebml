#include "clingo/io/print.h"
#include "clingo/io/read_type.h"
#include "clingo/io/write_type.h"
#include "oddebml/oEbmlSize.h"

static void print_usage( void )
{
   println_c_( "usage: ebml-vint $action $format <value>" );
   println_c_( "$action - use dec or enc" );
   println_c_( "$format - use -x or -d" );
}

typedef struct
{
   cChars action;
   char const* format;
   cScanner valueSca;
} argsDef;

bool init_args( int argc, char* argv[], argsDef args[static 1] )
{
   if ( argc < 4 )
   {
      println_c_( "not enough arguments: number of arguments {i64}", argc );
      return false;
   }
   
   if ( argc > 4 )
   {
      println_c_( "to much arguments: number of arguments {i64}", argc );
      return false;
   }

   cChars action = c_c( argv[1] );
   if ( not chars_is_c( action, "dec" ) and not chars_is_c( action, "enc" ) )
   {
      println_c_( "invalid $action value: {cs:Q}", action );
      return false;
   }

   cChars format = c_c( argv[2] );
   if ( not chars_is_c( format, "-x" ) and not chars_is_c( format, "-d" ) )
   {
      println_c_( "invalid $format value: {cs:Q}", format );
      return false;
   }

   args->action = action;
   args->format = chars_is_c( format, "-x" ) ? "x" : "d";
   args->valueSca = cstr_scanner_c_( argv[3] );
   return true;
}

int main( int argc, char* argv[] )
{
   //cErrorStack* es = &error_stack_c_( 1024 );

   argsDef args;
   if ( not init_args( argc, argv, &args ) )
   {
      print_usage();
      return EXIT_FAILURE;
   }

   if ( chars_is_c( args.action, "dec" ) )
   {
      uint64_t raw;
      if ( not read_uint64_c( &(args.valueSca), &raw, "x" ) )
      {
         println_c_( "not able to read EBML VINT: {cs}", unscanned_chars_c_( &(args.valueSca) ) );
         return EXIT_FAILURE;
      }

      oEbmlSize ebmlVal = ebml_size_o( raw );
      int64_t val = decode_ebml_size_o( ebmlVal );

      cRecorder* rec = &recorder_c_( 256 );
      if ( not write_int64_c( rec, val, args.format ) )
      {
         must_be_c_( false );
      }
      println_recorded_c( rec );
      return EXIT_SUCCESS;
   }
   else if ( chars_is_c( args.action, "enc" ) )
   {
      int64_t val;
      if ( not read_int64_c( &(args.valueSca), &val, args.format ) )
      {
         println_c_( "not able to read number: {cs}", unscanned_chars_c_( &(args.valueSca ) ) );
         return EXIT_FAILURE;
      }

      if ( val < 0 )
      {
         println_c_( "negative failures are not allowed: {i64}", val );
         return EXIT_FAILURE;
      }

      oEbmlSize ebmlVal = encode_ebml_size_o( val );
      println_c_( "{u64:x}", ebmlVal.raw );
      return EXIT_SUCCESS;
   }
   else
   {
      must_be_c_( false );
   }

   return EXIT_FAILURE;
}
