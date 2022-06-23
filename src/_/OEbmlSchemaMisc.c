#include "_/OEbmlSchemaMisc.h"

#include "clingo/type/int64.h"

STACK_IMPL_C_(
   oEbmlDecl,        // Type
   oEbmlDeclStack,   // StackType
   ebml_decl_o,      // FuncSuffix
   ebml_decl_stack_o // StackFuncSuffix
)

VAL_VAL_MAP_IMPL_C_(
   ,                 // Static
   OSchemaMap,       // MapType
   oSchemaRow,       // RowType
   uint32_t,         // KeyType
   oEbmlDeclStack,   // ValType
   schema_map_o,     // FuncName
   O_SchemaMapMeta,  // Meta
   hash_int64_c,     // HashFunc
   cmp_int64_c,      // CmpFunc
   do_not_ref_c_     // DoRef
)