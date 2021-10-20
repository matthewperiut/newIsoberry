cmake_minimum_required(VERSION 3.16)

include(FetchContent)

MESSAGE(STATUS "***")
MESSAGE(STATUS "***  Yojimbo -- START --")
MESSAGE(STATUS "***")

#############################################################
## Project Definition
#############################################################
project(Yojimbo C CXX)

############################################################
## Settings
############################################################

## Where to install yojimbo
#SET(YOJIMBO_INSTALL_DIR "${CMAKE_CURRENT_LIST_DIR}/install/${CMAKE_BUILD_TYPE}")
## Want Tests?
#SET(YOJIMBO_TESTS TRUE )
## Where to put the .git clone
#SET( YOJIMBO_SOURCE_DIR     "${CMAKE_CURRENT_LIST_DIR}/download/yojimbo"                   )
## Git tag to check out.
## Can be a branch ("master"), tag ("v1.2.1") or commit hash ("af30b7c3ab3329e69d0c5cfe22b7644a13e7c838")
#SET( YOJIMBO_TAG "master")
## Root of your vcpkg installation
# SET(VCPKG_ROOT "F:/vcpkg")

############################################################
## Derived Settings
############################################################
##
if(NOT DEFINED YOJIMBO_INSTALL_DIR)
    SET(YOJIMBO_INSTALL_DIR ${CMAKE_INSTALL_PREFIX} )
endif()

if(NOT DEFINED YOJIMBO_TESTS)
    SET(YOJIMBO_TESTS FALSE)
endif()

if(NOT DEFINED YOJIMBO_SOURCE_DIR)
    SET(YOJIMBO_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/download/yojimbo")
endif()

if(NOT DEFINED YOJIMBO_TAG)
    SET(YOJIMBO_TAG "master")
endif()

if(NOT DEFINED VCPKG_ROOT)
    MESSAGE(      "Cannot proceed without VCPKG_ROOT being defined. Please correct your settings.")
    MESSAGE(FATAL "You can get vcpkg from https://github.com/Microsoft/vcpkg")
endif()

## Debug output
MESSAGE("YOJIMBO_INSTALL_DIR = " ${YOJIMBO_INSTALL_DIR})
MESSAGE("YOJIMBO_TESTS       = " ${YOJIMBO_TESTS})
MESSAGE("YOJIMBO_SOURCE_DIR  = " ${YOJIMBO_SOURCE_DIR})
MESSAGE("YOJIMBO_TAG         = " ${YOJIMBO_TAG})
MESSAGE("VCPKG_ROOT          = " ${VCPKG_ROOT})


#############################################################
## Fetch Yojimbo
#############################################################
##
FetchContent_Declare( YojimboGit )
FetchContent_Populate(YojimboGit
        SOURCE_DIR     ${YOJIMBO_SOURCE_DIR}
        GIT_REPOSITORY "https://github.com/networkprotocol/yojimbo.git"
        GIT_TAG        ${YOJIMBO_TAG}
        )

############################################################
## External imports: libsodium and mbedtls
############################################################
##
## We require an installation of VCPKG here and VCPKG_ROOT set to the installation folder
## The dependecies are installed with vcpkg as follows (Windows x64):
## cd ${VCPKG_ROOT}
## vcpkg install libsodium:x64-windows-static
## vcpkg install mbedtls:x64-windows-static
## On Linux the triplet distinction between static and dynamic libraries is not existent

# External library paths
if(WIN32)
    SET(VCPKG_LIBSODIUM_BASE "${VCPKG_ROOT}/packages/libsodium_x64-windows-static" )
    SET(VCPKG_MBEDTLS_BASE   "${VCPKG_ROOT}/packages/mbedtls_x64-windows-static" )
elseif(APPLE)
    if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
        SET(VCPKG_LIBSODIUM_BASE "${VCPKG_ROOT}/installed/arm64-osx")
        SET(VCPKG_MBEDTLS_BASE "${VCPKG_ROOT}/installed/arm64-osx")
    elseif(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64")
        SET(VCPKG_LIBSODIUM_BASE "${VCPKG_ROOT}/installed/x64-osx")
        SET(VCPKG_MBEDTLS_BASE "${VCPKG_ROOT}/installed/x64-osx")
    endif()
elseif(UNIX)
    SET(VCPKG_LIBSODIUM_BASE "${VCPKG_ROOT}/installed/x64-linux")
    SET(VCPKG_MBEDTLS_BASE   "${VCPKG_ROOT}/installed/x64-linux")
else()
    MESSAGE(FATAL "Inrecognized Operating System. I understand either WIN32 or UNIX to be set to true.")
endif()

## External libraries and headers
add_library( sodium STATIC IMPORTED)
target_include_directories( sodium INTERFACE "${VCPKG_LIBSODIUM_BASE}/include"  )

add_library( mbedtls STATIC IMPORTED)
target_include_directories( mbedtls INTERFACE "${VCPKG_MBEDTLS_BASE}/include"  )

add_library( mbedx509 STATIC IMPORTED)
target_include_directories( mbedx509 INTERFACE "${VCPKG_MBEDTLS_BASE}/include"  )

add_library( mbedcrypto STATIC IMPORTED)
target_include_directories( mbedcrypto INTERFACE "${VCPKG_MBEDTLS_BASE}/include"  )

## External library binaries
if(WIN32)
    set_target_properties(sodium     PROPERTIES IMPORTED_LOCATION ${VCPKG_LIBSODIUM_BASE}/lib/libsodium.lib )
    set_target_properties(mbedtls    PROPERTIES IMPORTED_LOCATION ${VCPKG_MBEDTLS_BASE}/lib/mbedtls.lib     )
    set_target_properties(mbedx509   PROPERTIES IMPORTED_LOCATION ${VCPKG_MBEDTLS_BASE}/lib/mbedx509.lib    )
    set_target_properties(mbedcrypto PROPERTIES IMPORTED_LOCATION ${VCPKG_MBEDTLS_BASE}/lib/mbedcrypto.lib  )
ELSEIF(UNIX)
    set_target_properties(sodium     PROPERTIES IMPORTED_LOCATION ${VCPKG_LIBSODIUM_BASE}/lib/libsodium.a   )
    set_target_properties(mbedtls    PROPERTIES IMPORTED_LOCATION ${VCPKG_MBEDTLS_BASE}/lib/libmbedtls.a    )
    set_target_properties(mbedx509   PROPERTIES IMPORTED_LOCATION ${VCPKG_MBEDTLS_BASE}/lib/libmbedx509.a   )
    set_target_properties(mbedcrypto PROPERTIES IMPORTED_LOCATION ${VCPKG_MBEDTLS_BASE}/lib/libmbedcrypto.a )
ENDIF()



############################################################
## Yojimbo Static Library
############################################################
##
add_library(yojimbo STATIC
        ${YOJIMBO_SOURCE_DIR}/yojimbo.cpp
        ${YOJIMBO_SOURCE_DIR}/tlsf/tlsf.c
        ${YOJIMBO_SOURCE_DIR}/netcode.io/netcode.c
        ${YOJIMBO_SOURCE_DIR}/reliable.io/reliable.c
        )
target_link_libraries( yojimbo sodium mbedtls mbedx509 mbedcrypto )
target_compile_definitions( yojimbo PUBLIC NETCODE_ENABLE_TESTS=0 RELIABLE_ENABLE_TESTS=0 )
target_include_directories( yojimbo
        INTERFACE
        $<BUILD_INTERFACE:${YOJIMBO_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${YOJIMBO_INSTALL_DIR}/include>
        PRIVATE
        ${YOJIMBO_SOURCE_DIR}/netcode.io
        ${YOJIMBO_SOURCE_DIR}/reliable.io
        )

############################################################
## Yojimbo Static TEST Library and Test App
############################################################
##
if(${YOJIMBO_TESTS})
    ## library
    add_library(yojimbo_test STATIC
            ${YOJIMBO_SOURCE_DIR}/yojimbo.cpp
            ${YOJIMBO_SOURCE_DIR}/tlsf/tlsf.c
            ${YOJIMBO_SOURCE_DIR}/netcode.io/netcode.c
            ${YOJIMBO_SOURCE_DIR}/reliable.io/reliable.c
            )
    target_link_libraries( yojimbo_test sodium mbedtls mbedx509 mbedcrypto )
    target_compile_definitions( yojimbo_test PUBLIC NETCODE_ENABLE_TESTS=1 RELIABLE_ENABLE_TESTS=1 )
    target_include_directories( yojimbo_test
            INTERFACE
            $<BUILD_INTERFACE:${YOJIMBO_SOURCE_DIR}>
            $<INSTALL_INTERFACE:${YOJIMBO_INSTALL_DIR}/include>
            PRIVATE
            "${YOJIMBO_SOURCE_DIR}/netcode.io"
            "${YOJIMBO_SOURCE_DIR}/reliable.io"
            )

    target_include_directories( yojimbo PRIVATE "${VCPKG_LIBSODIUM_BASE}/include"  )
    target_include_directories( yojimbo PRIVATE "${VCPKG_MBEDTLS_BASE}/include"  )

    ## executable
    add_executable(testapp ${YOJIMBO_SOURCE_DIR}/test.cpp )
    target_link_libraries(testapp yojimbo_test)
    ##
endif()

############################################################
## Client App Target
############################################################
##
add_executable(client ${YOJIMBO_SOURCE_DIR}/client.cpp )
target_link_libraries( client yojimbo )

############################################################
## Server App Target
############################################################
##
add_executable(server ${YOJIMBO_SOURCE_DIR}/server.cpp )
target_link_libraries( server yojimbo )

############################################################
## Secure Client App Target
############################################################
##
add_executable(secure_client ${YOJIMBO_SOURCE_DIR}/secure_client.cpp )
target_link_libraries( secure_client yojimbo )

############################################################
## Secure Server App Target
############################################################
##
add_executable(secure_server ${YOJIMBO_SOURCE_DIR}/secure_server.cpp )
target_link_libraries( secure_server yojimbo )

############################################################
## Client Server App Target
############################################################
##
add_executable(client_server ${YOJIMBO_SOURCE_DIR}/client_server.cpp )
target_link_libraries( client_server yojimbo )

############################################################
## Loopback App Target
############################################################
##
add_executable(loopback ${YOJIMBO_SOURCE_DIR}/loopback.cpp )
target_link_libraries( loopback yojimbo )

############################################################
## Soak App Target
############################################################
##
add_executable(soak ${YOJIMBO_SOURCE_DIR}/soak.cpp )
target_link_libraries( soak yojimbo )

############################################################
## Install
############################################################
##
if(YOJIMBO_TESTS)
    SET(TEST_INSTALL testapp)
endif()

## yojimbo + EXPORT
install(
        TARGETS
        yojimbo
        EXPORT yojimboConfig
        RUNTIME  DESTINATION ${YOJIMBO_INSTALL_DIR}/bin
        LIBRARY  DESTINATION ${YOJIMBO_INSTALL_DIR}/lib
        ARCHIVE  DESTINATION ${YOJIMBO_INSTALL_DIR}/lib
        INCLUDES DESTINATION ${YOJIMBO_INSTALL_DIR}/include
)
## The rest
install(
        TARGETS
        ${TEST_INSTALL}
        client
        server
        secure_client
        secure_server
        client_server
        loopback
        soak
        RUNTIME  DESTINATION ${YOJIMBO_INSTALL_DIR}/bin
        LIBRARY  DESTINATION ${YOJIMBO_INSTALL_DIR}/lib
        ARCHIVE  DESTINATION ${YOJIMBO_INSTALL_DIR}/lib
        INCLUDES DESTINATION ${YOJIMBO_INSTALL_DIR}/include
)
install(  FILES   ${YOJIMBO_SOURCE_DIR}/yojimbo.h
        ${YOJIMBO_SOURCE_DIR}/shared.h
        DESTINATION
        ${YOJIMBO_INSTALL_DIR}/include
        )
## install cmake files for find_package
install(EXPORT yojimboConfig DESTINATION ${YOJIMBO_INSTALL_DIR}/lib/cmake  )

#### DONE ####


MESSAGE(STATUS "***")
MESSAGE(STATUS "***  Yojimbo -- DONE --")
MESSAGE(STATUS "***")
