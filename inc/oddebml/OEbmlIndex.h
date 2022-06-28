#ifndef ODDEBML_EBML_INDEX_H
#define ODDEBML_EBML_INDEX_H

#include "clingo/lang/CObject.h"
#include "oddebml/apidecl.h"
#include "oddebml/oEbmlMarker.h"
#include "oddebml/OEbmlSchema.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

ODDEBML_API extern cMeta const O_EbmlIndexMeta;

struct OEbmlIndex;
typedef struct OEbmlIndex OEbmlIndex;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************

*******************************************************************************/

ODDEBML_API OEbmlIndex* new_ebml_index_o( void );

ODDEBML_API OEbmlIndex* build_ebml_index_o( FILE* file,
                                            oEbmlIdSlice masters,
                                            oEbmlIdSlice toMark,
                                            cErrorStack es[static 1] );

/*******************************************************************************

*******************************************************************************/

ODDEBML_API bool attach_ebml_marker_o( OEbmlIndex* index,
                                       oEbmlMarker const marker[static 1] );

ODDEBML_API oEbmlMarkerSlice get_ebml_markers_o( OEbmlIndex const* index,
                                                 oEbmlId id );

#endif