#ifndef ODDEBML_EBML_FILE_TRAV_H
#define ODDEBML_EBML_FILE_TRAV_H

#include "oddebml/apidecl.h"
#include "oddebml/oEbmlMarker.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oEbmlFileTrav
{
   FILE* file;
   oEbmlMarker marker;
};
typedef struct oEbmlFileTrav oEbmlFileTrav;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#define start_ebml_file_trav_o_( File )                                        \
(                                                                              \
   (oEbmlFileTrav){                                                            \
      .file=(File),                                                            \
      .marker=(oEbmlMarker){                                                   \
         .pos=0                                                                \
      }                                                                        \
   }                                                                           \
)

ODDEBML_API bool visit_adj_ebml_marker_o( oEbmlFileTrav trav[static 1] );

ODDEBML_API bool visit_next_ebml_marker_o( oEbmlFileTrav trav[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool fread_ebml_bytes_o( oEbmlFileTrav trav[static 1],
                                     cVarBytes buf[static 1] );

ODDEBML_API bool fread_ebml_int_o( oEbmlFileTrav trav[static 1],
                                   int64_t val[static 1] );

ODDEBML_API bool fread_ebml_uint_o( oEbmlFileTrav trav[static 1],
                                    uint64_t val[static 1] );

ODDEBML_API bool fread_ebml_float_o( oEbmlFileTrav trav[static 1],
                                     double val[static 1] );

ODDEBML_API bool fread_ebml_string_o( oEbmlFileTrav trav[static 1],
                                      cVarChars val[static 1] );

ODDEBML_API bool fread_ebml_utf8_o( oEbmlFileTrav trav[static 1],
                                    cVarChars val[static 1] );

ODDEBML_API bool fread_ebml_date_o( oEbmlFileTrav trav[static 1],
                                    oEbmlDate date[static 1] );

#endif