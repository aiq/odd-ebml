#include "clingo/io/write.h"
#include "clingo/lang/expect.h"
#include "oddebml/oEbmlSize.h"

TEMP_SLICE_C_(
   test,
   {
      oEbmlSize size;
      bool exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( unknown_ebml_size_o( 0 ), false ),
      t_( unknown_ebml_size_o( 1 ), true ),
      t_( unknown_ebml_size_o( 2 ), true ),
      t_( unknown_ebml_size_o( 3 ), true ),
      t_( unknown_ebml_size_o( 4 ), true ),
      t_( unknown_ebml_size_o( 5 ), true ),
      t_( unknown_ebml_size_o( 6 ), true ),
      t_( unknown_ebml_size_o( 7 ), true ),
      t_( unknown_ebml_size_o( 8 ), true ),
      t_( unknown_ebml_size_o( 9 ), false )
   );

   for_each_c_( i, test const*, t, tests )
   {
      bool res = ebml_size_is_unknown_o( t->size ) == t->exp;

      expect_block_c_( i, res )
      {
         tap_exp_line_c_( "{bool}", t->exp );
         tap_line_c_( "input", "{u32:x}", t->size.raw );
      }
   }

   return finish_tap_c_();
}