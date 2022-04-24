#include <clingo/lang/expect.h>
#include "oddebml/oEbmlDate.h"

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

   return finish_tap_c_();
}