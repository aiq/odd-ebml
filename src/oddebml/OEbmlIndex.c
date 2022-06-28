#include "oddebml/OEbmlIndex.h"

#include "_/OMisc.h"
#include "clingo/io/FILE.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct OEbmlIndex
{
   OIndexMap* map;
};

static inline void cleanup( void* instance )
{
   OEbmlIndex* i = instance;

   if ( i->map )
   {
      uint32_t const* key;
      oEbmlMarkerStack* stack;
      iterate_map_c_( itr, key, stack, i->map, next_var_in_index_map_o )
      {
         if ( not is_empty_c_( *stack ) )
         {
            free_ebml_marker_stack_o( stack );
         }
      }
   }
}

cMeta const O_EbmlIndexMeta = {
   .desc = stringify_c_( OEbmlIndex ),
   .cleanup = &cleanup
};

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

OEbmlIndex* new_ebml_index_o( void )
{
   cObjectInfo const info = default_object_info_c_( &O_EbmlIndexMeta );
   OEbmlIndex* result = alloc_object_c_( OEbmlIndex, &info );
   if ( result == NULL ) return NULL;

   result->map = new_index_map_o();
   if ( result->map == NULL )
   {
      release_c( result );
      return NULL;
   }

   return result;
};

static FIND_VAL_C_(
   find_ebml_id_o,   // FuncName,
   oEbmlIdSlice,     // SliceType,
   oEbmlId const,    // ValueType,
   oEbmlId const,    // SearchType,
   cmp_ebml_id_o,    // CmpFunc,
   do_deref_c_       // DoDeref
)

OEbmlIndex* build_ebml_index_o( FILE* file,
                                oEbmlIdSlice masters,
                                oEbmlIdSlice toMark,
                                cErrorStack es[static 1] )
{
   OEbmlIndex* index = new_ebml_index_o();
   if ( index == NULL )
   {
      return NULL;
   }

   oEbmlMarker marker;
   bool ok = true;
   bool freadCurr = false;
   while ( ok )
   {
      if ( freadCurr )
      {
         ok = fread_curr_ebml_marker_o( file, &marker );
      }
      else
      {
         ok = fread_next_ebml_marker_o( file, marker.size, &marker );
      }

      freadCurr = find_ebml_id_o( masters, marker.id ) != NULL;

      if ( find_ebml_id_o( toMark, marker.id ) != NULL )
      {
         ok = attach_ebml_marker_o( index, &marker );
      }
   }
   if ( ferror( file ) != 0 )
   {
      push_file_error_c( es, file );
      release_c( index );
      return false;
   }

   return index;
}

/*******************************************************************************

*******************************************************************************/

bool attach_ebml_marker_o( OEbmlIndex* index,
                           oEbmlMarker const marker[static 1] )
{
   must_exist_c_( index );
   uint32_t key = marker->id.raw;

   oEbmlMarkerStack* stack = get_var_from_index_map_o( index->map, key );
   if ( stack == NULL )
   {
      oEbmlMarkerStack tmp = {};
      if ( not set_on_index_map_o( index->map, key, tmp ) ) return false;

      stack = get_var_from_index_map_o( index->map, key );
      if ( stack == NULL ) return false;
   }

   return push_ebml_marker_o( stack, *marker );
}

oEbmlMarkerSlice get_ebml_markers_o( OEbmlIndex const* index, oEbmlId id )
{
   must_exist_c_( index );

   oEbmlMarkerStack const* stack = get_from_index_map_o( index->map,
                                                         id.raw );
   if ( stack == NULL )
   {
      return (oEbmlMarkerSlice)invalid_slice_c_();
   }
   return (oEbmlMarkerSlice){ .s=stack->s, .v=stack->v };
}