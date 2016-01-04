# Install script for directory: /home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/tmxparser" TYPE FILE FILES
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxPropertySet.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxObject.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxTileOffset.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxMap.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxMapTile.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxImageLayer.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxPolygon.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/base64/base64.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxObjectGroup.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxPolyline.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxPoint.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxImage.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxLayer.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxTileLayer.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxUtil.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxTileset.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxTerrain.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxEllipse.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxTerrainArray.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/src/TmxTile.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/Tmx.h"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/tmxparser/Tmx.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtmxparser.so.2.0.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtmxparser.so.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtmxparser.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/libtmxparser.so.2.0.1"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/libtmxparser.so.2"
    "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/libtmxparser.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtmxparser.so.2.0.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtmxparser.so.2"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtmxparser.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_REMOVE
           FILE "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/libtmxparser.a")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/tmxparser.pc")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/alexy/Documents/ENSL/PROJET/Retro-Wars/dev/lib/Linux/tmxparser-master/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
