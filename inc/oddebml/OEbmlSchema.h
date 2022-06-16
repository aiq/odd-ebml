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

struct oEbmlSchemaNode;
typedef struct oEbmlSchemaNode oEbmlSchemaNode;

struct oEbmlSchemaNodeSlice
{
   int64_t s;
   oEbmlSchemaNode const* v;
};
typedef struct oEbmlSchemaNodeSlice oEbmlSchemaNodeSlice;

struct oEbmlSchemaNode
{
   oEbmlSchemaNode const* val;
   oEbmlSchemaNodeSlice sub;
};

ODDEBML_API extern cMeta const O_EbmlSchemaMeta;

struct OEbmlSchema;
typedef struct OEbmlSchema OEbmlSchema;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDEBML_API OEbmlSchema* build_ebml_schema_o( oEbmlDeclPtrSlice elements,
                                              cErrorStack es[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool get_ebml_schema_node_o( OEbmlSchema const* schema,
                                         oEbmlSchemaNode node[static 1] );

ODDEBML_API bool get_ebml_schema_root_o( OEbmlSchema const* schema,
                                         oEbmlSchemaNode node[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool write_ebml_schema_node_o( cRecorder rec[static 1],
                                           oEbmlSchemaNode const node[static 1],
                                           char const fmt[static 1] );

#endif