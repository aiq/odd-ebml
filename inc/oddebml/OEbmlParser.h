#ifndef ODDEBML_EBML_PARSER_H
#define ODDEBML_EBML_PARSER_H

#include "clingo/lang/CObject.h"
#include "oddebml/apidecl.h"
#include "oddebml/error.h"
#include "oddebml/oEbmlElement.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

ODDEBML_API extern cMeta const O_EbmlParserMeta;

struct OEbmlParser;
typedef struct OEbmlParser OEbmlParser;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDEBML_API OEbmlParser* new_ebml_parser_o( oEbmlId id, cBytes bin );

ODDEBML_API OEbmlParser* make_ebml_parser_o( oEbmlId id, cVarBytes bin );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool go_to_ebml_child_o( OEbmlParser* p,
                                     oEbmlId id,
                                     oEbmlElement elem[static 1] );

ODDEBML_API bool go_to_ebml_parent_o( OEbmlParser* p,
                                      oEbmlId id,
                                      oEbmlElement elem[static 1] );

ODDEBML_API bool go_to_ebml_sibling_o( OEbmlParser* p,
                                       oEbmlId id,
                                       oEbmlElement elem[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool curr_ebml_element_o( OEbmlParser const* p,
                                      oEbmlElement elem[static 1] );

ODDEBML_API bool curr_ebml_id_o( OEbmlParser const* p, oEbmlId id[static 1] );

ODDEBML_API
bool parse_ebml_child_o( OEbmlParser* p, oEbmlElement elem[static 1] );

ODDEBML_API
bool parse_ebml_element_o( OEbmlParser* p, oEbmlElement elem[static 1] );

ODDEBML_API
bool parse_ebml_parent_o( OEbmlParser* p, oEbmlElement elem[static 1] );

/*******************************************************************************
 
*******************************************************************************/

#endif