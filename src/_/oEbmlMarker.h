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

oEbmlMarker ebml_marker_o( oEbmlId id, int64_t pos );

/*******************************************************************************
 stack
*******************************************************************************/

bool alloc_ebml_marker_stack_o( oEbmlMarkerStack stack[static 1], int64_t size );

bool realloc_ebml_marker_stack_o( oEbmlMarkerStack stack[static 1], int64_t size );

void free_ebml_marker_stack_o( oEbmlMarkerStack stack[static 1] );

bool push_ebml_marker_o( oEbmlMarkerStack stack[static 1], oEbmlMarker marker );

bool pop_ebml_marker_o( oEbmlMarkerStack stack[static 1],
                        oEbmlMarker marker[static 1] );

#endif