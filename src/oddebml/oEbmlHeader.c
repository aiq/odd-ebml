#include "oddebml/oEbmlHeader.h"

#include "_/misc.h"
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

bool ebml_as_header_o( oEbmlElement const elem[static 1],
                       oEbmlHeader header[static 1] )
{
   if ( not eq_ebml_id_o( elem->id, O_Ebml.id ) ) return false;

   cScanner* sca = &make_scanner_c_( elem->bytes.s, elem->bytes.v );
   once_c_( xyz )
   {
      if ( not on_ebml_id_o( sca, O_EbmlVersion.id ) ) break;
      if ( not scan_ebml_uint_element_o( sca, &(header->version) ) ) break;

      if ( not on_ebml_id_o( sca, O_EbmlReadVersion.id ) ) break;
      if ( not scan_ebml_uint_element_o( sca, &(header->readVersion) ) ) break;

      if ( not on_ebml_id_o( sca, O_EbmlMaxIdLength.id ) ) break;
      if ( not scan_ebml_uint_element_o( sca, &(header->maxIdLength) ) ) break;

      if ( not on_ebml_id_o( sca, O_EbmlMaxSizeLength.id ) ) break;
      if ( not scan_ebml_uint_element_o( sca, &(header->maxSizeLength) ) ) break;

      if ( not on_ebml_id_o( sca, O_EbmlDocType.id ) ) break;
      if ( not view_ebml_string_element_o( sca, &(header->docType) ) ) break;

      if ( not on_ebml_id_o( sca, O_EbmlDocTypeVersion.id ) ) break;
      if ( not scan_ebml_uint_element_o( sca, &(header->docTypeVersion) ) ) break;

      if ( not on_ebml_id_o( sca, O_EbmlDocTypeReadVersion.id ) ) break;
      if ( not scan_ebml_uint_element_o( sca, &(header->docTypeReadVersion) ) ) break;

      return sca->space == 0;
   }
   return false;
}

bool view_ebml_header_element_o( cScanner sca[static 1],
                                 oEbmlHeader header[static 1] )
{
   int64_t oldPos = sca->pos;
   oEbmlElement elem;
   if ( view_ebml_element_o( sca, &elem ) and
        eq_ebml_id_o( elem.id, O_Ebml.id ) and
        ebml_as_header_o( &elem, header ) )
   {
      return true;
   }
   move_scanner_to_c( sca, oldPos );
   return false;
}