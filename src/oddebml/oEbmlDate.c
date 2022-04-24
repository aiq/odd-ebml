#include "oddebml/oEbmlDate.h"

cTimestamp ebml_date_as_timestamp_o( oEbmlDate ed )
{
   return now_c();
}

oEbmlDate ebml_date_from_timestamp_o( cTimestamp ts )
{
   return (oEbmlDate){ ._v = 0 };
}