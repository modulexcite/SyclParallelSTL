cmake_minimum_required (VERSION 2.8.12.2)
project (SyclSTL)

if(HEADER_ONLY)
  message(WARNING "The SYCL implementation is header-only")
else(HEADER_ONLY)
  #####  Find the SYCL implementation

  find_library(SYCL_LIBRARY
    NAMES SYCL SYCL_d
    HINTS ${SYCL_PATH}
    PATH_SUFFIXES lib 
    )

  find_library(OPENCL_LIBRARY
    NAMES OpenCL 
    HINTS ${OPENCL_ROOT_DIR}
    PATH_SUFFIXES lib lib64 
    )

  if(NOT DEFINED OPENCL_LIBRARY)
    message(FATAL_ERROR "OpenCL library is not defined")
  endif()

  message(STATUS "${SYCL_LIBRARY}")
  if (${SYCL_LIBRARY} MATCHES "NOTFOUND")
    message(FATAL_ERROR "Cannot find SYCL implementation (${SYCL_PATH})")
  else()
    message(STATUS "The path to SYCL is: ${SYCL_PATH}")
  endif()

  set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SYCL_PATH}/cmake/Modules/")


  set(DEVICE_COMPILER_PATH "${SYCL_PATH}/bin/")
  set(DEVICE_COMPILER_INCLUDE_PATH "${SYCL_PATH}/include/device_compiler")
  set(RUNTIME_INCLUDES "${SYCL_PATH}/include")

  if (UNIX)
      # TODO(Ruyman) Figure out the linux distribution
      # Fix for device compiler not finding specific C++ headers with Ubuntu
      set(CMAKE_INCLUDE_PATH "${CMAKE_INCLUDE_PATH}" 
                         "/usr/include/c++/4.8.2/" 
                          "/usr/include/x86_64-linux-gnu/c++/4.8/")
  endif()

  if (NOT DEFINED DEVICE_COMPILER_NAME)
    if (WIN32)
      set(DEVICE_COMPILER_NAME "compute++.exe")
    else(WIN32)
      set(DEVICE_COMPILER_NAME "compute++")
    endif(WIN32)
  endif (NOT DEFINED DEVICE_COMPILER_NAME)
  set(DEVICE_COMPILER "${DEVICE_COMPILER_PATH}/${DEVICE_COMPILER_NAME}" 
    CACHE FILEPATH "device compiler")
  add_custom_target(compiler)

  include(${SYCL_PATH}/cmake/common.cmake)

  add_library(SYCL_LIBRARY SHARED IMPORTED)
  add_library(OPENCL_LIBRARY SHARED IMPORTED)

endif(HEADER_ONLY)

include_directories("${SYCL_PATH}/include")
include_directories("${SYCL_PATH}/include/image_library")



# Build the parallel stl

include_directories("include")

add_subdirectory (src)
add_subdirectory (examples)
add_subdirectory (tests)


