cmake_minimum_required(VERSION 3.12)

project(ICE4131-202021-Assignment)


# JPEG ########################################################################
FIND_PACKAGE(JPEG REQUIRED)
SET(requiredLibs ${requiredLibs} ${JPEG_LIBRARY})


# ASSIMP ######################################################################
OPTION(USE_SYSTEM_ASSIMP "Use system library" OFF)

# Use system library
IF (USE_SYSTEM_ASSIMP)
    FIND_PACKAGE( assimp )
ENDIF (USE_SYSTEM_ASSIMP)

# The system library was not found
# Build ASSIMP instead
IF (NOT assimp_FOUND OR NOT USE_SYSTEM_ASSIMP)
    MESSAGE (STATUS "Build ASSIMP")
    SET (USE_SYSTEM_ASSIMP OFF)
    include(ExternalProject)
    INCLUDE(BuildASSIMP.cmake)
    build_assimp( assimp ${PROJECT_BINARY_DIR} )
ENDIF (NOT assimp_FOUND OR NOT USE_SYSTEM_ASSIMP)


# ZLIB ######################################################################
FIND_PACKAGE( ZLIB REQUIRED )
SET(requiredLibs ${requiredLibs} ${ZLIB_LIBRARY})

# OpenMP ####################################################################
find_package(OpenMP)

# Build RayTracing library ##################################################
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

TARGET_INCLUDE_DIRECTORIES(RayTracing PRIVATE ${JPEG_INCLUDE_DIR})
TARGET_INCLUDE_DIRECTORIES(RayTracing PUBLIC ${ASSIMP_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(RayTracing PRIVATE ${ZLIB_INCLUDE_DIRS})
TARGET_INCLUDE_DIRECTORIES(RayTracing PUBLIC include)

TARGET_LINK_LIBRARIES (RayTracing ${requiredLibs} ${optionalLibs})


# Program ###############################################################
add_executable(main src/main.cxx)
TARGET_LINK_LIBRARIES (main PUBLIC RayTracing ${ASSIMP_LIBRARY})
if(OpenMP_CXX_FOUND)
    TARGET_LINK_LIBRARIES(main PUBLIC OpenMP::OpenMP_CXX)
endif()

FILE(COPY cloud2.jpg DESTINATION ${CMAKE_BINARY_DIR})
#FILE(COPY Bangor_Logo_A1.jpg DESTINATION ${CMAKE_BINARY_DIR})
FILE(COPY dragon.ply DESTINATION ${CMAKE_BINARY_DIR})

