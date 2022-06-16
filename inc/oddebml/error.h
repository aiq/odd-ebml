#ifndef ODDEBML_ERROR_H
#define ODDEBML_ERROR_H

#include "clingo/lang/CObject.h"
#include "clingo/lang/error.h"
#include "oddebml/apidecl.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

CLINGO_API extern cErrorType const C_EbmlError;

struct cEbmlErrorData
{
   int number;
};
typedef struct cEbmlErrorData cEbmlErrorData;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

CLINGO_API bool push_ebml_error_c( cErrorStack es[static 1],
                                   FILE* file );

*******************************************************************************/

CLINGO_API bool note_ebml_error_c( cRecorder rec[static 1], cError const* err );

#endif