#ifndef ODDEBML_INTERN_EBML_ELEMENT_STACK_H
#define ODDEBML_INTERN_EBML_ELEMENT_STACK_H

#include "oddebml/apidecl.h"
#include "oddebml/oEbmlElement.h"
#include "_/stack.h"

/*******************************************************************************
********************************************************* Types and Definitions
********************************************************************************
 
*******************************************************************************/

STACK_DEF_C_(
   oEbmlElement,        // Type
   oEbmlElementStack,   // StackType
   ebml_element_o,      // FuncSuffix
   ebml_element_stack_o // StackFuncSuffix
)

#endif