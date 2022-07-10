#ifndef EBML_NAVI_DFS_H
#define EBML_NAVI_DFS_H

#include "ctx.h"
#include "clingo/io/print.h"
#include "oddebml/oEbmlTrav.h"

static bool visit_next_dfs( oEbmlTrav trav[static 1], NaviCtx ctx[static 1] )
{
   oEbmlDecl const* decl = get_from_ebml_decl_map_o( ctx->declMap,
                                                     trav->marker.id );
   if ( decl == NULL )
   {
      println_c_(
         "unknown element with ID {u32:x} @ {i64}",
         trav->marker.id.raw, trav->marker.pos
      );
      return false;
   }
   return ( decl->type == o_EbmlMaster )
      ? visit_adj_ebml_marker_o( trav, ctx->es )
      : visit_next_ebml_marker_o( trav, ctx->es );
}

#endif