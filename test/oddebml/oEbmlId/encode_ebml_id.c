#include "oddebml/oddebml.h"

TEMP_SLICE_C_(
   test,
   {
      int32_t inp;
      uint32_t exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 0xa45dfa3, 0x1a45dfa3 ),
      t_( 0x1e83bb, 0x3e83bb ),
      t_( 0x286, 0x4286 )
   );

   for_each_c_( i, test const*, t, tests )
   {
      oEbmlId id = encode_ebml_id_o( t->inp );
      bool res = id.raw == t->exp;

      expect_block_c_( i, res )
      {
         tap_exp_line_c_( "{u32:x}", t->exp );
         tap_exp_line_c_( "{u32:x}", id.raw );
      }
   }

   return finish_tap_c_();
}