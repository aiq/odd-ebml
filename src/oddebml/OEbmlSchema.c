#include "oddebml/OEbmlSchema.h"

#include "_/OEbmlSchemaMisc.h"
#include "clingo/container/CInt64Map.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct OEbmlSchema
{
   OSchemaMap* map;
   CInt64Map* parents;
};

static inline void cleanup( void* instance )
{
   OEbmlSchema* schema = instance;

   if ( schema->map != NULL )
   {
      uint32_t const* key;
      oEbmlDeclStack* stack;
      iterate_map_c_( itr, key, stack, schema->map, next_var_in_schema_map_o )
      {
         if ( not is_empty_c_( *stack ) )
         {
            free_ebml_decl_stack_o( stack );
         }
      }
      release_c( schema->map );
   }
   if ( schema->parents != NULL )
   {
      release_c( schema->parents );
   }
}

cMeta const O_EbmlSchemaMeta = {
   .desc = stringify_c_( OEbmlSchema ),
   .cleanup = &cleanup
};

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

static inline oEbmlSchemaItr itr_for_id( OEbmlSchema const* schema,
                                         uint32_t rawId )
{
   int64_t const* pid64 = get_from_int64_map_c( schema->parents, rawId );
   if ( pid64 == NULL ) return start_ebml_schema_itr_o();

   uint32_t pid;
   if ( not int64_to_uint32_c( *pid64, &pid ) ) return start_ebml_schema_itr_o();

   oEbmlDeclStack const* stack = get_from_schema_map_o( schema->map, pid );
   if ( stack == NULL ) return start_ebml_schema_itr_o();

   uint16_t i = 0;
   for_each_c_( oEbmlDecl const*, decl, *stack )
   {
      if ( decl->id.raw == rawId )
      {
         return (oEbmlSchemaItr){ ._i=rawId, ._n=i };
      }
      ++i;
   }

   return start_ebml_schema_itr_o();
}

static inline oEbmlDecl const* decl_for_itr( OEbmlSchema const* schema,
                                             oEbmlSchemaItr itr )
{
   if ( not ebml_schema_itr_is_valid_o( itr ) ) return NULL;

   oEbmlDeclStack const* stack = get_from_schema_map_o( schema->map,
                                                        itr._i );
   if ( stack == NULL ) return NULL;
   
   return ptr_for_c_( *stack, itr._n );
}

static inline bool attach_ebml_leaf( OEbmlSchema* schema,
                                     uint32_t rawId )
{
   oEbmlDeclStack sub = (oEbmlDeclStack){ .s=0, .v=0, .cap=0 };
   return set_on_schema_map_o( schema->map, rawId, sub );
}

/*******************************************************************************

*******************************************************************************/

OEbmlSchema* new_ebml_schema_o( void )
{
   cObjectInfo const info = default_object_info_c_( &O_EbmlSchemaMeta );
   OEbmlSchema* result = alloc_object_c_( OEbmlSchema, &info );
   if ( result == NULL )
   {
      return NULL;
   }

   result->map = new_schema_map_o();
   result->parents = new_int64_map_c();
   if ( result->map == NULL or
        result->parents == NULL or
        not attach_ebml_leaf( result, O_EbmlRoot.id.raw ) )
   {
      release_c( result );
      return NULL;
   }

   return result;
}

/*******************************************************************************

*******************************************************************************/

bool attach_ebml_decl_o( OEbmlSchema* schema,
                         oEbmlDecl const parent[static 1],
                         oEbmlDecl const decl[static 1] )
{
   must_exist_c_( schema );

   oEbmlDeclStack* stack = get_var_from_schema_map_o( schema->map,
                                                      parent->id.raw );
   if ( stack == NULL ) return false;
   if ( stack->s == UINT16_MAX ) return false;

   if ( not push_ebml_decl_o( stack, *decl ) ) return false;

   if (
      not attach_ebml_leaf( schema, decl->id.raw ) or 
      not set_on_int64_map_c( schema->parents, decl->id.raw, parent->id.raw )
   )
   {
      stack->s -= 1;
      remove_from_schema_map_o( schema->map, decl->id.raw );
      return false;
   }

   return true;
}

bool attach_many_ebml_decl_o( OEbmlSchema* schema,
                              oEbmlDecl const parent[static 1],
                              oEbmlDeclSlice many )
{
   must_exist_c_( schema );

   oEbmlDeclStack* stack = get_var_from_schema_map_o( schema->map,
                                                      parent->id.raw );
   if ( stack == NULL ) return false;

   if ( stack->s == 0 and stack->cap == 0 )
   {
      alloc_ebml_decl_stack_o( stack, many.s );
   }
   int64_t reqCap;
   if ( not iadd64_c( stack->s, many.s, &reqCap ) ) return false;
   if ( reqCap > stack->cap )
   {
      if ( reqCap > UINT16_MAX ) return false;
      if ( not realloc_ebml_decl_stack_o( stack, reqCap*2 ) ) return false;
   }

   for_each_c_( oEbmlDecl const*, decl, many )
   {
      if ( not push_ebml_decl_o( stack, *decl ) ) return false;
      if (
         not attach_ebml_leaf( schema, decl->id.raw ) or 
         not set_on_int64_map_c( schema->parents, decl->id.raw, parent->id.raw )
      )
      {
         stack->s -= 1;
         remove_from_schema_map_o( schema->map, decl->id.raw );
         return false;
      }
   }

   return true;
}

oEbmlDecl const* find_ebml_decl_o( OEbmlSchema const* schema,
                                   oEbmlId id )
{
   must_exist_c_( schema );

   oEbmlSchemaItr itr = itr_for_id( schema, id.raw );
   return decl_for_itr( schema, itr );
}

oEbmlDeclSlice get_sub_ebml_decl_o( OEbmlSchema const* schema,
                                    oEbmlDecl const decl[static 1] )
{
   must_exist_c_( schema );

   oEbmlDeclStack const* stack = get_from_schema_map_o( schema->map,
                                                        decl->id.raw );
   if ( stack == NULL )
   {
      return (oEbmlDeclSlice)invalid_slice_c_();
   }
   return (oEbmlDeclSlice){ .s=stack->s, .v=stack->v };
}

/*******************************************************************************

*******************************************************************************/

bool attach_ebml_header_schema_o( OEbmlSchema* schema )
{
   must_exist_c_( schema );

   if ( not attach_ebml_decl_o( schema, &O_EbmlRoot, &O_Ebml ) )
      return false;

   return attach_many_ebml_decl_o_( schema, &O_Ebml,
      O_EbmlVersion, O_EbmlReadVersion, O_EbmlMaxIdLength, O_EbmlMaxSizeLength,
      O_EbmlDocType, O_EbmlDocTypeVersion, O_EbmlDocTypeReadVersion
   );
}

/*******************************************************************************

*******************************************************************************/

extern inline oEbmlSchemaItr start_ebml_schema_itr_o();

extern inline bool ebml_schema_itr_is_valid_o( oEbmlSchemaItr itr );

static oEbmlSchemaItr first_itr( OEbmlSchema const* schema,
                                 oEbmlDecl const* decl[static 1] )
{
   oEbmlDeclStack const* stack = get_from_schema_map_o( schema->map,
                                                        O_EbmlRoot.id.raw );
   if ( is_empty_c_( *stack ) ) return start_ebml_schema_itr_o();

   oEbmlSchemaItr itr = { ._i=O_EbmlRoot.id.raw, ._n=0, .level=0 };
   *decl =  stack->v;
   return itr;
}

static inline bool is_leaf( OEbmlSchema const* schema, uint32_t rawId )
{
   oEbmlDeclStack const* subStack = get_from_schema_map_o( schema->map,
                                                           rawId );
   return is_empty_c_( *subStack );
}

static oEbmlSchemaItr move_itr_right_up( OEbmlSchema const* schema,
                                         oEbmlSchemaItr itr )
{
   oEbmlDeclStack const* stack = get_from_schema_map_o( schema->map,
                                                        itr._i );
   if ( itr._n+1 == stack->s )
   {
      int64_t const* pid64 = get_from_int64_map_c( schema->parents, itr._i );
      if ( pid64 == NULL ) return start_ebml_schema_itr_o();

      uint32_t pid;
      if ( int64_to_uint32_c( *pid64, &pid ) ) return start_ebml_schema_itr_o();

      itr = itr_for_id( schema, pid );
      if ( not ebml_schema_itr_is_valid_o( itr ) ) return itr;

      itr.level--;
      return move_itr_right_up( schema, itr );
   }

   itr._n += 1;
   return itr;
}

static oEbmlSchemaItr move_itr( OEbmlSchema const* schema,
                                oEbmlSchemaItr itr )
{
   oEbmlDeclStack const* stack = get_from_schema_map_o( schema->map,
                                                        itr._i );
   uint32_t currRawId = stack->v[itr._n ].id.raw;
   if ( not is_leaf( schema, currRawId ) )
   {
      itr._i = currRawId;
      itr._n = 0;
      itr.level++;
      return itr;
   }

   return move_itr_right_up( schema, itr );
}

oEbmlSchemaItr next_ebml_decl_in_schema_o( OEbmlSchema const* schema,
                                           oEbmlSchemaItr itr,
                                           oEbmlDecl const* decl[static 1] )
{
   if ( not ebml_schema_itr_is_valid_o( itr ) )
   {
      return first_itr( schema, decl );
   }

   itr = move_itr( schema, itr );
   *decl = decl_for_itr( schema, itr );
   return itr;
}