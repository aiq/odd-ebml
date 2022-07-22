#include "oddebml/oEbmlHeader.h"

#include "_/misc.h"
#include "clingo/io/c_ImpExpError.h"
#include "oddebml/error.h"
#include "oddebml/o_EbmlType.h"
#include "oddebml/oEbmlDecl.h"
#include "oddebml/oEbmlElement.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

bool append_ebml_header_o( OEbmlBuilder* b,
                           oEbmlHeader const header[static 1] )
{
   must_exist_c_( b );

   begin_ebml_master_o( b, O_Ebml.id, unknown_ebml_size_o( 1 ) );
   {
      append_ebml_uint_o( b, O_EbmlVersion.id, header->version );
      append_ebml_uint_o( b, O_EbmlReadVersion.id, header->readVersion );
      append_ebml_uint_o( b, O_EbmlMaxIdLength.id, header->maxIdLength );
      append_ebml_uint_o( b, O_EbmlMaxSizeLength.id, header->maxSizeLength );
      append_ebml_string_o( b, O_EbmlDocType.id, header->docType );
      append_ebml_uint_o( b, O_EbmlDocTypeVersion.id, header->docTypeVersion );
      append_ebml_uint_o( b, O_EbmlDocTypeReadVersion.id, header->docTypeReadVersion );
   }
   finish_ebml_master_o( b );

   return true;
}

bool unmarshal_ebml_header_o( oEbmlElement const elem[static 1],
                              oEbmlHeader header[static 1],
                              cErrorStack es[static 1] )
{
   if ( not eq_ebml_id_o( elem->id, O_Ebml.id ) )
      return push_missing_ebml_id_error_o( es, O_Ebml.id );

   cScanner* sca = &make_scanner_c_( elem->bytes.s, elem->bytes.v );
   // -------------------------------------------------------------- EBMLVersion
   if ( not on_ebml_id_o( sca, O_EbmlVersion.id ) )
      return push_missing_ebml_id_error_o( es, O_EbmlVersion.id );

   if ( not scan_ebml_uint_element_o( sca, &(header->version) ) )
      return push_imp_exp_error_c( es, sca->err ) and
             push_unmarshal_ebml_error_o( es, O_EbmlVersion.id, o_EbmlUint );

   // ---------------------------------------------------------- EBMLReadVersion
   if ( not on_ebml_id_o( sca, O_EbmlReadVersion.id ) )
      return push_missing_ebml_id_error_o( es, O_EbmlReadVersion.id );

   if ( not scan_ebml_uint_element_o( sca, &(header->readVersion) ) )
      return push_imp_exp_error_c( es, sca->err ) and
             push_unmarshal_ebml_error_o( es, O_EbmlReadVersion.id, o_EbmlUint );

   // ---------------------------------------------------------- EBMLMaxIdLength
   if ( not on_ebml_id_o( sca, O_EbmlMaxIdLength.id ) )
      return push_missing_ebml_id_error_o( es, O_EbmlMaxIdLength.id );

   if ( not scan_ebml_uint_element_o( sca, &(header->maxIdLength) ) )
      return push_imp_exp_error_c( es, sca->err ) and
             push_unmarshal_ebml_error_o( es, O_EbmlMaxIdLength.id, o_EbmlUint );

   // -------------------------------------------------------- EBMLMaxSizeLength
   if ( not on_ebml_id_o( sca, O_EbmlMaxSizeLength.id ) )
      return push_missing_ebml_id_error_o( es, O_EbmlMaxSizeLength.id );

   if ( not scan_ebml_uint_element_o( sca, &(header->maxSizeLength) ) )
      return push_imp_exp_error_c( es, sca->err ) and
             push_unmarshal_ebml_error_o( es, O_EbmlMaxSizeLength.id, o_EbmlUint );

   // -------------------------------------------------------------- EBMLDocType
   if ( not on_ebml_id_o( sca, O_EbmlDocType.id ) )
      return push_missing_ebml_id_error_o( es, O_EbmlDocType.id );

   if ( not view_ebml_string_element_o( sca, &(header->docType) ) )
       return push_imp_exp_error_c( es, sca->err ) and
             push_unmarshal_ebml_error_o( es, O_EbmlDocType.id, o_EbmlString );

   // ----------------------------------------------------- O_EbmlDocTypeVersion
   if ( not on_ebml_id_o( sca, O_EbmlDocTypeVersion.id ) )
      return push_missing_ebml_id_error_o( es, O_EbmlDocTypeVersion.id );

   if ( not scan_ebml_uint_element_o( sca, &(header->docTypeVersion) ) )
      return push_imp_exp_error_c( es, sca->err ) and
             push_unmarshal_ebml_error_o( es, O_EbmlDocTypeVersion.id, o_EbmlUint );

   // ------------------------------------------------- O_EbmlDocTypeReadVersion
   if ( not on_ebml_id_o( sca, O_EbmlDocTypeReadVersion.id ) )
      return push_missing_ebml_id_error_o( es, O_EbmlDocTypeReadVersion.id );

   if ( not scan_ebml_uint_element_o( sca, &(header->docTypeReadVersion) ) )
      return push_imp_exp_error_c( es, sca->err ) and
             push_unmarshal_ebml_error_o( es, O_EbmlDocTypeReadVersion.id, o_EbmlUint );

   return sca->space == 0;
}
