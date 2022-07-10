#include "_/misc.h"

extern inline int64_t vint_scan_size_o( cByte first, cBytes checkBytes );

extern inline cBytes vint_fread_o( FILE* f,
                                   cVarBytes buf,
                                   cBytes checkBytes,
                                   cErrorStack es[static 1] );