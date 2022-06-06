#ifndef ODDEBML_EBML_BUILDER_H
#define ODDEBML_EBML_BUILDER_H

#include "clingo/lang/CObject.h"
#include "oddebml/apidecl.h"
#include "oddebml/oEbmlDate.h"
#include "oddebml/oEbmlId.h"

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

ODDEBML_API bool begin_ebml_master_o( OEbmlBuilder* b, oEbmlId id );

ODDEBML_API bool finish_ebml_master_o( OEbmlBuilder* b );

/*******************************************************************************
 append
*******************************************************************************/

ODDEBML_API bool append_embl_int_o( OEbmlBuilder* b, oEbmlId id, int64_t val );

ODDEBML_API bool append_ebml_uint_o( OEbmlBuilder* b, oEbmlId id, uint64_t val );

ODDEBML_API bool append_ebml_float_o( OEbmlBuilder* b, oEbmlId id, double val );

ODDEBML_API bool append_ebml_string_o( OEbmlBuilder* b, oEbmlId id, cChars val );

ODDEBML_API bool append_ebml_utf8_o( OEbmlBuilder* b, oEbmlId id, cChars val );

ODDEBML_API bool append_ebml_date_o( OEbmlBuilder* b, oEbmlId id, oEbmlDate val );

ODDEBML_API bool append_ebml_binary_o( OEbmlBuilder* b, oEbmlId id, cBytes val );

#endif