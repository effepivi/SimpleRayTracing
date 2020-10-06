cmake_minimum_required(VERSION 2.6)

project(ICE4131-202021-Assignment)

include_directories(include)

# JPEG ########################################################################
FIND_PACKAGE(JPEG REQUIRED)
IF(JPEG_FOUND)
    INCLUDE_DIRECTORIES(${JPEG_INCLUDE_DIR})
    LINK_DIRECTORIES(${JPEG_LIBRARY_DIR})
    SET(requiredLibs ${requiredLibs} ${JPEG_LIBRARY})
ELSE(JPEG_FOUND)
    MESSAGE(FATAL_ERROR "JPEG not found.")
ENDIF(JPEG_FOUND)


add_library(RayTracing
  include/Image.h
  include/Image.inl
  src/Image.cxx
  include/Ray.h
  include/Ray.inl
  src/Ray.cxx
  include/Triangle.h
  include/Triangle.inl
  src/Triangle.cxx
  include/TriangleMesh.h
  include/TriangleMesh.inl
  src/TriangleMesh.cxx
  include/Vec3.h
  include/Vec3.inl
)

TARGET_LINK_LIBRARIES (RayTracing ${requiredLibs} ${optionalLibs})


add_executable(main src/main.cxx)
TARGET_LINK_LIBRARIES (main RayTracing ${requiredLibs})
