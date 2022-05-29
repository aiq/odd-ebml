#ifndef ODDEBML_EBML_IDS_H
#define ODDEBML_EBML_IDS_H

#include "oddebml/apidecl.h"
#include "oddebml/oEbmlId.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 ebml basics
*******************************************************************************/

ODDEBML_API extern oEbmlId const O_Ebml;
ODDEBML_API extern oEbmlId const O_EbmlVersion;
ODDEBML_API extern oEbmlId const O_EbmlReadVersion;
ODDEBML_API extern oEbmlId const O_EbmlMaxIdLength;
ODDEBML_API extern oEbmlId const O_EbmlMaxSizeLength;

ODDEBML_API extern oEbmlId const O_EbmlDocType;
ODDEBML_API extern oEbmlId const O_EbmlDocTypeVersion;
ODDEBML_API extern oEbmlId const O_EbmlDocTypeReadVersion;

/*******************************************************************************
 global
*******************************************************************************/

ODDEBML_API extern oEbmlId const O_EbmlCrc32;
ODDEBML_API extern oEbmlId const O_EbmlVoid;

/*******************************************************************************
 signature
*******************************************************************************/

ODDEBML_API extern oEbmlId const O_EbmlSignatureSlot;
ODDEBML_API extern oEbmlId const O_EbmlSignatureAlgo;
ODDEBML_API extern oEbmlId const O_EbmlSignatureHash;
ODDEBML_API extern oEbmlId const O_EbmlSignaturePublicKey;
ODDEBML_API extern oEbmlId const O_EbmlSignature;
ODDEBML_API extern oEbmlId const O_EbmlSignatureElements;
ODDEBML_API extern oEbmlId const O_EbmlSignatureElementList;
ODDEBML_API extern oEbmlId const O_EbmlSignedElement;

#endif
