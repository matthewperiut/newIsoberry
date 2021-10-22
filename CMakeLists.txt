cmake_minimum_required(VERSION 3.19)
set(CMAKE_CXX_STANDARD 20)

project(Isoberry)

# CMAKE extensions
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# sudo dnf groupinstall "Development Tools" "Development Libraries"
# sudo dnf install glew-devel SDL2-devel SDL2_image-devel glm-devel freetype-devel g++ enet-devel.x86_64 gtk3-devel
set(CMAKE_CXX_STANDARD 20)
set(ISOBERRY_VERSION 0.1)

if(${CMAKE_SYSTEM} MATCHES "Linux")
    set(LINUX 1)
endif(${CMAKE_SYSTEM} MATCHES "Linux")

file (GLOB MY_SRC
        "main.cpp"
        "game/tools/settings/*.cpp"
        "game/tools/asset/*.cpp"
        "game/external/png/*.cpp"
        "game/network/*.cpp"
        "game/physics/*.cpp"
        "game/sound/*.cpp"
        "game/file/*.cpp"
        "game/*.cpp")

if (WIN32)
    add_executable(Isoberry WIN32 ${MY_SRC} "${CMAKE_CURRENT_SOURCE_DIR}/game/icon/isoberry.rc")
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/game/icon/isoberry.ico DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/game/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)
elseif(LINUX)
    add_executable(Isoberry ${MY_SRC})
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/game/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/assets/)
endif()

if (APPLE)
    add_compile_definitions(GL_SILENCE_DEPRECATION)
    add_compile_options(-stdlib=libc++)

    set(CUR_TARGET Isoberry)
    set(MACOSX_BUNDLE_ICON_FILE isoberry.icns)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/game/assets/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Isoberry.app/Contents/assets)

    set(myApp_ICON ${CMAKE_CURRENT_SOURCE_DIR}/game/icon/isoberry.icns)
    set_source_files_properties(${myApp_ICON} PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources")

    add_executable(${CUR_TARGET} MACOSX_BUNDLE ${MY_SRC} ${myApp_ICON})
    set_target_properties(${CUR_TARGET} PROPERTIES
            BUNDLE True
            MACOSX_BUNDLE_GUI_IDENTIFIER my.domain.style.identifier.${CUR_TARGET}
            MACOSX_BUNDLE_BUNDLE_NAME ${CUR_TARGET}
            MACOSX_BUNDLE_BUNDLE_VERSION ${ISOBERRY_VERSION}
            MACOSX_BUNDLE_SHORT_VERSION_STRING ${ISOBERRY_VERSION}
            )
endif(APPLE)

# yojimbo
file(COPY game/external/assistance/yojimbo/CMakeLists.txt DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/game/external/yojimbo)

# Set VCPKG_ROOT
# (UNIX)    vcpkg install libsodium mbedtls
# (WINDOWS) vcpkg install libsodium:x64-windows-static mbedtls:x64-windows-static
if(WIN32)
    SET(VCPKG_ROOT "C:/vcpkg")
elseif(APPLE)
    SET(VCPKG_ROOT "/opt/homebrew/Cellar/vcpkg/2021.05.12/libexec")
elseif(UNIX)
    SET(VCPKG_ROOT "/home/matthewperiut/Downloads/vcpkg-2021.05.12")
endif()

add_subdirectory(game/external/yojimbo EXCLUDE_FROM_ALL)
target_link_libraries(Isoberry PRIVATE yojimbo)

add_subdirectory(game/external/openal-soft EXCLUDE_FROM_ALL)
target_link_libraries(Isoberry PRIVATE OpenAL)

if (UNIX)
    # X11
    if(LINUX)
        find_package(X11 REQUIRED)
        include_directories(${X11_INCLUDE_DIR})
        link_directories(${X11_LIBRARIES})
        target_link_libraries(Isoberry PRIVATE ${X11_LIBRARIES})
    endif(LINUX)
    # GLUT
    if(APPLE)
        find_package(GLUT REQUIRED)
        include_directories(${GLUT_INCLUDE_DIR})
        link_directories(${GLUT_LIBRARIES})
        target_link_libraries(Isoberry PRIVATE ${GLUT_LIBRARIES})
    endif(APPLE)

    find_package(OpenGL REQUIRED)
    include_directories(${OPENGL_INCLUDE_DIR})
    link_directories(${OPENGL_LIBRARIES})
    target_link_libraries(Isoberry PRIVATE ${OPENGL_LIBRARIES})

    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(Isoberry PRIVATE Threads::Threads)
endif (UNIX)