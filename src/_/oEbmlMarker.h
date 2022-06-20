#ifndef ODDEBML_INTERN_EBML_MARKER_H
#define ODDEBML_INTERN_EBML_MARKER_H

#include "oddebml/apidecl.h"
#include "oddebml/oEbmlId.h"
#include "oddebml/oEbmlSize.h"
#include "_/stack.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oEbmlMarker {
   oEbmlId id;
   int64_t pos;
};
typedef struct oEbmlMarker oEbmlMarker;

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

STACK_DEF_C_(
   oEbmlMarker,         // Type
   oEbmlMarkerStack,    // StackType
   ebml_marker_o,       // FuncSuffix
   ebml_marker_stack_o  // StackFuncSuffix
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 marker
*******************************************************************************/

oEbmlMarker ebml_marker_o( oEbmlId id, int64_t pos );

#endif