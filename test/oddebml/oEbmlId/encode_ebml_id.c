#include <clingo/lang/expect.h>
#include "odd/ebml/oEbmlId.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      uint32_t inp;
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


   for_each_c_( test const*, t, tests )
   {
      oEbmlId id = ebml_id_o( t->inp );
      bool res = id._v != t->exp

      cRecorder* rec = &recorder_c_( 32 );
      write_c_( rec, "expected {u32:x}, got {u32:x}", t->exp, id._v );
      tap_descf_c( res != t->exp, "%s", turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}