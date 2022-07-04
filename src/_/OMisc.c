#include "_/OMisc.h"

#include "clingo/type/int64.h"

STACK_IMPL_C_(
   oEbmlDecl,        // Type
   oEbmlDeclStack,   // StackType
   ebml_decl_o,      // FuncSuffix
   ebml_decl_stack_o // StackFuncSuffix
)



STACK_IMPL_C_(
   oEbmlMarker,         // Type
   oEbmlMarkerStack,    // StackType
   ebml_marker_o,       // FuncSuffix
   ebml_marker_stack_o  // StackFuncSuffix
)

VAL_VAL_MAP_IMPL_C_(
   ,                 // Static
   OIndexMap,        // MapType
   oIndexRow,        // RowType
   uint32_t,         // KeyType
   oEbmlMarkerStack, // ValType
   index_map_o,      // FuncName
   O_IndexMapMeta,   // Meta
   hash_int64_c,     // HashFunc
   cmp_int64_c,      // CmpFunc
   do_not_ref_c_     // DoRef
)