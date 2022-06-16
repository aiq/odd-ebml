#ifndef ODDEBML_EBML_TOKEN_H
#define ODDEBML_EBML_TOKEN_H

#include "oddebml/apidecl.h"
#include "oddebml/oEbmlDate.h"
#include "oddebml/oEbmlId.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oEbmlToken
{
   oEbmlId id;
   cBytes bytes;
};
typedef struct oEbmlToken oEbmlToken;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#define ebml_token_o_( Id, Bytes )                                             \
(                                                                              \
   (oEbmlToken){ .id=(Id), .bytes=(Bytes) }                                    \
)

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

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool record_ebml_token_o( cRecorder rec[static 1],
                                      oEbmlToken const tok[static 1] );

ODDEBML_API bool scan_ebml_token_o( cScanner sca[static 1],
                                    oEbmlToken tok[static 1] );

#endif