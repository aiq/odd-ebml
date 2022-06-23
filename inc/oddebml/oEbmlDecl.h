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

struct oEbmlDeclSlice
{
   int64_t s;
   oEbmlDecl const* v;
};
typedef struct oEbmlDeclSlice oEbmlDeclSlice;

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

ODDEBML_API bool write_ebml_decl_o( cRecorder rec[static 1],
                                    oEbmlDecl const decl[static 1],
                                    char const fmt[static 1] );

#endif