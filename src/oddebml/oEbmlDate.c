#include "oddebml/oEbmlDate.h"

#include "clingo/type/int32.h"

#define UNIX_SECS_DIFF 978307200

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICE_IMPL_C_(
   oEbmlDate,              // Type
   oEbmlDateSlice,         // SliceType
   ebml_date_slice_o,      // FuncName
   oVarEbmlDateSlice,      // VarSliceType
   var_ebml_date_slice_o   // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

oEbmlDate default_ebml_date_o( void )
{
   return (oEbmlDate){ ._v=0 };
}

oEbmlDate ebml_date_o( cDate d, cDaytime dt, cTzOffset tz )
{
   return as_ebml_date_o( time_c( d, dt, tz ) );
}

cTime from_ebml_date_o( oEbmlDate ed )
{
   cDuration nsec;
   cDuration sec = truncate_duration_c( nsecs_c( ed._v ), C_Sec, &nsec );

   int32_t n;
   if ( not int64_to_int32_c( nsec._v, &n ) ) return null_time_c();

   return (cTime){ as_secs_c( sec ) + UNIX_SECS_DIFF, n, 0 };
}

oEbmlDate as_ebml_date_o( cTime t )
{
   cDuration dur = add_duration_c( secs_c( t._s - UNIX_SECS_DIFF ), nsecs_c( t._n ) );
   return (oEbmlDate){ ._v=dur._v };
}

/*******************************************************************************
 overall
*******************************************************************************/

int cmp_ebml_date_c( oEbmlDate a, oEbmlDate b )
{
   return cmp_int64_c( a._v, b._v );
}

extern inline bool eq_ebml_date_c( oEbmlDate a, oEbmlDate b );

/*******************************************************************************
 io
*******************************************************************************/

bool record_ebml_date_o( cRecorder rec[static 1], oEbmlDate date )
{
   int64_t raw = swap_int64_to_c( date._v, c_BigEndian );
   return record_int64_c( rec, raw );
}

bool scan_ebml_date_o( cScanner sca[static 1], oEbmlDate date[static 1] )
{
   int64_t i64;
   if ( not scan_int64_c( sca, &i64 ) ) return false;

   date->_v = swap_int64_from_c( i64, c_BigEndian );
   return true;
}