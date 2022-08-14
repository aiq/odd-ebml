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

ODDEBML_API bool ebml_as_int_o( oEbmlElement const elem[static 1],
                                int64_t val[static 1] );

ODDEBML_API bool ebml_as_uint_o( oEbmlElement const elem[static 1],
                                 uint64_t val[static 1] );

ODDEBML_API bool ebml_as_float_o( oEbmlElement const elem[static 1],
                                  double val[static 1] );

ODDEBML_API bool ebml_as_string_o( oEbmlElement const elem[static 1],
                                   cChars val[static 1] );

ODDEBML_API bool ebml_as_utf8_o( oEbmlElement const elem[static 1],
                                 cChars val[static 1] );

ODDEBML_API bool ebml_as_date_o( oEbmlElement const elem[static 1],
                                 oEbmlDate val[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool record_ebml_element_o( cRecorder rec[static 1],
                                        oEbmlElement const elem[static 1] );

ODDEBML_API bool view_ebml_element_o( cScanner sca[static 1],
                                      oEbmlElement elem[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool view_ebml_binary_element_o( cScanner sca[static 1],
                                             cBytes val[static 1] );

ODDEBML_API bool scan_ebml_int_element_o( cScanner sca[static 1],
                                          int64_t val[static 1] );

ODDEBML_API bool scan_ebml_uint_element_o( cScanner sca[static 1],
                                           uint64_t val[static 1] );

ODDEBML_API bool scan_ebml_float_element_o( cScanner sca[static 1],
                                            double val[static 1] );

ODDEBML_API bool view_ebml_string_element_o( cScanner sca[static 1],
                                             cChars val[static 1] );

ODDEBML_API bool view_ebml_utf8_element_o( cScanner sca[static 1],
                                           cChars val[static 1] );

ODDEBML_API bool scan_ebml_date_element_o( cScanner sca[static 1],
                                           oEbmlDate val[static 1] );

#endif