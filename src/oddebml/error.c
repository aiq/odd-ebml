#include "oddebml/error.h"

#include "clingo/io/write.h"

/*******************************************************************************
********************************************************* Types and Definitions
**+*****************************************************************************
 Definitions
*******************************************************************************/

SINGLE_ERROR_TYPE_C_( O_EbmlError, note_ebml_error_o, "oddebml error" )

static bool note_missing_ebml_id_error( cRecorder rec[static 1],
                                        cError const* err )
{
   must_be_c_( err->type == &O_MissingEdmlIdError );
   oMissingEdmlIdErrorData const* errd = get_error_data_c( err );

   return write_c_( rec, "missing EBML ID {u32:X}", errd->id.raw );
}
cErrorType const O_MissingEdmlIdError = {
   .desc = stringify_c_( O_MissingEdmlIdError ),
   .note = &note_missing_ebml_id_error
};

static bool note_unmarshal_ebml_error( cRecorder rec[static 1],
                                       cError const* err )
{
   must_be_c_( err->type == &O_UnmarshalEdmlError );
   oUnmarshalEdmlErrorData const* errd = get_error_data_c( err );

   char const* typeStr = stringify_ebml_type_c( errd->type );
   return write_c_( rec, "not able to unmarshal {u32:X}(type: {s})", errd->id.raw, typeStr );
}
cErrorType const O_UnmarshalEdmlError = {
   .desc = stringify_c_( O_UnmarshalEdmlError ),
   .note = &note_unmarshal_ebml_error
};
