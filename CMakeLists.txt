cmake_minimum_required(VERSION 3.3 FATAL_ERROR)
project(JahMiner)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt5 REQUIRED COMPONENTS Widgets Network)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

## OPENCL
        find_path(OpenCL_INCLUDE_DIR
        NAMES
            CL/cl.h
            OpenCL/cl.h
        NO_DEFAULT_PATH
        PATHS
            ENV "OpenCL_ROOT"
            ENV AMDAPPSDKROOT
            ENV ATISTREAMSDKROOT
            ENV "PROGRAMFILES(X86)"
            /usr
        PATH_SUFFIXES
            include
            OpenCL/common/inc
            "AMD APP/include")

    find_library(OpenCL_LIBRARY
        NAMES
            OpenCL
            OpenCL.lib
        NO_DEFAULT_PATH
        PATHS
            ENV "OpenCL_ROOT"
            ENV AMDAPPSDKROOT
            ENV ATISTREAMSDKROOT
            ENV "PROGRAMFILES(X86)"
        PATH_SUFFIXES
            "AMD APP/lib/x86_64"
            lib/x86_64
            lib/x86_64-linux-gnu
            lib/x64
            OpenCL/common/lib/x64)
    # find package will use the previews searched path variables
    find_package(OpenCL)
    if(OpenCL_FOUND)
        include_directories(SYSTEM ${OpenCL_INCLUDE_DIRS})
        set(LIBS ${LIBS} ${OpenCL_LIBRARY})
        link_directories(${OpenCL_LIBRARY})
                #target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCL_LIBRARY} )
    else()
        message(FATAL_ERROR "OpenCL NOT found: use `-DOpenCL_ENABLE=OFF` to build without OpenCL support for AMD gpu's")
    endif()

# This will allow a .lib to be built alongside the dll, ((needed)) for MSVC
if(WIN32 AND MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
    set(USE_MSVC_RUNTIME_LIBRARY_DLL 1)
endif()

option (BUILD_MINER_AS_LIB "if the miner is in jahshaka")
if(BUILD_MINER_AS_LIB)
    set(HEADERS
        autominer.h
        cuda_gpu_list.h
        minerchart.h
        minerui.h
         minerprocess.h
        ../../src/misc/QtAwesome.h
        ../../src/misc/QtAwesomeAnim.h
        ../../src/subclass/switch.h
        ../../src/constants.h
        ../../src/core/settingsmanager.h
         )
    add_library(JahMiner
        main.cpp
        autominer.cpp
        cuda_gpu_list.cu
        minerchart.cpp
        minerui.cpp
        minerprocess.cpp
        ../../src/misc/QtAwesome.cpp
        ../../src/misc/QtAwesomeAnim.cpp
        ../../src/subclass/switch.cpp
        ../../src/constants.cpp
        ../../src/core/settingsmanager.cpp
        ${HEADERS_moc})
else()
    qt5_add_resources(QRCS
    ${CMAKE_SOURCE_DIR}/fonts.qrc
)
    set(HEADERS autominer.h constants.h cuda_gpu_list.h graphicscard.h minerchart.h minerui.h qtawesome.h qtawesomeanim.h settingsmanager.h minerprocess.h)
    add_executable(JahMiner WIN32 ${QRCS} main.cpp autominer.cpp constants.cpp cuda_gpu_list.cu graphicscard.cpp minerchart.cpp minerui.cpp qtawesome.cpp qtawesomeanim.cpp settingsmanager.cpp minerprocess.cpp  ${HEADERS_moc})

    if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL Release)
        set(CMAKE_WIN32_EXECUTABLE ON)
    endif()
endif(BUILD_MINER_AS_LIB)

set (MINER_ENABLED OFF CACHE BOOL "Enable Mining (OpenCL required)")
set (MINER_MHTTPD_LIB "NONE" CACHE BOOL "path to libmicrohttpd .lib file")
set (MINER_MHTTPD_INCLUDE "NONE" CACHE BOOL "path to libmicrohttpd ")

    #XMR-STAK
    set(OpenSSL_ENABLE OFF)
    set(HWLOC_ENABLE OFF)
    set(CUDA_ENABLE OFF)
   # add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/xmr-stak)
   # set_target_properties(xmr-stak PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/xmr-stak)
   # set_target_properties(xmr-stak PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/xmr-stak)
   # set_target_properties(xmr-stak PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/xmr-stak)
   # set_target_properties(xmr-stak PROPERTIES OpenSSL_ENABLE OFF)
   # set_target_properties(xmr-stak PROPERTIES HWLOC_ENABLE OFF)
   # set_target_properties(xmr-stak PROPERTIES CUDA_ENABLE OFF)


if(BUILD_MINER_AS_LIB)
add_definitions("-DBUILD_AS_LIB")
endif(BUILD_MINER_AS_LIB)


if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Disable compiler specific warnings if we are building with MSVC
# NOMINMAX - http://www.suodenjoki.dk/us/archive/2010/min-max.htm
if(MSVC)
    add_definitions("-D_CRT_SECURE_NO_WARNINGS" "-DNOMINMAX")
    # Disable ZERO_CHECK if need be
    # set(CMAKE_SUPPRESS_REGENERATION true)
endif()

  #  qt5_wrap_cpp(HEADERS_moc autominer.h constants.h cuda_gpu_list.h minerchart.h minerui.h qtawesome.h qtawesomeanim.h switch.h settingsmanager.h minerprocess.h)

target_link_libraries(JahMiner Qt5::Widgets Qt5::Network)
target_link_libraries(JahMiner ${LIBS})
target_compile_options(JahMiner PUBLIC)

if (WIN32)
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
    set(QT5_WINDEPLOYQT_EXECUTABLE "${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")

    add_custom_command(TARGET JahMiner POST_BUILD
        COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE_DIR:JahMiner>)
endif(WIN32)
