#include "clingo/lang/expect.h"
#include "oddebml/oEbmlDate.h"

TEMP_SLICE_C_(
   test,
   {
      cTime inp;
      oEbmlDate exp;
   }
)
#define t_( ... ) ((test){__VA_ARGS__})

int main( void )
{
   init_tap_c_();

   testSlice tests = slice_c_( test,
      t_( make_time_c( 2001, c_Jan,  1,  0,  0,  0, 0, utc_c() ),
          (oEbmlDate){ ._v=0 } ),
      t_( make_time_c( 1708, c_Sep, 11,  0, 12, 44, 854775808, utc_c() ),
          (oEbmlDate){ ._v=INT64_MIN } ),
      t_( make_time_c( 2293, c_Apr, 11, 23, 47, 16, 854775807, utc_c() ),
          (oEbmlDate){ ._v=INT64_MAX } )
   );

   for_each_c_( test const*, t, tests )
   {
      oEbmlDate res = as_ebml_date_o( t->inp );
      expect_c_( eq_ebml_date_c( res, t->exp ) );
   }

   return finish_tap_c_();
}
