find_path(AALIB_INCLUDE_DIR NAMES aalib.h)

find_library(AALIB_LIBRARY NAMES aa)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(AALIB AALIB_INCLUDE_DIR AALIB_LIBRARY)

if(AALIB_FOUND AND NOT TARGET aa::aa)
    add_library(aa::aa UNKNOWN IMPORTED)
    set_target_properties(aa::aa PROPERTIES
        IMPORTED_LINK_INTERFACE_LANGUAGES "C"
        IMPORTED_LOCATION "${AALIB_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${AALIB_INCLUDE_DIR}")
endif()

mark_as_advanced(AALIB_INCLUDE_DIR AALIB_LIBRARY)
