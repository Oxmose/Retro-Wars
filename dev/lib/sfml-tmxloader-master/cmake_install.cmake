# Install script for directory: /Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master

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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "bin")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/libpugi.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpugi.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpugi.dylib")
    execute_process(COMMAND "/opt/local/bin/install_name_tool"
      -id "libpugi.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpugi.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libpugi.dylib")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "bin")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/libtmx-loader.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtmx-loader.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtmx-loader.dylib")
    execute_process(COMMAND "/opt/local/bin/install_name_tool"
      -id "libtmx-loader.dylib"
      -change "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/libpugi.dylib" "libpugi.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtmx-loader.dylib")
    execute_process(COMMAND /opt/local/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtmx-loader.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtmx-loader.dylib")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE DIRECTORY FILES "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/include")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tmx/examples" TYPE EXECUTABLE FILES "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/BenchMark")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/BenchMark" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/BenchMark")
    execute_process(COMMAND "/opt/local/bin/install_name_tool"
      -change "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/libpugi.dylib" "libpugi.dylib"
      -change "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/libtmx-loader.dylib" "libtmx-loader.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/BenchMark")
    execute_process(COMMAND /opt/local/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/BenchMark")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/BenchMark")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tmx/examples" TYPE EXECUTABLE FILES "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/DrawWithDebug")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/DrawWithDebug" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/DrawWithDebug")
    execute_process(COMMAND "/opt/local/bin/install_name_tool"
      -change "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/libpugi.dylib" "libpugi.dylib"
      -change "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/libtmx-loader.dylib" "libtmx-loader.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/DrawWithDebug")
    execute_process(COMMAND /opt/local/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/DrawWithDebug")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/DrawWithDebug")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tmx/examples" TYPE EXECUTABLE FILES "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/Isometric")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/Isometric" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/Isometric")
    execute_process(COMMAND "/opt/local/bin/install_name_tool"
      -change "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/libpugi.dylib" "libpugi.dylib"
      -change "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/libtmx-loader.dylib" "libtmx-loader.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/Isometric")
    execute_process(COMMAND /opt/local/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/Isometric")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/Isometric")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tmx/examples" TYPE EXECUTABLE FILES "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/QuadTree")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/QuadTree" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/QuadTree")
    execute_process(COMMAND "/opt/local/bin/install_name_tool"
      -change "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/libpugi.dylib" "libpugi.dylib"
      -change "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/libtmx-loader.dylib" "libtmx-loader.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/QuadTree")
    execute_process(COMMAND /opt/local/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/QuadTree")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/QuadTree")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tmx/examples" TYPE EXECUTABLE FILES "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/ShaderEffects")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/ShaderEffects" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/ShaderEffects")
    execute_process(COMMAND "/opt/local/bin/install_name_tool"
      -change "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/libpugi.dylib" "libpugi.dylib"
      -change "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/libtmx-loader.dylib" "libtmx-loader.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/ShaderEffects")
    execute_process(COMMAND /opt/local/bin/install_name_tool
      -delete_rpath "/usr/local/lib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/ShaderEffects")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tmx/examples/ShaderEffects")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tmx/examples/maps" TYPE DIRECTORY FILES "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/maps/")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tmx/examples/fonts" TYPE DIRECTORY FILES "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/fonts/")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/tristansterin/Documents/Retro-Wars/dev/lib/sfml-tmxloader-master/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
