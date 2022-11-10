#ifndef ODDEBML_OEBMLDECLMAP_H
#define ODDEBML_OEBMLDECLMAP_H

#include "clingo/container/map.h"
#include "oddebml/apidecl.h"
#include "oddebml/oEbmlDecl.h"
#include "oddebml/oEbmlId.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

VAL_VAL_MAP_DEF_C_(
   ODDEBML_API,      // LibApi
   OEbmlDeclMap,     // MapType
   oEbmlId,          // KeyType
   oEbmlDecl,        // ValType
   ebml_decl_map_o,  // FuncName
   O_EbmlDeclMapMeta // Meta
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDEBML_API
bool fill_ebml_decl_map_o( OEbmlDeclMap* map, oEbmlDeclSlice slice );

#endif