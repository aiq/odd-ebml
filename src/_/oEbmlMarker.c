#include "_/oEbmlMarker.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICE_IMPL_C_(
   oEbmlMarker,            // Type
   oEbmlMarkerSlice,       // SliceType
   ebml_marker_slice_o,    // FuncName
   oVarEbmlMarkerSlice,    // VarSliceType
   var_ebml_marker_slice_o // VarFuncName
)

STACK_IMPL_C_(
   oEbmlMarker,         // Type
   oEbmlMarkerStack,    // StackType
   ebml_marker_o,       // FuncSuffix
   ebml_marker_stack_o  // StackFuncSuffix
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

oEbmlMarker ebml_marker_o( oEbmlId id, int64_t pos )
{
   return (oEbmlMarker){ .id=id, .pos=pos };
}
