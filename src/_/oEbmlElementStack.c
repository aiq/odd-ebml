#include "_/oEbmlElementStack.h"

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 stack
*******************************************************************************/

bool alloc_ebml_element_stack_o( oEbmlElementStack stack[static 1],
                                 int64_t size )
{
   stack->v = alloc_array_c_( size, oEbmlElement );
   if ( stack->v == NULL ) return false;

   stack->s = 0;
   stack->cap = size;

   return true;
}

bool realloc_ebml_element_stack_o( oEbmlElementStack stack[static 1],
                                   int64_t size )
{
   void* mem = realloc_array_c_( stack->v, size, oEbmlElement );
   if ( mem == NULL ) return false;

   stack->v = mem;
   stack->cap = size;

   return true;
}

void free_ebml_element_stack_o( oEbmlElementStack stack[static 1] )
{
   return free( stack->v );
}

bool push_ebml_element_o( oEbmlElementStack stack[static 1],
                          oEbmlElement elem )
{
   if ( stack->s == stack->cap )
   {
      int64_t newCap;
      if ( not imul64_c( stack->cap, 2, &newCap ) or
           not realloc_ebml_element_stack_o( stack, newCap ) )
      {
         return false;
      }
      stack->cap = newCap;
   }

   stack->v[ stack->s ] = elem;
   stack->s += 1;
   return true;
}

bool pop_ebml_element_o( oEbmlElementStack stack[static 1],
                         oEbmlElement elem[static 1] )
{
   if ( is_empty_c_( *stack ) ) return false;

   *elem = last_c_( *stack );
   stack->s -= 1;
   return true;
}

bool top_ebml_element_o( oEbmlElementStack stack[static 1],
                         oEbmlElement elem[static 1] )
{
   if ( is_empty_c_( *stack ) ) return false;

   *elem = last_c_( *stack );
   return true;
}