#include "oddebml/OEbmlParser.h"

#include "_/oEbmlElementStack.h"
#include "oddebml/oEbmlSize.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct OEbmlParser
{
   oEbmlElementStack stack;
   cScanner sca;
   cVarBytes mem;
};

static inline void cleanup( void* instance )
{
   OEbmlParser* p = instance;

   if ( p->stack.v )
   {
      free( p->stack.v );
   }

   if ( p->mem.v )
   {
      free( p->mem.v );
   }
}

cMeta const O_EbmlParserMeta = {
   .desc = stringify_c_( OEbmlParser ),
   .cleanup = &cleanup
};

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

static inline OEbmlParser* construct_ebml_parser( oEbmlId id,
                                                  cScanner sca[static 1],
                                                  cVarBytes mem )
{
   cObjectInfo const info = default_object_info_c_( &O_EbmlParserMeta );
   OEbmlParser* result = alloc_object_c_( OEbmlParser, &info );
   if ( result == NULL )
   {
      return NULL;
   }

   result->sca = *sca;
   result->mem = mem;
   if ( not alloc_ebml_element_stack_o( &(result->stack), 8 ) )
   {
      release_c( result );
      return NULL;
   }

   oEbmlElement root = ebml_element_o_( id, as_bytes_c( mem ) );
   push_ebml_element_o( &(result->stack), root );

   return result;
}

OEbmlParser* new_ebml_parser_o( oEbmlId id, cBytes bin )
{
   cScanner sca = make_scanner_c_( bin.s, bin.v );
   return construct_ebml_parser( id, &sca, empty_var_bytes_c() );
}

OEbmlParser* make_ebml_parser_o( oEbmlId id, cVarBytes bin )
{
   cScanner sca = make_scanner_c_( bin.s, bin.v );
   return construct_ebml_parser( id, &sca, bin );
}

/*******************************************************************************
 traverse
*******************************************************************************/

bool go_to_ebml_child_o( OEbmlParser* p,
                         oEbmlId id,
                         oEbmlElement elem[static 1] )
{
   return false;
}

bool go_to_ebml_parent_o( OEbmlParser* p,
                          oEbmlId id,
                          oEbmlElement tok[static 1] )
{
   return false;
}

bool go_to_ebml_sibling_o( OEbmlParser* p,
                           oEbmlId id,
                           oEbmlElement tok[static 1] )
{
   return false;
}

/*******************************************************************************
 traverse
*******************************************************************************/

bool curr_ebml_element_o( OEbmlParser const* p, oEbmlElement elem[static 1] )
{
   cScanner* sca = &scanner_copy_c_( &(p->sca) );
   return view_ebml_element_o( sca, elem );
}

bool first_ebml_child_o( OEbmlParser* p, oEbmlElement elem[static 1] )
{
   return false;
}

bool next_ebml_sibling_o( OEbmlParser* p, oEbmlElement elem[static 1] )
{
   return false;
}

bool prev_ebml_parent_o( OEbmlParser* p, oEbmlElement elem[static 1] )
{
   return false;
}

/*******************************************************************************
 
*******************************************************************************/

int64_t count_ebml_children_o( OEbmlParser* p, oEbmlId id )
{
   return 0;
}
