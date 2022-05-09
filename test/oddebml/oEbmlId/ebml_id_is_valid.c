#include "clingo/io/write.h"
#include "clingo/lang/expect.h"
#include "oddebml/oEbmlId.h"

TEMP_SLICE_DEF_C_(
   test,
   {
      uint32_t raw;
      bool exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( 0x80, false ),         // value is 0
      t_( 0x4000, false ),       // value is 0
      t_( 0x81, true ),
      t_( 0x4001, false ),       // a shorter encoding is available
      t_( 0xbf, true ),
      t_( 0x403f, false ),       // a shoreter encoding is available
      t_( 0xff, false ),         // must not set to all 1
      t_( 0x407f, true )
   );

   for_each_c_( test const*, t, tests )
   {
      oEbmlId id = ebml_id_o( t->raw );
      bool res = ebml_id_is_valid_o( id ) == t->exp;

      cRecorder* rec = &recorder_c_( 64 );
      write_c_( rec, "expected {bool} for {u32:x}", t->exp, t->raw );
      tap_desc_c( res, turn_into_cstr_c( rec ) );
   }

   return finish_tap_c_();
}