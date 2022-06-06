################################################################################
# INC_FILES
################################################################################
set( INC_FILES
   ${INC_DIR}/oddebml/apidecl.h
   ${INC_DIR}/oddebml/version.h

   ${INC_DIR}/oddebml/oEbmlDate.h
   ${INC_DIR}/oddebml/oEbmlId.h
   ${INC_DIR}/oddebml/oEbmlSize.h
)

################################################################################
# SRC_FILES
################################################################################
set( SRC_FILES
   ${SRC_DIR}/oddebml/oEbmlDate.c
   ${SRC_DIR}/oddebml/oEbmlId.c
   ${SRC_DIR}/oddebml/oEbmlSize.c
)

################################################################################
# TEST_FILES
################################################################################
set( TEST_FILES
   # oEbmlDate
   ${TEST_DIR}/oddebml/oEbmlDate/as_ebml_date.c
   # oEbmlId
   ${TEST_DIR}/oddebml/oEbmlId/decode_ebml_id.c
   ${TEST_DIR}/oddebml/oEbmlId/ebml_id_is_valid.c
   ${TEST_DIR}/oddebml/oEbmlId/ebml_id_length.c
   ${TEST_DIR}/oddebml/oEbmlId/encode_ebml_id.c
   ${TEST_DIR}/oddebml/oEbmlId/record_ebml_id.c
   ${TEST_DIR}/oddebml/oEbmlId/scan_ebml_id.c
   # oEbmlSize
   ${TEST_DIR}/oddebml/oEbmlSize/decode_ebml_size.c
   ${TEST_DIR}/oddebml/oEbmlSize/ebml_size_is_unknown.c
   ${TEST_DIR}/oddebml/oEbmlSize/ebml_size_length.c
   ${TEST_DIR}/oddebml/oEbmlSize/encode_ebml_size.c
   ${TEST_DIR}/oddebml/oEbmlSize/record_ebml_size.c
   ${TEST_DIR}/oddebml/oEbmlSize/scan_ebml_size.c
)
