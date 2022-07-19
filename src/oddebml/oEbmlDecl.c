#include "oddebml/oEbmlDecl.h"

#include "clingo/io/write.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************

*******************************************************************************/

SLICE_IMPL_C_(
   oEbmlDecl,              // Type
   oEbmlDeclSlice,         // SliceType
   ebml_decl_slice_c,      // FuncName
   oVarEbmlDeclSlice,      // VarSliceType
   var_ebml_decl_slice_c   // VarFuncName
)

/*******************************************************************************

*******************************************************************************/

#define oEBML_HEADER_DECL_LIST_                                                \
   XMAP_C_( O_EbmlRoot, "EBMLRoot", 0x00, 1, 1, o_EbmlMaster ) \
   \
   XMAP_C_( O_Ebml,                    "EBML",                 0x1A45DFA3, 1, 0, o_EbmlMaster ) \
   XMAP_C_( O_EbmlVersion,             "EBMLVersion",          0x4286,     1, 0, o_EbmlUint ) \
   XMAP_C_( O_EbmlReadVersion,         "EBMLReadVersion",      0x42F7,     1, 0, o_EbmlUint ) \
   XMAP_C_( O_EbmlMaxIdLength,         "EBMLMaxIDLength",      0x42F2,     1, 0, o_EbmlUint ) \
   XMAP_C_( O_EbmlMaxSizeLength,       "EBMLMaxSizeLength",    0x42F3,     1, 0, o_EbmlUint ) \
   \
   XMAP_C_( O_EbmlDocType,             "DocType",              0x4282,     1, 0, o_EbmlString ) \
   XMAP_C_( O_EbmlDocTypeVersion,      "DocTypeVersion",       0x4287,     1, 0, o_EbmlUint ) \
   XMAP_C_( O_EbmlDocTypeReadVersion,  "DocTypeReadVersion",   0x4285,     1, 0, o_EbmlUint ) \
   \
   XMAP_C_( O_EbmlCrc32,   "CRC-32",   0xBF, 0, 1, o_EbmlBinary ) \
   XMAP_C_( O_EbmlVoid,    "Void",     0xEC, 0, 1, o_EbmlBinary ) \
   \
   XMAP_C_( O_EbmlSignatureSlot,          "SignatureSlot",        0x1B538667, 0, 1, o_EbmlUint ) \
   XMAP_C_( O_EbmlSignatureAlgo,          "SignatureAlgo",        0x7E8A, 0, 0, o_EbmlUint ) \
   XMAP_C_( O_EbmlSignatureHash,          "SignatureHash",        0x7E9A, 0, 0, o_EbmlUint ) \
   XMAP_C_( O_EbmlSignaturePublicKey,     "SignaturePublicKey",   0x7EA5, 0, 0, o_EbmlBinary ) \
   XMAP_C_( O_EbmlSignature,              "Signature",            0x7EB5, 0, 0, o_EbmlBinary ) \
   XMAP_C_( O_EbmlSignatureElements,      "SignatureElements",    0x7E5B, 0, 0, o_EbmlMaster ) \
   XMAP_C_( O_EbmlSignatureElementList,   "SignatureElementList", 0x7E7B, 0, 1, o_EbmlMaster ) \
   XMAP_C_( O_EbmlSignedElement,          "SignatureElement",     0x6532, 0, 1, o_EbmlBinary )

#define XMAP_C_( Var, Name, Id, MinOccurs, MaxOccurs, Type )           \
oEbmlDecl const Var = ebml_decl_o_( Name, (oEbmlId){ .raw=Id }, MinOccurs, MaxOccurs, Type );

oEBML_HEADER_DECL_LIST_;
#undef XMAP_C_

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

oEbmlDeclSlice get_ebml_header_decl_o( oVarEbmlDeclSlice buf )
{
   oEbmlDeclSlice src = slice_c_( oEbmlDecl,
      O_Ebml, O_EbmlVersion, O_EbmlReadVersion,
      O_EbmlMaxIdLength, O_EbmlMaxSizeLength,
      O_EbmlDocType, O_EbmlDocTypeVersion, O_EbmlDocTypeReadVersion,
      O_EbmlCrc32, O_EbmlVoid,
      O_EbmlSignatureSlot, O_EbmlSignatureAlgo, O_EbmlSignatureHash, 
      O_EbmlSignaturePublicKey, O_EbmlSignature,
      O_EbmlSignatureElements,
      O_EbmlSignatureElementList, O_EbmlSignedElement
   );

   buf.s = set_ebml_decl_slice_c( buf, src );
   if ( buf.s != src.s )
   {
      return (oEbmlDeclSlice)invalid_slice_c_();
   }

   return as_ebml_decl_slice_c( buf );
}

bool write_ebml_decl_o( cRecorder rec[static 1],
                        oEbmlDecl const decl[static 1],
                        char const fmt[static 1] )
{
   return write_c_( rec, "{cs} {u32:X}", decl->name, decl->id );
}