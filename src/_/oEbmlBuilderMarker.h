#ifndef ODDEBML_INTERN_EBML_BUILDER_MARKER_H
#define ODDEBML_INTERN_EBML_BUILDER_MARKER_H

#include "oddebml/apidecl.h"
#include "oddebml/oEbmlId.h"
#include "oddebml/oEbmlSize.h"
#include "_/stack.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oEbmlBuilderMarker {
   oEbmlId id;
   int64_t pos;
};
typedef struct oEbmlBuilderMarker oEbmlBuilderMarker;

/*******************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   oEbmlBuilderMarker,              // Type
   oEbmlBuilderMarkerSlice,         // SliceType
   ebml_builder_marker_slice_o,     // FuncName
   oVarEbmlBuilderMarkerSlice,      // VarSliceType
   var_ebml_builder_marker_slice_o  // VarFuncName
)

STACK_DEF_C_(
   oEbmlBuilderMarker,           // Type
   oEbmlBuilderMarkerStack,      // StackType
   ebml_builder_marker_o,        // FuncSuffix
   ebml_builder_marker_stack_o   // StackFuncSuffix
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 marker
*******************************************************************************/

oEbmlBuilderMarker ebml_builder_marker_o( oEbmlId id, int64_t pos );

#endif