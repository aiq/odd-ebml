#include "oddebml/OEbmlParser.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

ODDEBML_API extern cMeta const O_EbmlMasterMeta;

struct OEbmlMaster;
typedef struct OEbmlMaster OEbmlMaster;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

OEbmlParser* make_ebml_parser_o( cBytes data, cErrorStack es[static 1] )
{
   return NULL;
}

/*******************************************************************************
 traverse
*******************************************************************************/

bool go_to_ebml_child_o( OEbmlParser* p,
                         oEbmlId id,
                         oEbmlToken tok[static 1] )
{
   return false;
}

bool go_to_ebml_parent_o( OEbmlParser* p,
                          oEbmlId id,
                          oEbmlToken tok[static 1] )
{
   return false;
}

bool go_to_ebml_sibling_o( OEbmlParser* p,
                           oEbmlId id,
                           oEbmlToken tok[static 1] )
{
   return false;
}

/*******************************************************************************
 traverse
*******************************************************************************/

bool curr_ebml_token_o( OEbmlParser const* p, oEbmlToken tok[static 1] )
{
   return false;
}

bool first_ebml_child_o( OEbmlParser* p, oEbmlToken tok[static 1] )
{
   return false;
}

bool next_ebml_sibling_o( OEbmlParser* p, oEbmlToken tok[static 1] )
{
   return false;
}

bool prev_ebml_parent_o( OEbmlParser* p, oEbmlToken tok[static 1] )
{
   return false;
}

/*******************************************************************************
 
*******************************************************************************/

int64_t count_ebml_children_o( OEbmlParser* p, oEbmlId id )
{
   return 0;
}

/*******************************************************************************
 get
*******************************************************************************/

bool get_ebml_int_o( oEbmlToken const tok[static 1], int64_t val[static 1] )
{
   return false;
}

bool get_ebml_uint_o( oEbmlToken const tok[static 1], uint64_t val[static 1] )
{
   return false;
}

bool get_ebml_float_o( oEbmlToken const tok[static 1], double val[static 1] )
{
   return false;
}

bool get_ebml_string_o( oEbmlToken const tok[static 1], cChars val[static 1] )
{
   return false;
}

bool get_ebml_utf8_o( oEbmlToken const tok[static 1], cChars val[static 1] )
{
   return false;
}

bool get_ebml_date_o( oEbmlToken const tok[static 1], oEbmlDate val[static 1] )
{
   return false;
}