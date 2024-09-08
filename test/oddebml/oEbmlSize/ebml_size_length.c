#include "oddebml/oddebml.h"

TEMP_SLICE_C_(
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

   for_each_c_( i, test const*, t, tests )
   {
      int8_t len = ebml_size_length_o( ebml_size_o( t->raw ) );
      bool res = len == t->exp;

      expect_block_c_( i, res )
      {
         tap_exp_line_c_( "{i8}", t->exp );
         tap_got_line_c_( "{i8}", len );
      }
   }

   return finish_tap_c_();
}