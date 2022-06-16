#ifndef ODDEBML_EBML_ELEMENT_H
#define ODDEBML_EBML_ELEMENT_H

#include "oddebml/apidecl.h"
#include "oddebml/oEbmlDate.h"
#include "oddebml/oEbmlId.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oEbmlElement
{
   oEbmlId id;
   cBytes bytes;
};
typedef struct oEbmlElement oEbmlElement;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#define ebml_element_o_( Id, Bytes )                                           \
(                                                                              \
   (oEbmlElement){ .id=(Id), .bytes=(Bytes) }                                  \
)

/*******************************************************************************

*******************************************************************************/

ODDEBML_API
bool get_ebml_int_o( oEbmlElement const elem[static 1], int64_t val[static 1] );

ODDEBML_API
bool get_ebml_uint_o( oEbmlElement const elem[static 1], uint64_t val[static 1] );

ODDEBML_API
bool get_ebml_float_o( oEbmlElement const elem[static 1], double val[static 1] );

ODDEBML_API
bool get_ebml_string_o( oEbmlElement const elem[static 1], cChars val[static 1] );

ODDEBML_API
bool get_ebml_utf8_o( oEbmlElement const elem[static 1], cChars val[static 1] );

ODDEBML_API
bool get_ebml_date_o( oEbmlElement const elem[static 1], oEbmlDate val[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool record_ebml_element_o( cRecorder rec[static 1],
                                        oEbmlElement const elem[static 1] );

ODDEBML_API bool scan_ebml_element_o( cScanner sca[static 1],
                                      oEbmlElement elem[static 1] );

#endif