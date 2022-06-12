#include "_/oEbmlMarker.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 generated
*******************************************************************************/

SLICE_IMPL_C_(
   oEbmlMarker,            // Type
   oEbmlMarkerSlice,       // SliceType
   ebml_marker_slice_o,    // FuncName
   oVarEbmlMarkerSlice,    // VarSliceType
   var_ebml_marker_slice_o // VarFuncName
)

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 init
*******************************************************************************/

oEbmlMarker ebml_marker_o( oEbmlId id, int64_t pos )
{
   return (oEbmlMarker){ .id=id, .pos=pos };
}

/*******************************************************************************
 stack
*******************************************************************************/

bool alloc_ebml_marker_stack_o( oEbmlMarkerStack stack[static 1], int64_t size )
{
   stack->v = alloc_c( size );
   if ( stack->v == NULL ) return false;

   stack->s = 0;
   stack->cap = size;

   return true;
}

bool realloc_ebml_marker_stack_o( oEbmlMarkerStack stack[static 1], int64_t size )
{
   void* mem = realloc_c( stack->v, size );
   if ( mem == NULL ) return false;

   stack->v = mem;
   stack->cap = size;

   return true;
}

void free_ebml_marker_stack_o( oEbmlMarkerStack stack[static 1] )
{
   return free( stack->v );
}

bool push_ebml_marker_o( oEbmlMarkerStack stack[static 1], oEbmlMarker marker )
{
   if ( stack->s == stack->cap )
   {
      int64_t newCap;
      if ( not imul64_c( stack->cap, 2, &newCap ) or
           not realloc_ebml_marker_stack_o( stack, newCap ) )
      {
         return false;
      }
      stack->cap = newCap;
   }

   stack->v[ stack->s ] = marker;
   stack->s += 1;
   return true;
}

bool pop_ebml_marker_o( oEbmlMarkerStack stack[static 1],
                        oEbmlMarker marker[static 1] )
{
   if ( is_empty_c_( *stack ) ) return false;

   *marker = last_c_( *stack );
   stack->s -= 1;
   return true;
}