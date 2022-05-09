#ifndef ODDEBML_EBML_DATE_H
#define ODDEBML_EBML_DATE_H

#include "clingo/time/cTime.h"
#include "oddebml/apidecl.h"

struct oEbmlDate {
    int64_t _v;
};
typedef struct oEbmlDate oEbmlDate;

ODDEBML_API oEbmlDate ebml_date_o( cDate d, cDaytime dt, cTzOffset tz );

ODDEBML_API cTime ebml_date_as_time_o( oEbmlDate ed );
ODDEBML_API cTimestamp ebml_date_as_timestamp_o( oEbmlDate ed );

ODDEBML_API oEbmlDate ebml_date_from_time_o( cTime t );
ODDEBML_API oEbmlDate ebml_date_from_timestamp_o( cTimestamp ts );

#endif