#ifndef ODDEBML_EBML_DATE_H
#define ODDEBML_EBML_DATE_H

#include "clingo/time/cTime.h"
#include "oddebml/apidecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oEbmlDate {
    int64_t _v;
};
typedef struct oEbmlDate oEbmlDate;

/*******************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   oEbmlDate,               // Type
   oEbmlDateSlice,          // SliceType
   ebml_date_slice_o,       // FuncName
   oVarEbmlDateSlice,       // VarSliceType
   var_ebml_date_slice_o    // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

ODDEBML_API oEbmlDate default_ebml_date_o( void );

ODDEBML_API oEbmlDate ebml_date_o( cDate d, cDaytime dt, cTzOffset tz );

ODDEBML_API cTime from_ebml_date_o( oEbmlDate ed );

ODDEBML_API oEbmlDate as_ebml_date_o( cTime t );

/*******************************************************************************
 overall
*******************************************************************************/

ODDEBML_API int cmp_ebml_date_c( oEbmlDate a, oEbmlDate b );

ODDEBML_API inline bool eq_ebml_date_c( oEbmlDate a, oEbmlDate b )
{
   return a._v == b._v;
}

/*******************************************************************************
 io
*******************************************************************************/

ODDEBML_API bool record_ebml_date_o( cRecorder rec[static 1], oEbmlDate date );

ODDEBML_API
bool scan_ebml_date_o( cScanner sca[static 1], oEbmlDate date[static 1] );

#endif