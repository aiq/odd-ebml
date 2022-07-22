#ifndef ODDEBML_EBML_HEADER_H
#define ODDEBML_EBML_HEADER_H

#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "oddebml/apidecl.h"
#include "oddebml/OEbmlBuilder.h"
#include "oddebml/oEbmlElement.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oEbmlHeader {
   uint64_t version;
   uint64_t readVersion;
   uint64_t maxIdLength;
   uint64_t maxSizeLength;
   cChars docType;
   uint64_t docTypeVersion;
   uint64_t docTypeReadVersion;
};
typedef struct oEbmlHeader oEbmlHeader;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDEBML_API bool append_ebml_header_o( OEbmlBuilder* b,
                                       oEbmlHeader const header[static 1] );

ODDEBML_API bool unmarshal_ebml_header_o( oEbmlElement const elem[static 1],
                                          oEbmlHeader header[static 1],
                                          cErrorStack es[static 1] );

#endif