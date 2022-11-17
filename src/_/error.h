#ifndef ODDJSON_INTERN_ERROR_H
#define ODDJSON_INTERN_ERROR_H

#include "oddebml/error.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

static inline bool push_ebml_error_o( cErrorStack es[static 1] )
{
   return push_error_c_( es, &O_EbmlError );
}

static inline bool push_ebml_lit_error_o( cErrorStack es[static 1],
                                          char const str[static 1] )
{
   return push_lit_error_c( es, str ) || push_ebml_error_o( es );
}

static inline bool push_missing_ebml_id_error_o( cErrorStack es[static 1],
                                                 oEbmlId id )
{
   oMissingEdmlIdErrorData d = { .id=id };
   int64_t dSize = sizeof_c_( oMissingEdmlIdErrorData );
   return push_error_c( es, &O_MissingEdmlIdError, &d, dSize ) ||
          push_ebml_error_o( es );
}

static inline bool push_unmarshal_ebml_error_o( cErrorStack es[static 1],
                                                oEbmlId id,
                                                o_EbmlType type )
{
   oUnmarshalEdmlErrorData d = { .id=id, .type=type };
   int64_t dSize = sizeof_c_( oUnmarshalEdmlErrorData );
   return push_error_c( es, &O_UnmarshalEdmlError, &d, dSize ) ||
          push_ebml_error_o( es );
}

#endif