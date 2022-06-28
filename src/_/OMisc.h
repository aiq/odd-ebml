#ifndef ODDEBML_INTERN_EBML_SCHEMA_MISC_H
#define ODDEBML_INTERN_EBML_SCHEMA_MISC_H

#include "clingo/container/map.h"
#include "_/stack.h"
#include "oddebml/oEbmlDecl.h"
#include "oddebml/oEbmlMarker.h"

STACK_DEF_C_(
   oEbmlDecl,        // Type
   oEbmlDeclStack,   // StackType
   ebml_decl_o,      // FuncSuffix
   ebml_decl_stack_o // StackFuncSuffix
)

VAL_VAL_MAP_DEF_C_(
   ,                 // LibApi
   OSchemaMap,       // MapType
   uint32_t,         // KeyType
   oEbmlDeclStack,   // ValType
   schema_map_o,     // FuncName
   O_SchemaMapMeta   // Meta
)

STACK_DEF_C_(
   oEbmlMarker,         // Type
   oEbmlMarkerStack,    // StackType
   ebml_marker_o,       // FuncSuffix
   ebml_marker_stack_o  // StackFuncSuffix
)

VAL_VAL_MAP_DEF_C_(
   ,                 // LibApi
   OIndexMap,        // MapType
   uint32_t,         // KeyType
   oEbmlMarkerStack, // ValType
   index_map_o,      // FuncName
   O_IndexMapMeta    // Meta
)

#endif