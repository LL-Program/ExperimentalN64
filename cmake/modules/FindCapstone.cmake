
FIND_PATH(
        Capstone_INCLUDE_DIRS
        NAMES
        capstone/capstone.h
        HINTS
        ${Capstone_ROOT_DIR}
        PATH_SUFFIXES
        include/
)

FIND_LIBRARY(Capstone_LIBRARIES
        NAMES
        libcapstone.a
        capstone
        capstone_dll
        HINTS
        ${Capstone_ROOT_DIR}
        PATH_SUFFIXES
        lib
        )

INCLUDE(FindPackageHandleStandardArgs)

IF(Capstone_INCLUDE_DIRS AND Capstone_LIBRARIES)
    SET(Capstone_FOUND TRUE)
    FIND_PACKAGE_HANDLE_STANDARD_ARGS(
            Capstone
            DEFAULT_MSG
            Capstone_INCLUDE_DIRS
            Capstone_LIBRARIES
    )
    ADD_LIBRARY(Capstone::Capstone INTERFACE IMPORTED)
    SET_TARGET_PROPERTIES(Capstone::Capstone PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES ${Capstone_INCLUDE_DIRS}
            INTERFACE_LINK_LIBRARIES ${Capstone_LIBRARIES}
            )
ENDIF()

MARK_AS_ADVANCED(
        Capstone_INCLUDE_DIR
        Capstone_LIBRARY
)