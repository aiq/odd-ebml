#ifndef ODDEBML_INTERN_EBML_MARKER_H
#define ODDEBML_INTERN_EBML_MARKER_H

#include "oddebml/apidecl.h"
#include "oddebml/oEbmlId.h"
#include "oddebml/oEbmlSize.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oEbmlMarker {
   oEbmlId id;
   int64_t pos;
};
typedef struct oEbmlMarker oEbmlMarker;

struct oEbmlMarkerStack {
   int64_t s;
   oEbmlMarker* v;
   int64_t cap;
};
typedef struct oEbmlMarkerStack oEbmlMarkerStack;

/*******************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   oEbmlMarker,            // Type
   oEbmlMarkerSlice,       // SliceType
   ebml_marker_slice_o,    // FuncName
   oVarEbmlMarkerSlice,    // VarSliceType
   var_ebml_marker_slice_o // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 marker
*******************************************************************************/

ODDEBML_API oEbmlMarker ebml_marker_o( oEbmlId id, int64_t pos );

/*******************************************************************************
 stack
*******************************************************************************/

ODDEBML_API
bool alloc_ebml_marker_stack_o( oEbmlMarkerStack stack[static 1], int64_t size );

ODDEBML_API
bool realloc_ebml_marker_stack_o( oEbmlMarkerStack stack[static 1], int64_t size );

ODDEBML_API
void free_ebml_marker_stack_o( oEbmlMarkerStack stack[static 1] );

ODDEBML_API
bool push_ebml_marker_o( oEbmlMarkerStack stack[static 1], oEbmlMarker marker );

ODDEBML_API
bool pop_ebml_marker_o( oEbmlMarkerStack stack[static 1],
                        oEbmlMarker marker[static 1] );

#endif