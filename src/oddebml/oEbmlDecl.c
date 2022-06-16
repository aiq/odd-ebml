#include "oddebml/oEbmlDecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************

*******************************************************************************/

#define oEBML_HEADER_DECL_LIST_                                                \
   XMAP_C_( O_EbmlRoot, NULL, "", 0x00, 1, 1, o_EbmlMaster ) \
    \
   XMAP_C_( O_Ebml,                    &O_EbmlRoot,   "EBML",                 0x1A45DFA3, 1, 1, o_EbmlMaster ) \
   XMAP_C_( O_EbmlVersion,             &O_Ebml,       "EBMLVersion",          0x4286,     1, 1, o_EbmlUint ) \
   XMAP_C_( O_EbmlReadVersion,         &O_Ebml,       "EBMLReadVersion",      0x42F7,     1, 1, o_EbmlUint ) \
   XMAP_C_( O_EbmlMaxIdLength,         &O_Ebml,       "EBMLMaxIDLength",      0x42F2,     1, 1, o_EbmlUint ) \
   XMAP_C_( O_EbmlMaxSizeLength,       &O_Ebml,       "EBMLMaxSizeLength",    0x42F3,     1, 1, o_EbmlUint ) \
   XMAP_C_( O_EbmlDocType,             &O_Ebml,       "DocType",              0x4282,     1, 1, o_EbmlString ) \
   XMAP_C_( O_EbmlDocTypeVersion,      &O_Ebml,       "DocTypeVersion",       0x4287,     1, 1, o_EbmlUint ) \
   XMAP_C_( O_EbmlDocTypeReadVersion,  &O_Ebml,       "DocTypeReadVersion",   0x4285,     1, 1, o_EbmlUint ) \
    \
   XMAP_C_( O_EbmlCrc32,   NULL, "CRC-32",   0xBF, 0, INT64_MAX, o_EbmlBinary ) \
   XMAP_C_( O_EbmlVoid,    NULL, "Void",     0xEC, 0, INT64_MAX, o_EbmlBinary ) \
    \
   XMAP_C_( O_EbmlSignatureSlot,          NULL,                         "SignatureSlot",        0x1B538667, 0, INT64_MAX, o_EbmlUint ) \
   XMAP_C_( O_EbmlSignatureAlgo,          &O_EbmlSignatureSlot,         "SignatureAlgo",        0x7E8A, 0, 1, o_EbmlUint ) \
   XMAP_C_( O_EbmlSignatureHash,          &O_EbmlSignatureSlot,         "SignatureHash",        0x7E9A, 0, 1, o_EbmlUint ) \
   XMAP_C_( O_EbmlSignaturePublicKey,     &O_EbmlSignatureSlot,         "SignaturePublicKey",   0x7EA5, 0, 1, o_EbmlBinary ) \
   XMAP_C_( O_EbmlSignature,              &O_EbmlSignatureSlot,         "Signature",            0x7EB5, 0, 1, o_EbmlBinary ) \
   XMAP_C_( O_EbmlSignatureElements,      &O_EbmlSignatureSlot,         "SignatureElements",    0x7E5B, 0, 1, o_EbmlMaster ) \
   XMAP_C_( O_EbmlSignatureElementList,   &O_EbmlSignatureElements,     "SignatureElementList", 0x7E7B, 0, INT64_MAX, o_EbmlMaster ) \
   XMAP_C_( O_EbmlSignedElement,          &O_EbmlSignatureElementList,  "SignatureElement",     0x6532, 0, INT64_MAX, o_EbmlBinary )

#define XMAP_C_( Var, Parent, Name, Id, MinOccurs, MaxOccurs, Type )           \
oEbmlDecl const Var = ebml_decl_o_( Parent, Name, (oEbmlId){ .raw=Id }, MinOccurs, MaxOccurs, Type );

oEBML_HEADER_DECL_LIST_;
#undef XMAP_C_

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/