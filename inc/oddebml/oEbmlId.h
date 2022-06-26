#ifndef ODDEBML_EBML_ID_H
#define ODDEBML_EBML_ID_H

#include "clingo/io/cRecorder.h"
#include "clingo/io/cScanner.h"
#include "clingo/type/uint32.h"
#include "oddebml/apidecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oEbmlId {
   uint32_t raw;
};
typedef struct oEbmlId oEbmlId;

/*******************************************************************************
 generated
*******************************************************************************/

SLICE_DEF_C_(
   oEbmlId,             // Type
   oEbmlIdSlice,        // SliceType
   ebml_id_slice_o,     // FuncName
   oVarEbmlIdSlice,     // VarSliceType
   var_ebml_id_slice_o  // VarFuncName
)

/*******************************************************************************

*******************************************************************************/

ODDEBML_API extern int32_t const O_MaxEbmlId;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

ODDEBML_API inline oEbmlId ebml_id_o( uint32_t raw )
{
   return (oEbmlId){ .raw = raw };
}

ODDEBML_API oEbmlId encode_ebml_id_o( int32_t val );

/*******************************************************************************
 overall
*******************************************************************************/

ODDEBML_API inline int cmp_ebml_id_o( oEbmlId id, oEbmlId oth )
{
   return cmp_uint32_c( id.raw, oth.raw );
}

ODDEBML_API int32_t decode_ebml_id_o( oEbmlId id );

ODDEBML_API int8_t ebml_id_length_o( oEbmlId id );

ODDEBML_API bool ebml_id_is_valid_o( oEbmlId id );

ODDEBML_API bool eq_ebml_id_o( oEbmlId id, oEbmlId oth );

ODDEBML_API oEbmlId invalid_ebml_id_o( void );

/*******************************************************************************
 io
*******************************************************************************/

ODDEBML_API bool fread_ebml_id_o( FILE* f, oEbmlId id[static 1] );

ODDEBML_API bool fwrite_ebml_id_o( FILE* f, oEbmlId id );

ODDEBML_API bool on_ebml_id_o( cScanner sca[static 1], oEbmlId id );

ODDEBML_API bool record_ebml_id_o( cRecorder rec[static 1], oEbmlId id );

ODDEBML_API bool scan_ebml_id_o( cScanner sca[static 1], oEbmlId id[static 1] );

ODDEBML_API bool write_ebml_id_o( cRecorder rec[static 1],
                                  oEbmlId id,
                                  char const fmt[static 1] );

#endif