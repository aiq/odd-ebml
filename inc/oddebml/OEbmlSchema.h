#ifndef ODDEBML_EBML_SCHEMA_H
#define ODDEBML_EBML_SCHEMA_H

#include "clingo/lang/CObject.h"
#include "oddebml/apidecl.h"
#include "oddebml/error.h"
#include "oddebml/oEbmlDecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

ODDEBML_API extern cMeta const O_EbmlSchemaMeta;

struct OEbmlSchema;
typedef struct OEbmlSchema OEbmlSchema;

struct oEbmlSchemaItr
{
   uint32_t _i;
   uint16_t _n;
   int16_t level;
};
typedef struct oEbmlSchemaItr oEbmlSchemaItr;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDEBML_API OEbmlSchema* new_ebml_schema_o( void );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool attach_ebml_decl_o( OEbmlSchema* schema,
                                     oEbmlDecl const parent[static 1],
                                     oEbmlDecl const decl[static 1] );


#define attach_many_ebml_decl_o_( Schema, Parent, ... )                        \
   attach_many_ebml_decl_o(                                                    \
      (Schema), (Parent), (oEbmlDeclSlice)slice_c_( oEbmlDecl, __VA_ARGS__ )   \
   )
ODDEBML_API bool attach_many_ebml_decl_o( OEbmlSchema* schema,
                                          oEbmlDecl const parent[static 1],
                                          oEbmlDeclSlice many );

ODDEBML_API oEbmlDecl const* find_ebml_decl_o( OEbmlSchema const* schema,
                                               oEbmlId id );

ODDEBML_API
oEbmlDeclSlice get_sub_ebml_decl_o( OEbmlSchema const* schema,
                                    oEbmlDecl const decl[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool attach_ebml_header_schema_o( OEbmlSchema* schema );

/*******************************************************************************
 itr
*******************************************************************************/

#define iterate_ebml_schema_c_( Itr, DeclPtr, Schema )                         \
for (                                                                          \
   oEbmlSchemaItr Itr = next_ebml_decl_in_schema_o(                            \
      Schema, start_ebml_schema_itr_o(), &DeclPtr                              \
   );                                                                          \
   ebml_schema_itr_is_valid_o( Itr );                                          \
   Itr = next_ebml_decl_in_schema_o( Schema, Itr, &DeclPtr )                   \
)

ODDEBML_API inline oEbmlSchemaItr start_ebml_schema_itr_o()
{
   return (oEbmlSchemaItr){ ._i=0, ._n=0, .level=-1 };
}

ODDEBML_API inline bool ebml_schema_itr_is_valid_o( oEbmlSchemaItr itr )
{
   return itr.level >= 0;
}

oEbmlSchemaItr next_ebml_decl_in_schema_o( OEbmlSchema const* schema,
                                           oEbmlSchemaItr itr,
                                           oEbmlDecl const* decl[static 1] );

#endif