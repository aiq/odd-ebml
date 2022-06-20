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
   int64_t n = 0;
   while ( parse_ebml_child_o( p, elem ) )
   {
      ++n;
      if ( eq_ebml_id_o( elem->id, id ) ) return true;
   }
   for ( int64_t i = 0; i < n; ++i )
   {
      parse_ebml_parent_o( p, elem );
   }
   return false;
}

bool go_to_ebml_parent_o( OEbmlParser* p,
                          oEbmlId id,
                          oEbmlElement elem[static 1] )
{
   int64_t n = 0;
   while ( parse_ebml_parent_o( p, elem ) )
   {
      ++n;
      if ( eq_ebml_id_o( elem->id, id ) ) return true;
   }
   for ( int64_t i = 0; i < n; ++i )
   {
      parse_ebml_child_o( p, elem );
   }
   return false;
}

bool go_to_ebml_sibling_o( OEbmlParser* p,
                           oEbmlId id,
                           oEbmlElement elem[static 1] )
{
   int64_t oldPos = p->sca.pos;
   while ( parse_ebml_element_o( p, elem ) )
   {
      if ( eq_ebml_id_o( elem->id, id ) ) return true;
   }
   move_scanner_to_c( &(p->sca), oldPos );
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

bool curr_ebml_id_o( OEbmlParser const* p, oEbmlId id[static 1] )
{
   cScanner* sca = &scanner_copy_c_( &(p->sca) );
   return scan_ebml_id_o( sca, id );
}

bool parse_ebml_child_o( OEbmlParser* p, oEbmlElement elem[static 1] )
{
   oEbmlElement tmpElem;
   if ( not curr_ebml_element_o( p, &tmpElem ) ) return false;
   if ( not push_ebml_element_o( &(p->stack), tmpElem ) ) return false;

   p->sca = make_scanner_c_( tmpElem.bytes.s, tmpElem.bytes.v );
   return curr_ebml_element_o( p, elem );
}

bool parse_ebml_element_o( OEbmlParser* p, oEbmlElement elem[static 1] )
{
   return view_ebml_element_o( &(p->sca), elem );
}

bool parse_ebml_parent_o( OEbmlParser* p, oEbmlElement elem[static 1] )
{
   if ( p->stack.s == 0 ) return false;
   return pop_ebml_element_o( &(p->stack), elem );
}

/*******************************************************************************
 
*******************************************************************************/