#ifndef ODDEBML_OEBMLBUILDER_H
#define ODDEBML_OEBMLBUILDER_H

#include "clingo/lang/CObject.h"
#include "oddebml/apidecl.h"
#include "oddebml/oEbmlElement.h"
#include "oddebml/oEbmlSize.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

ODDEBML_API extern cMeta const O_EbmlBuilderMeta;

struct OEbmlBuilder;
typedef struct OEbmlBuilder OEbmlBuilder;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDEBML_API OEbmlBuilder* make_ebml_builder_o( int64_t cap );

ODDEBML_API OEbmlBuilder* new_ebml_builder_o( void );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API cBytes built_ebml_o( OEbmlBuilder* b );

/*******************************************************************************

*******************************************************************************/

#define begin_ebml_master_o_( Builder, Id )                                    \
   begin_ebml_master_o( (Builder), (Id), unknown_ebml_size_o( 2 ) )
ODDEBML_API bool begin_ebml_master_o( OEbmlBuilder* b,
                                      oEbmlId id,
                                      oEbmlSize size );

ODDEBML_API bool finish_ebml_master_o( OEbmlBuilder* b );

/*******************************************************************************
 append
*******************************************************************************/

ODDEBML_API
bool append_ebml_element_o( OEbmlBuilder* b, oEbmlElement const tok[static 1] );

ODDEBML_API bool append_embl_int_o( OEbmlBuilder* b, oEbmlId id, int64_t val );

ODDEBML_API bool append_ebml_uint_o( OEbmlBuilder* b, oEbmlId id, uint64_t val );

ODDEBML_API bool append_ebml_float_o( OEbmlBuilder* b, oEbmlId id, double val );

ODDEBML_API bool append_ebml_string_o( OEbmlBuilder* b, oEbmlId id, cChars val );

ODDEBML_API bool append_ebml_utf8_o( OEbmlBuilder* b, oEbmlId id, cChars val );

ODDEBML_API bool append_ebml_date_o( OEbmlBuilder* b, oEbmlId id, oEbmlDate val );

ODDEBML_API bool append_ebml_binary_o( OEbmlBuilder* b, oEbmlId id, cBytes val );

ODDEBML_API bool append_empty_ebml_o( OEbmlBuilder* b, oEbmlId id );

#endif
