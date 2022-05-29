#include "oddebml/O_EbmlIds.h"

#define v_( Raw ) (oEbmlId){ .raw=(Raw) }

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 ebml basics
*******************************************************************************/

oEbmlId const O_Ebml = v_( 0x1A45DFA3 );
oEbmlId const O_EbmlVersion = v_( 0x4286 );
oEbmlId const O_EbmlReadVersion = v_( 0x42F7 );
oEbmlId const O_EbmlMaxIdLength = v_( 0x42F2 );
oEbmlId const O_EbmlMaxSizeLength = v_( 0x42F3 );

oEbmlId const O_EbmlDocType = v_( 0x4282 );
oEbmlId const O_EbmlDocTypeVersion = v_( 0x4287 );
oEbmlId const O_EbmlDocTypeReadVersion = v_( 0x4285 );

/*******************************************************************************
 global
*******************************************************************************/

oEbmlId const O_EbmlCrc32 = v_( 0xBF );
oEbmlId const O_EbmlVoid = v_( 0xEC );

/*******************************************************************************
 signature
*******************************************************************************/

oEbmlId const O_EbmlSignatureSlot = v_( 0x1B538667 );
oEbmlId const O_EbmlSignatureAlgo = v_( 0x7E8A );
oEbmlId const O_EbmlSignatureHash = v_( 0x7E9A );
oEbmlId const O_EbmlSignaturePublicKey = v_( 0x7EA5 );
oEbmlId const O_EbmlSignature = v_( 0x7EB5 );
oEbmlId const O_EbmlSignatureElements = v_( 0x7E5B );
oEbmlId const O_EbmlSignatureElementList = v_( 0x7E7B );
oEbmlId const O_EbmlSignedElement = v_( 0x6532 );