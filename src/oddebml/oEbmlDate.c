#include "oddebml/oEbmlDate.h"

oEbmlDate ebml_date_o( cDate d, cDaytime dt, cTzOffset tz )
{
   return ebml_date_from_time_o( time_c( d, dt, tz ) );
}

cTime ebml_date_as_time_o( oEbmlDate ed )
{
   return local_time_c();
}

cTimestamp ebml_date_as_timestamp_o( oEbmlDate ed )
{
   return now_c();
}

oEbmlDate ebml_date_from_time_o( cTime t )
{
   return (oEbmlDate){ ._v = 0 };
}

oEbmlDate ebml_date_from_timestamp_o( cTimestamp ts )
{
   return (oEbmlDate){ ._v = 0 };
}
