#include "oddebml/OEbmlDeclMap.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************

*******************************************************************************/

static inline uint64_t hash_ebml_id_o( oEbmlId id )
{
   return id.raw;
}

VAL_VAL_MAP_IMPL_C_(
   ,                    // Static
   OEbmlDeclMap,        // MapType
   oEbmlDeclMapRow,     // RowType
   oEbmlId,             // KeyType
   oEbmlDecl,           // ValType
   ebml_decl_map_o,     // FuncName
   O_EbmlDeclMapMeta,   // Meta
   hash_ebml_id_o,      // HashFunc
   cmp_ebml_id_o,       // CmpFunc
   do_not_ref_c_        // DoRef
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool fill_ebml_decl_map_o( OEbmlDeclMap* map, oEbmlDeclSlice slice )
{
   must_exist_c_( map );

   for_each_c_( oEbmlDecl const*, decl, slice )
   {
      if ( not set_on_ebml_decl_map_o( map, decl->id, *decl ) ) return false;
   }
   return true;
}