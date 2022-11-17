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

#endif