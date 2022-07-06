#ifndef EBML_NAVI_ENV_H
#define EBML_NAVI_ENV_H

#include "_/stack.h"
#include "clingo/container/map.h"
#include "clingo/io/FILE.h"
#include "oddebml/OEbmlDeclMap.h"

#include "mkv_decl.h"

STATIC_STACK_IMPL_C_(
   __attribute__((unused)),   // Attr
   oEbmlMarker,               // Type
   oEbmlMarkerStack,          // StackType
   ebml_marker_o,             // FuncSuffix
   ebml_marker_stack_o        // StackFuncSuffix
)

static uint64_t hash_ebml_marker_o( oEbmlMarker const m[static 1] )
{
   return uint64_c_( m->pos );
}

VAL_VAL_MAP_IMPL_C_(
   static __attribute__((unused)),  // Static
   ParentMarkerMap,     // MapType
   ParentMarkerMapRow,  // RowType
   oEbmlMarker,         // KeyType
   oEbmlMarker,         // ValType
   parent_marker_map_o, // FuncName
   ParentMarkerMapMeta, // Meta
   hash_ebml_marker_o,  // HashFunc
   cmp_ebml_marker_o,   // CmpFunc
   do_ref_c_            // DoRef
)

struct EbmlNaviCtx
{
   FILE* file;
   oEbmlMarkerStack markerStack;
   OEbmlDeclMap* declMap;
};
typedef struct EbmlNaviCtx EbmlNaviCtx;

void deinit_ctx( EbmlNaviCtx ctx[static 1], cErrorStack es[static 1] )
{
   if ( ctx->file != NULL ) close_file_c( ctx->file, es );

   if ( ctx->markerStack.v != NULL ) free_ebml_marker_stack_o( &(ctx->markerStack) );

   if ( ctx->declMap != NULL ) release_c( ctx->declMap );
}

bool init_ctx( EbmlNaviCtx ctx[static 1], cChars filePath, cErrorStack es[static 1] )
{
   *ctx = (EbmlNaviCtx){0};
   ctx->file = ropen_file_c( filePath, es );
   if ( ctx->file == NULL )
   {
      deinit_ctx( ctx, es );
      return false;
   }

   if ( not alloc_ebml_marker_stack_o( &(ctx->markerStack), 8 ) )
   {
      push_errno_error_c( es, ENOMEM );
      push_text_error_c_( es, "not able to allocate ctx.markerStack" );
      deinit_ctx( ctx, es );
      return false;
   }

   ctx->declMap = new_ebml_decl_map_o();
   if ( ctx->declMap == NULL )
   {
      push_errno_error_c( es, ENOMEM );
      push_text_error_c_( es, "not able to allocate ctx.declMap" );
      deinit_ctx( ctx, es );
      return false;
   }

   oVarEbmlDeclSlice declBuf = structs_c_( 300, oEbmlDecl );
   fill_ebml_decl_map_o( ctx->declMap, get_ebml_header_decl_o( declBuf ) );
   fill_ebml_decl_map_o( ctx->declMap, get_ebml_mkv_decl( declBuf ) );

   return true;
}

#endif