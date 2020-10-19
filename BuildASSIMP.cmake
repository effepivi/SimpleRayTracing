macro(build_assimp install_prefix staging_prefix)


# make a custom ASSIMP configuration file

SET (ASSIMP_VERSION_STRING 5.0)
SET (ASSIMP_VERSION_MAJOR  5)
SET (ASSIMP_VERSION_MINOR  0)

set(CMAKE_OSX_EXTERNAL_PROJECT_ARGS)
if(APPLE)
  list(APPEND CMAKE_OSX_EXTERNAL_PROJECT_ARGS
    -DCMAKE_OSX_ARCHITECTURES=${CMAKE_OSX_ARCHITECTURES}
    -DCMAKE_OSX_SYSROOT=${CMAKE_OSX_SYSROOT}
    -DMACOSX_RPATH:BOOL=ON
    -DCMAKE_OSX_DEPLOYMENT_TARGET=${CMAKE_OSX_DEPLOYMENT_TARGET}
  )
endif()

SET (ASSIMP_INSTALL_DIR ${staging_prefix}/${install_prefix}-install)

ExternalProject_Add(assimp
  URL  "https://github.com/assimp/assimp/archive/v5.0.1.zip"
  URL_MD5 "11595546066ce52c0039818b8599f38b"
  UPDATE_COMMAND ""
  SOURCE_DIR  ${staging_prefix}/${install_prefix}-source
  BINARY_DIR  ${staging_prefix}/${install_prefix}-build
  INSTALL_DIR ${ASSIMP_INSTALL_DIR}
  LIST_SEPARATOR :::
  CMAKE_GENERATOR ${CMAKE_GEN}
  CMAKE_ARGS
      ${LOCAL_CMAKE_BUILD_OPTIONS}
      -DCMAKE_CXX_STANDARD=11
      -DCMAKE_CXX_STANDARD_REQUIRED=ON
      -DCMAKE_CXX_EXTENSIONS=OFF
      -DCMAKE_INSTALL_PREFIX:PATH=${ASSIMP_INSTALL_DIR}
      -DASSIMP_BUILD_TESTS:BOOL=OFF
      -DBUILD_SHARED_LIBS:BOOL=OFF
      -DBUILD_TESTING:BOOL=OFF
      -DASSIMP_BUILD_ASSIMP_TOOLS:BOOL=OFF
      -DASSIMP_BUILD_DOCBOOK_MANPAGES:BOOL=OFF
)

SET(ASSIMP_ROOT_DIR      ${ASSIMP_INSTALL_DIR}          CACHE PATH "Where ASSIMP is."   FORCE)
SET(ASSIMP_INCLUDE_DIRS  ${ASSIMP_INSTALL_DIR}/include/ CACHE PATH "Where ASSIMP's headers are."   FORCE)
SET(ASSIMP_LIBRARY_DIRS  ${ASSIMP_INSTALL_DIR}/lib      CACHE PATH "Where ASSIMP's libraries are." FORCE)


IF (MSVC12)
    SET(ASSIMP_MSVC_VERSION "vc120")
ELSEIF (MSVC14)
    SET(ASSIMP_MSVC_VERSION "vc140")
ENDIF (MSVC12)

if (WIN32 AND ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
	FILE (WRITE ${staging_prefix}/${install_prefix}-build/code/Debug/assimp-${ASSIMP_MSVC_VERSION}-mt.pdb "Create a file to pass the install process")

    SET(ASSIMP_LIBRARIES
        ${ASSIMP_INSTALL_DIR}/lib/assimp-${ASSIMP_MSVC_VERSION}-mt.lib
        ${ASSIMP_INSTALL_DIR}/lib/IrrXML.lib
	    optimized
        ${ASSIMP_INSTALL_DIR}/lib/zlibstatic.lib
	    debug
        ${ASSIMP_INSTALL_DIR}/lib/zlibstaticd.lib

		CACHE FILEPATH "ASSIMP's libraries." FORCE
    )
else ()
    SET(ASSIMP_LIBRARIES
        ${ASSIMP_INSTALL_DIR}/lib/libassimp.a
        ${ASSIMP_INSTALL_DIR}/lib/libIrrXML.a
		CACHE FILEPATH "ASSIMP's libraries." FORCE
    )

    IF (NOT WIN32)
        SET(ASSIMP_LIBRARIES
            ${ASSIMP_LIBRARIES}
            ${ASSIMP_INSTALL_DIR}/lib/libassimp.a
            ${ASSIMP_INSTALL_DIR}/lib/libIrrXML.a
			CACHE FILEPATH "ASSIMP's libraries." FORCE
        )
    ELSE (NOT WIN32)
        SET(ASSIMP_LIBRARIES
            ${ASSIMP_LIBRARIES}
            ${ASSIMP_INSTALL_DIR}/lib/libassimp.a
            ${ASSIMP_INSTALL_DIR}/lib/libIrrXML.a
			CACHE FILEPATH "ASSIMP's libraries." FORCE
        )
    ENDIF (NOT WIN32)

endif ()

SET (ASSIMP_LIBRARY ${ASSIMP_LIBRARIES} CACHE FILEPATH "ASSIMP's libraries." FORCE)

SET(assimp_FOUND ON)
SET(ASSIMP_FOUND ON)


# copy libraries into install tree
install(DIRECTORY ${ASSIMP_INSTALL_DIR}/include/ DESTINATION ${INSTALL_DIR}/third_party/include COMPONENT Development FILES_MATCHING PATTERN "*.*")
install(DIRECTORY ${ASSIMP_INSTALL_DIR}/lib/     DESTINATION ${INSTALL_DIR}/third_party/lib     COMPONENT Development FILES_MATCHING PATTERN "*.*")
#install(DIRECTORY ${ASSIMP_INSTALL_DIR}/lib64/   DESTINATION ${INSTALL_DIR}/third_party/lib64   COMPONENT Development FILES_MATCHING PATTERN "*.*")
install(DIRECTORY ${ASSIMP_INSTALL_DIR}/bin/     DESTINATION ${INSTALL_DIR}/third_party/bin     COMPONENT Development FILES_MATCHING PATTERN "*.*")
#install(DIRECTORY ${ASSIMP_INSTALL_DIR}/share/   DESTINATION ${INSTALL_DIR}/third_party/share   COMPONENT Development FILES_MATCHING PATTERN "*.*")
#install(DIRECTORY ${ASSIMP_INSTALL_DIR}/man/     DESTINATION ${INSTALL_DIR}/third_party/man     COMPONENT Development FILES_MATCHING PATTERN "*.*")

endmacro(build_assimp)
