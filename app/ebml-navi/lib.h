#ifndef EBML_NAVI_LIB_H
#define EBML_NAVI_LIB_H

#include "clingo/io/print.h"

#define eprint_( ... )                                                         \
   println_c_(__VA_ARGS__) and false

#define failln_( ... )                                                         \
   println_c_(__VA_ARGS__) ? EXIT_FAILURE : EXIT_FAILURE

#endif