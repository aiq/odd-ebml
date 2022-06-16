#include "clingo/lang/expect.h"
#include "oddebml/OEbmlBuilder.h"
#include "oddebml/oEbmlDecl.h"

#define expect_( Slice, ... )                                                  \
   expect_eq_c_( cmp_bytes_c_( (Slice), __VA_ARGS__ ) )

int main( void )
{
   init_tap_c_();

   OEbmlBuilder* b = retain_c( make_ebml_builder_o( 10 ) );

   begin_ebml_master_o_( b, O_Ebml.id );
   {
      append_ebml_uint_o( b, O_EbmlVersion.id, 1 );
      append_ebml_uint_o( b, O_EbmlReadVersion.id, 1 );
      append_empty_ebml_o( b, O_EbmlMaxIdLength.id );
      append_empty_ebml_o( b, O_EbmlMaxSizeLength.id );
   }
   finish_ebml_master_o( b );

   expect_( built_ebml_c( b ),
      0x1a, 0x45, 0xdf, 0xa3, 0x8e, // EBML ID + size
      0x42, 0x86, 0x81, 0x01,       // EBMLVersion ID + size + value
      0x42, 0xf7, 0x81, 0x01,       // EBMLReadVersion ID + size + value
      0x42, 0xf2, 0x80,             // EBMLMaxIdLength ID + default
      0x42, 0xf3, 0x80              // EBMLMaxSizeLength ID + default
   );

   release_all_c_( b );

   return finish_tap_c_();
}
