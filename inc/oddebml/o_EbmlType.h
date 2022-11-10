#ifndef ODDEBML_OEBMLTYPE_H
#define ODDEBML_OEBMLTYPE_H

#include "oddebml/apidecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
*******************************************************************************/

#define oEBML_TYPE_                                                            \
   XMAP_C_( o_EbmlInt, 0 )                                                     \
   XMAP_C_( o_EbmlUint, 1 )                                                    \
   XMAP_C_( o_EbmlFloat, 2 )                                                   \
   XMAP_C_( o_EbmlString, 3 )                                                  \
   XMAP_C_( o_EbmlUtf8, 4 )                                                    \
   XMAP_C_( o_EbmlDate, 5 )                                                    \
   XMAP_C_( o_EbmlMaster, 6 )                                                  \
   XMAP_C_( o_EbmlBinary, 7 )

#define XMAP_C_( N, I ) N = I,
enum o_EbmlType { oEBML_TYPE_ };
#undef XMAP_C_

typedef enum o_EbmlType o_EbmlType;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDEBML_API char const* stringify_ebml_type_c( o_EbmlType type );

#endif