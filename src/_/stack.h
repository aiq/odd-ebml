#ifndef ODDEBML_INTERN_STACK_H
#define ODDEBML_INTERN_STACK_H

#include "clingo/lang/math.h"
#include "clingo/lang/mem.h"
#include "clingo/lang/slice.h"

/*******************************************************************************
******************************************************** Code Generation Macros 
********************************************************************************
 init
*******************************************************************************/

#define ALLOC_STACK_O_( FuncName, StackType, Type )                            \
bool FuncName( StackType stack[static 1], int64_t size )                       \
{                                                                              \
   stack->v = alloc_array_c_( size, Type );                                    \
   if ( stack->v == NULL ) return false;                                       \
                                                                               \
   stack->s = 0;                                                               \
   stack->cap = size;                                                          \
                                                                               \
   return true;                                                                \
}

#define REALLOC_STACK_O_( FuncName, StackType, Type )                          \
bool FuncName( StackType stack[static 1], int64_t size )                       \
{                                                                              \
   void* mem = realloc_array_c_( stack->v, size, Type );                       \
   if ( mem == NULL ) return false;                                            \
                                                                               \
   stack->v = mem;                                                             \
   stack->cap = size;                                                          \
                                                                               \
   return true;                                                                \
}

#define FREE_STACK_O_( FuncName, StackType )                                   \
void FuncName( StackType stack[static 1] )                                     \
{                                                                              \
   return free( stack->v );                                                    \
}

#define PUSH_STACK_O_( FuncName, StackType, Type, ReallocFunc )                \
bool FuncName( StackType stack[static 1], Type val )                           \
{                                                                              \
   if ( stack->s == stack->cap )                                               \
   {                                                                           \
      if ( stack->cap == 0 )                                                   \
      {                                                                        \
         stack->cap = 4;                                                       \
      }                                                                        \
      int64_t newCap;                                                          \
      if ( not imul64_c( stack->cap, 2, &newCap ) or                           \
           not ReallocFunc( stack, newCap ) )                                  \
      {                                                                        \
         return false;                                                         \
      }                                                                        \
      stack->cap = newCap;                                                     \
   }                                                                           \
   stack->v[ stack->s ] = val;                                                 \
   stack->s += 1;                                                              \
   return true;                                                                \
}

#define POP_STACK_O_( FuncName, StackType, Type )                              \
bool FuncName( StackType stack[static 1], Type val[static 1] )                 \
{                                                                              \
   if ( is_empty_c_( *stack ) ) return false;                                  \
                                                                               \
   *val = last_c_( *stack );                                                   \
   stack->s -= 1;                                                              \
   return true;                                                                \
}

#define TOP_STACK_O_( FuncName, StackType, Type )                              \
bool FuncName( StackType stack[static 1], Type val[static 1] )                 \
{                                                                              \
   if ( is_empty_c_( *stack ) ) return false;                                  \
                                                                               \
   *val = last_c_( *stack );                                                   \
   return true;                                                                \
}

/*******************************************************************************
 type
*******************************************************************************/

#define STACK_DEF_C_( Type, StackType, FuncSuffix, StackFuncSuffix )           \
struct StackType                                                               \
{                                                                              \
   int64_t s;                                                                  \
   Type* v;                                                                    \
   int64_t cap;                                                                \
};                                                                             \
typedef struct StackType StackType;                                            \
                                                                               \
bool alloc_##StackFuncSuffix( StackType stack[static 1], int64_t size );       \
bool realloc_##StackFuncSuffix( StackType stack[static 1], int64_t size );     \
void free_##StackFuncSuffix( StackType stack[static 1] );                      \
bool push_##FuncSuffix( StackType stack[static 1], Type val );                 \
bool pop_##FuncSuffix( StackType stack[static 1], Type val[static 1] );        \
bool top_##FuncSuffix( StackType stack[static 1], Type val[static 1] );

/**********************************************************/

#define STACK_IMPL_C_( Type, StackType, FuncSuffix, StackFuncSuffix )          \
ALLOC_STACK_O_( alloc_##StackFuncSuffix, StackType, Type )                     \
REALLOC_STACK_O_( realloc_##StackFuncSuffix, StackType, Type )                 \
FREE_STACK_O_( free_##StackFuncSuffix, StackType )                             \
PUSH_STACK_O_( push_##FuncSuffix, StackType, Type, realloc_##StackFuncSuffix ) \
POP_STACK_O_( pop_##FuncSuffix, StackType, Type )                              \
TOP_STACK_O_( top_##FuncSuffix, StackType, Type )

/*******************************************************************************

*******************************************************************************/

#endif