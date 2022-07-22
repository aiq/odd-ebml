#ifndef ODDEBML_ERROR_H
#define ODDEBML_ERROR_H

#include "clingo/lang/CObject.h"
#include "clingo/lang/error.h"
#include "oddebml/apidecl.h"
#include "oddebml/o_EbmlType.h"
#include "oddebml/oEbmlId.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

ODDEBML_API extern cErrorType const O_EbmlError;

ODDEBML_API extern cErrorType const O_MissingEdmlIdError;

struct oMissingEdmlIdErrorData
{
   oEbmlId id;
};
typedef struct oMissingEdmlIdErrorData oMissingEdmlIdErrorData;

ODDEBML_API extern cErrorType const O_UnmarshalEdmlError;

struct oUnmarshalEdmlErrorData
{
   oEbmlId id;
   o_EbmlType type;
};
typedef struct oUnmarshalEdmlErrorData oUnmarshalEdmlErrorData;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDEBML_API bool push_ebml_error_o( cErrorStack es[static 1] );

ODDEBML_API bool push_missing_ebml_id_error_o( cErrorStack es[static 1],
                                               oEbmlId id );

ODDEBML_API bool push_unmarshal_ebml_error_o( cErrorStack es[static 1],
                                              oEbmlId id,
                                              o_EbmlType type );

#endif