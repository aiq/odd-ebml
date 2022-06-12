#ifndef ODDEBML_EBML_PARSER_H
#define ODDEBML_EBML_PARSER_H

#include "clingo/lang/CObject.h"
#include "oddebml/apidecl.h"
#include "oddebml/error.h"
#include "oddebml/oEbmlDate.h"
#include "oddebml/oEbmlId.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

ODDEBML_API extern cMeta const O_EbmlMasterMeta;

struct OEbmlParser;
typedef struct OEbmlParser OEbmlParser;

struct oEbmlToken
{
   int64_t pos;
   oEbmlId id;
   cBytes bin;
};
typedef struct oEbmlToken oEbmlToken;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDEBML_API
OEbmlParser* make_ebml_parser_o( cBytes bin, cErrorStack es[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool go_to_ebml_child_o( OEbmlParser* p,
                                     oEbmlId id,
                                     oEbmlToken tok[static 1] );

ODDEBML_API bool go_to_ebml_parent_o( OEbmlParser* p,
                                      oEbmlId id,
                                      oEbmlToken tok[static 1] );

ODDEBML_API bool go_to_ebml_sibling_o( OEbmlParser* p,
                                       oEbmlId id,
                                       oEbmlToken tok[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool curr_ebml_token_o( OEbmlParser const* p,
                                    oEbmlToken tok[static 1] );

ODDEBML_API bool first_ebml_child_o( OEbmlParser* p, oEbmlToken tok[static 1] );

ODDEBML_API bool next_ebml_sibling_o( OEbmlParser* p, oEbmlToken tok[static 1] );

ODDEBML_API bool prev_ebml_parent_o( OEbmlParser* p, oEbmlToken tok[static 1] );

/*******************************************************************************
 
*******************************************************************************/

ODDEBML_API int64_t count_ebml_children_o( OEbmlParser* p, oEbmlId id );

/*******************************************************************************
 
*******************************************************************************/

ODDEBML_API
bool get_ebml_int_o( oEbmlToken const tok[static 1], int64_t val[static 1] );

ODDEBML_API
bool get_ebml_uint_o( oEbmlToken const tok[static 1], uint64_t val[static 1] );

ODDEBML_API
bool get_ebml_float_o( oEbmlToken const tok[static 1], double val[static 1] );

ODDEBML_API
bool get_ebml_string_o( oEbmlToken const tok[static 1], cChars val[static 1] );

ODDEBML_API
bool get_ebml_utf8_o( oEbmlToken const tok[static 1], cChars val[static 1] );

ODDEBML_API
bool get_ebml_date_o( oEbmlToken const tok[static 1], oEbmlDate val[static 1] );

#endif