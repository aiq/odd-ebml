#include "_/oEbmlBuilderMarker.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICE_IMPL_C_(
   oEbmlBuilderMarker,              // Type
   oEbmlBuilderMarkerSlice,         // SliceType
   ebml_builder_marker_slice_o,     // FuncName
   oVarEbmlBuilderMarkerSlice,      // VarSliceType
   var_ebml_builder_marker_slice_o  // VarFuncName
)

STACK_IMPL_C_(
   oEbmlBuilderMarker,           // Type
   oEbmlBuilderMarkerStack,      // StackType
   ebml_builder_marker_o,        // FuncSuffix
   ebml_builder_marker_stack_o   // StackFuncSuffix
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

oEbmlBuilderMarker ebml_builder_marker_o( oEbmlId id, int64_t pos )
{
   return (oEbmlBuilderMarker){ .id=id, .pos=pos };
}
