#include "clingo/io/write.h"
#include "clingo/lang/expect.h"
#include "oddebml/oEbmlSize.h"

TEMP_SLICE_C_(
   test,
   {
      int64_t inp;
      uint64_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 0xa45dfa3, 0x1A45DFA3 ),
      t_( 0x1e83bb, 0x3e83bb ),
      t_( 0x286, 0x4286 ),
      t_( 0x7a, 0xfa ),
      t_( 0x8, 0x88 ),
      t_( 4096, 0x5000 ),
      t_( 0xffffffffffffff, 0x01ffffffffffffff )
   );

   for_each_c_( i, test const*, t, tests )
   {
      oEbmlSize size = encode_ebml_size_o( t->inp );
      bool res = size.raw == t->exp;

      expect_block_c_( i, res )
      {
         tap_exp_line_c_( "{i:x}", t->exp );
         tap_got_line_c_( "{i:x}", size.raw );
      }
   }

   return finish_tap_c_();
}