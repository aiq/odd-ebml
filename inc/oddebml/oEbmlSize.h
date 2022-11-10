#ifndef ODDEBML_OEBMLSIZE_H
#define ODDEBML_OEBMLSIZE_H

#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/lang/error.h"
#include "clingo/type/uint64.h"
#include "oddebml/apidecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oEbmlSize {
   uint64_t raw;
};
typedef struct oEbmlSize oEbmlSize;

ODDEBML_API extern int64_t O_MaxEbmlSize;

/*******************************************************************************
 generated
*******************************************************************************/

SLICES_C_(
   oEbmlSize,           // Type
   oEbmlSizeSlice,      // SliceType
   oVarEbmlSizeSlice    // VarSliceType
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

ODDEBML_API inline oEbmlSize ebml_size_o( uint64_t raw )
{
   return (oEbmlSize){ .raw = raw };
}

ODDEBML_API oEbmlSize encode_ebml_size_o( int64_t val );

ODDEBML_API oEbmlSize invalid_ebml_size_o( void );

ODDEBML_API oEbmlSize unknown_ebml_size_o( int8_t len );

/*******************************************************************************
 overall
*******************************************************************************/

ODDEBML_API inline int cmp_ebml_size_o( oEbmlSize size, oEbmlSize oth )
{
   return cmp_uint64_c( size.raw, oth.raw );
}

ODDEBML_API int64_t decode_ebml_size_o( oEbmlSize size );

ODDEBML_API int8_t ebml_size_length_o( oEbmlSize size );

ODDEBML_API bool ebml_size_is_unknown_o( oEbmlSize size );

/*******************************************************************************
 io
*******************************************************************************/

ODDEBML_API bool fscan_ebml_size_o( FILE* f,
                                    oEbmlSize size[static 1],
                                    cErrorStack es[static 1] );

ODDEBML_API bool frecord_ebml_size_o( FILE* f,
                                      oEbmlSize size,
                                      cErrorStack es[static 1] );

ODDEBML_API bool record_ebml_size_o( cRecorder rec[static 1], oEbmlSize size );

ODDEBML_API
bool scan_ebml_size_o( cScanner sca[static 1], oEbmlSize size[static 1] );

ODDEBML_API bool write_ebml_size_o( cRecorder rec[static 1],
                                    oEbmlSize size,
                                    char const fmt[static 1] );

#endif