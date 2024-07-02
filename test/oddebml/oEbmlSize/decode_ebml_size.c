#include "clingo/io/write.h"
#include "clingo/lang/expect.h"
#include "oddebml/oEbmlSize.h"

TEMP_SLICE_C_(
   test,
   {
      uint64_t raw;
      int64_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 0x01ffffffffffffff, 0xffffffffffffff ),
      t_( 0x1a45dfa3, 0xa45dfa3 ),
      t_( 0x3e83bb, 0x1e83bb ),
      t_( 0x4286, 0x286 ),
      t_( 0xfa, 0x7a )
   );

   for_each_c_( i, test const*, t, tests )
   {
      int64_t val = decode_ebml_size_o( ebml_size_o( t->raw ) );
      bool res = val == t->exp;

      expect_block_c_( i, res )
      {
         tap_exp_line_c_( "{i:x}", t->exp );
         tap_got_line_c_( "{i:x}", val );
      }
   }

   return finish_tap_c_();
}