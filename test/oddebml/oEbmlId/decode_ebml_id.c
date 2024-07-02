#include "clingo/io/write.h"
#include "clingo/lang/expect.h"
#include "oddebml/oEbmlId.h"

TEMP_SLICE_C_(
   test,
   {
      uint32_t raw;
      int32_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 0x1a45dfa3, 0xa45dfa3 ),
      t_( 0x3e83bb, 0x1e83bb ),
      t_( 0x4286, 0x286 ),
      t_( 0xfa, 0x7a )
   );

   for_each_c_( i, test const*, t, tests )
   {
      int32_t val = decode_ebml_id_o( ebml_id_o( t->raw ) );
      bool res = val == t->exp;

      expect_block_c_( i, res )
      {
         tap_exp_line_c_( "{i32:x}", t->exp );
         tap_got_line_c_( "{i32:x}", val );
      }
   }

   return finish_tap_c_();
}