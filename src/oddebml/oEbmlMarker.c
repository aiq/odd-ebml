#include "oddebml/oEbmlMarker.h"

#include "_/misc.h"
#include "clingo/io/FILE.h"
#include "oddebml/oEbmlElement.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

int cmp_ebml_marker_o( oEbmlMarker const a[static 1],
                       oEbmlMarker const b[static 1] )
{
   if ( a->pos < b->pos )
   {
      return -1;
   }
   else if ( a->pos > b->pos )
   {
      return 1;
   }
   return 0;
}

bool ebml_marker_covers_o( oEbmlMarker const marker[static 1],
                           oEbmlMarker const oth[static 1] )
{
   cRange markerRng = sized_range_c_( marker->pos, marker->size );
   cRange othRng = sized_range_c_( oth->pos, oth->size );
   return in_range_c( markerRng, othRng.min ) and
          in_range_c( markerRng, othRng.max );
}

bool fread_ebml_marker_o( FILE* f, oEbmlMarker marker[static 1] )
{
   must_exist_c_( f );

   oEbmlId id;
   if ( not fread_ebml_id_o( f, &id ) ) return false;

   oEbmlSize size;
   if ( not fread_ebml_size_o( f, &size ) ) return false;

   fpos_t pos;
   if ( fgetpos( f, &pos ) != 0 ) return false;

   marker->id = id;
   marker->size = decode_ebml_size_o( size );
   marker->pos = pos;

   return true;
}
