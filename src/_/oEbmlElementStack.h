#ifndef ODDEBML_INTERN_EBML_ELEMENT_STACK_H
#define ODDEBML_INTERN_EBML_ELEMENT_STACK_H

#include "oddebml/apidecl.h"
#include "oddebml/oEbmlElement.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

struct oEbmlElementStack {
   int64_t s;
   oEbmlElement* v;
   int64_t cap;
};
typedef struct oEbmlElementStack oEbmlElementStack;

/*******************************************************************************
********************************************************************* Functions
********************************************************************************
 stack
*******************************************************************************/

bool alloc_ebml_element_stack_o( oEbmlElementStack stack[static 1],
                                 int64_t size );

bool realloc_ebml_element_stack_o( oEbmlElementStack stack[static 1],
                                   int64_t size );

void free_ebml_element_stack_o( oEbmlElementStack stack[static 1] );

bool push_ebml_element_o( oEbmlElementStack stack[static 1],
                          oEbmlElement elem );

bool pop_ebml_element_o( oEbmlElementStack stack[static 1],
                         oEbmlElement elem[static 1] );

bool top_ebml_element_o( oEbmlElementStack stack[static 1],
                         oEbmlElement elem[static 1] );

#endif