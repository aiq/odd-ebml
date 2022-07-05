#ifndef ODDEBML_EBML_DECL_H
#define ODDEBML_EBML_DECL_H

#include "oddebml/apidecl.h"
#include "oddebml/o_EbmlType.h"
#include "oddebml/oEbmlId.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

struct oEbmlDecl
{
   char const* name;
   oEbmlId id;
   int64_t minOccurs;
   int64_t maxOccurs;
   o_EbmlType type;
};
typedef struct oEbmlDecl oEbmlDecl;

SLICE_DEF_C_(
   oEbmlDecl,              // Type
   oEbmlDeclSlice,         // SliceType
   ebml_decl_slice_c,      // FuncName
   oVarEbmlDeclSlice,      // VarSliceType
   var_ebml_decl_slice_c   // VarFuncName
)

/*******************************************************************************

*******************************************************************************/

ODDEBML_API extern oEbmlDecl const O_EbmlRoot;

ODDEBML_API extern oEbmlDecl const O_Ebml;
ODDEBML_API extern oEbmlDecl const O_EbmlVersion;
ODDEBML_API extern oEbmlDecl const O_EbmlReadVersion;
ODDEBML_API extern oEbmlDecl const O_EbmlMaxIdLength;
ODDEBML_API extern oEbmlDecl const O_EbmlMaxSizeLength;

ODDEBML_API extern oEbmlDecl const O_EbmlDocType;
ODDEBML_API extern oEbmlDecl const O_EbmlDocTypeVersion;
ODDEBML_API extern oEbmlDecl const O_EbmlDocTypeReadVersion;

ODDEBML_API extern oEbmlDecl const O_EbmlCrc32;
ODDEBML_API extern oEbmlDecl const O_EbmlVoid;

ODDEBML_API extern oEbmlDecl const O_EbmlSignatureSlot;
ODDEBML_API extern oEbmlDecl const O_EbmlSignatureAlgo;
ODDEBML_API extern oEbmlDecl const O_EbmlSignatureHash;
ODDEBML_API extern oEbmlDecl const O_EbmlSignaturePublicKey;
ODDEBML_API extern oEbmlDecl const O_EbmlSignature;
ODDEBML_API extern oEbmlDecl const O_EbmlSignatureElements;
ODDEBML_API extern oEbmlDecl const O_EbmlSignatureElementList;
ODDEBML_API extern oEbmlDecl const O_EbmlSignedElement;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#define ebml_decl_o_( Name, Id, MinOccurs, MaxOccurs, Type )                   \
(                                                                              \
   (oEbmlDecl){                                                                \
      .name=(Name),                                                            \
      .id=(Id),                                                                \
      .minOccurs=(MinOccurs),                                                  \
      .maxOccurs=(MaxOccurs),                                                  \
      .type=(Type)                                                             \
   }                                                                           \
)

ODDEBML_API oEbmlDeclSlice get_ebml_header_decl_o( oVarEbmlDeclSlice buf );

ODDEBML_API oEbmlDeclSlice ebml_header_decl_o( void );

ODDEBML_API bool write_ebml_decl_o( cRecorder rec[static 1],
                                    oEbmlDecl const decl[static 1],
                                    char const fmt[static 1] );

#endif