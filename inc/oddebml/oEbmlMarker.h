#ifndef ODDEBML_EBML_MARKER_H
#define ODDEBML_EBML_MARKER_H

#include "clingo/lang/CObject.h"
#include "clingo/lang/error.h"
#include "oddebml/apidecl.h"
#include "oddebml/oEbmlDate.h"
#include "oddebml/oEbmlId.h"
#include "oddebml/oEbmlSize.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oEbmlMarker
{
   oEbmlId id;
   int64_t size;
   fpos_t pos;
};
typedef struct oEbmlMarker oEbmlMarker;

struct oEbmlMarkerSlice
{
   int64_t s;
   oEbmlMarker const* v;
};
typedef struct oEbmlMarkerSlice oEbmlMarkerSlice;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDEBML_API bool fread_curr_ebml_marker_o( FILE* f,
                                           oEbmlMarker marker[static 1] );

ODDEBML_API bool fread_next_ebml_marker_o( FILE* f,
                                           int64_t delta,
                                           oEbmlMarker marker[static 1] );

ODDEBML_API
bool fread_ebml_child_marker_o( FILE* f,
                                oEbmlMarker const from[static 1],
                                oEbmlMarker marker[static 1] );

ODDEBML_API
bool fread_ebml_sibling_marker_o( FILE* f,
                                  oEbmlMarker const from[static 1],
                                  oEbmlMarker marker[static 1] );

ODDEBML_API bool fread_ebml_bytes_o( FILE* f,
                                     oEbmlMarker const from[static 1],
                                     cVarBytes buf[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool fread_ebml_int_o( FILE* f,
                                   oEbmlMarker const from[static 1],
                                   int64_t val[static 1] );

ODDEBML_API bool fread_ebml_uint_o( FILE* f,
                                    oEbmlMarker const from[static 1],
                                    uint64_t val[static 1] );

ODDEBML_API bool fread_ebml_float_o( FILE* f,
                                     oEbmlMarker const from[static 1],
                                     double val[static 1] );

ODDEBML_API bool fread_ebml_string_o( FILE* f,
                                      oEbmlMarker const from[static 1],
                                      cVarChars val[static 1] );

ODDEBML_API bool fread_ebml_utf8_o( FILE* f,
                                    oEbmlMarker const from[static 1],
                                    cVarChars val[static 1] );

ODDEBML_API bool fread_ebml_date_o( FILE* f,
                                    oEbmlMarker const from[static 1],
                                    oEbmlDate date[static 1] );

#endif