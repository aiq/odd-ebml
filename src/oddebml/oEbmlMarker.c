#include "oddebml/oEbmlMarker.h"

#include "_/misc.h"
#include "clingo/io/FILE.h"
#include "oddebml/oEbmlElement.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

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

bool fread_ebml_child_marker_o( FILE* f,
                                oEbmlMarker const from[static 1],
                                oEbmlMarker marker[static 1] )
{
   must_exist_c_( f );

   if ( fsetpos( f, &(from->pos) ) != 0 ) return false;

   return fread_ebml_marker_o( f, marker );
}

bool fread_ebml_sibling_marker_o( FILE* f,
                                  oEbmlMarker const from[static 1],
                                  oEbmlMarker marker[static 1] )
{
   must_exist_c_( f );

   fpos_t next = from->pos + from->size;
   if ( fsetpos( f, &next ) != 0 ) return false;

   return fread_ebml_marker_o( f, marker );
}
