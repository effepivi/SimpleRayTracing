cmake_minimum_required(VERSION 2.6)

project(ICP3038--Lab01)

include_directories(include)

add_library(RayTracing
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


add_executable(main src/main.cxx)
TARGET_LINK_LIBRARIES (main RayTracing)
