#ifndef ODDEBML_EBML_ELEMENT_H
#define ODDEBML_EBML_ELEMENT_H

#include "oddebml/apidecl.h"
#include "oddebml/o_EbmlType.h"
#include "oddebml/oEbmlId.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

struct oEbmlElement;
typedef struct oEbmlElement oEbmlElement;

struct oEbmlElement
{
   oEbmlElement const* parent;
   char const* name;
   oEbmlId id;
   int64_t minOccurs;
   int64_t maxOccurs;
   o_EbmlType type;
};

struct oEbmlElementPtrSlice
{
   int64_t s;
   oEbmlElement* v;
};
typedef struct oEbmlElementPtrSlice oEbmlElementPtrSlice;

/*******************************************************************************

*******************************************************************************/

ODDEBML_API extern oEbmlElement const O_EbmlRoot;

ODDEBML_API extern oEbmlElement const O_Ebml;
ODDEBML_API extern oEbmlElement const O_EbmlVersion;
ODDEBML_API extern oEbmlElement const O_EbmlReadVersion;
ODDEBML_API extern oEbmlElement const O_EbmlMaxIdLength;
ODDEBML_API extern oEbmlElement const O_EbmlMaxSizeLength;

ODDEBML_API extern oEbmlElement const O_EbmlDocType;
ODDEBML_API extern oEbmlElement const O_EbmlDocTypeVersion;
ODDEBML_API extern oEbmlElement const O_EbmlDocTypeReadVersion;

ODDEBML_API extern oEbmlElement const O_EbmlSignatureSlot;
ODDEBML_API extern oEbmlElement const O_EbmlSignatureAlgo;
ODDEBML_API extern oEbmlElement const O_EbmlSignatureHash;
ODDEBML_API extern oEbmlElement const O_EbmlSignaturePublicKey;
ODDEBML_API extern oEbmlElement const O_EbmlSignature;
ODDEBML_API extern oEbmlElement const O_EbmlSignatureElements;
ODDEBML_API extern oEbmlElement const O_EbmlSignatureElementList;
ODDEBML_API extern oEbmlElement const O_EbmlSignedElement;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

#define ebml_element_o_( Parent, Name, Id, MinOccurs, MaxOccurs, Type )        \
(                                                                              \
   (oEbmlElement){                                                             \
      .parent=(Parent),                                                        \
      .name=(Name),                                                            \
      .id=(Id),                                                                \
      .minOccurs=(MinOccurs),                                                  \
      .maxOccurs=(MaxOccurs),                                                  \
      .type=(Type)                                                             \
   }                                                                           \
)

#endif