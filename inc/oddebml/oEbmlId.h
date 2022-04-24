#ifndef ODDEBML_EBML_ID_H
#define ODDEBML_EBML_ID_H

#include <clingo/io/cRecorder.h>
#include <clingo/io/cScanner.h>

struct oEbmlId {
    uint32_t _v;
}
typedef struct oEbmlId oEbmlId;

struct oEbmlIdInfo {
    uint8_t length;
    uint32_t value;
}

typedef struct oEbmlIdInfo oEbmlIdInfo;

bool possible_ebml_id_o( uint32_t val );

#endif