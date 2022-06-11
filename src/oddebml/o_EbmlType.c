#include "oddebml/o_EbmlType.h"

/*******************************************************************************

*******************************************************************************/

char const* stringify_ebml_type_c( o_EbmlType type )
{
   switch ( type )
   {
      #define XMAP_C_( N, I ) case N: return #N;
         oEBML_TYPE_
      #undef XMAP_C_
   }
}
