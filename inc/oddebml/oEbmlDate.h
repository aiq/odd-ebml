#ifndef ODDEBML_OEBMLDATE_H
#define ODDEBML_OEBMLDATE_H

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

SLICES_C_(
   oEbmlDate,           // Type
   oEbmlDateSlice,      // SliceType
   oVarEbmlDateSlice    // VarSliceType
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

#define read_ebml_date_o_( Sca, Date )                                         \
   read_ebml_date_o( (Sca), (Date), "" )
ODDEBML_API bool read_ebml_date_o( cScanner sca[static 1],
                                   oEbmlDate date[static 1],
                                   char const fmt[static 1] );

ODDEBML_API bool record_ebml_date_o( cRecorder rec[static 1], oEbmlDate date );

ODDEBML_API
bool scan_ebml_date_o( cScanner sca[static 1], oEbmlDate date[static 1] );

#define write_ebml_date_o_( Rec, Date )                                        \
   write_ebml_date_o( (Rec), (Date), "" )
ODDEBML_API bool write_ebml_date_o( cRecorder rec[static 1],
                                    oEbmlDate date,
                                    char const fmt[static 1] );

#endif