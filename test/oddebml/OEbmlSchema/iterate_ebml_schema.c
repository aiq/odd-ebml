#include "clingo/lang/expect.h"
#include "oddebml/OEbmlSchema.h"

int main( void )
{
   init_tap_c_();

   OEbmlSchema* schema = new_ebml_schema_o();
   require_c_( attach_ebml_header_schema_o( schema ) );

   cVarUint32Slice ids = scalars_c_( 20, uint32_t );
   cVarCharsSlice names = structs_c_( 20, cChars );

   int64_t i = 0;
   oEbmlDecl const* decl;
   iterate_ebml_schema_c_( itr, decl, schema )
   {
      require_c_( i < ids.s );
      ids.v[i] = decl->id.raw;
      names.v[i] = c_c( decl->name );
      ++i;
   }
   ids.s = i;
   names.s = i;

   cUint32Slice expIds = slice_c_( uint32_t, 0x1A45DFA3,
      0x4286, 0x42F7, 0x42F2, 0x42F3, 0x4282, 0x4287, 0x4285 );
   cCharsSlice expNames = cs_c_( "EBML",
      "EBMLVersion", "EBMLReadVersion", "EBMLMaxIDLength", "EBMLMaxSizeLength",
      "DocType", "DocTypeVersion", "DocTypeReadVersion"
   );

   expect_eq_c_( cmp_uint32_slice_c( as_uint32_slice_c( ids ), expIds ) );
   times_c_( i, j )
   {
      expect_eq_c_( cmp_chars_c( names.v[j], expNames.v[j] ) );
   }
   
   release_all_c_( schema );

   return finish_tap_c_();
}