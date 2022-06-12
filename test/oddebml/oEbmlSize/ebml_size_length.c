#include "clingo/io/write.h"
#include "clingo/lang/expect.h"
#include "oddebml/oEbmlSize.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      uint64_t raw;
      int8_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 0xffffffffffffffff, 0 ),
      t_( 0x5000, 2 ),
      t_( 0x01ffffffffffffff, 8 ),
      t_( 0x1a45dfa3, 4 ),
      t_( 0x3e83bb, 3 ),
      t_( 0x4286, 2 ),
      t_( 0xfa, 1 )
   );

   for_each_c_( test const*, t, tests )
   {
      int8_t len = ebml_size_length_o( ebml_size_o( t->raw ) );
      bool res = len == t->exp;

      cRecorder* rec = &recorder_c_( 64 );
      write_c_( rec, "expected {i8}, got {i8}", t->exp, len );
      tap_desc_c( res, turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}