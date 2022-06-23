#ifndef ODDEBML_INTERN_EBML_SCHEMA_MISC_H
#define ODDEBML_INTERN_EBML_SCHEMA_MISC_H

#include "clingo/container/map.h"
#include "_/stack.h"
#include "oddebml/OEbmlSchema.h"

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

#endif