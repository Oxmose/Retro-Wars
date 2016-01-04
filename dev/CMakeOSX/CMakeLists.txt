project(RetroWars)

include_directories(/usr/local/include)
include_directories(lib/OSX/tinyxml2-master)
include_directories(lib/OSX/tmxparser-master)
include_directories(lib/OSX/SFML-2.3.2-osx-clang-universal/include)

link_directories(/usr/local/lib)
link_directories(lib/OSX/tinyxml2-master)
link_directories(lib/OSX/tmxparser-master)
link_directories(lib/OSX/SFML-2.3.2-osx-clang-universal/lib)


SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++14 -Wall")
SET(GCC_COVERAGE_LINK_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -pthread -ltinyxml2 -ltmxparser")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")


file(
        GLOB_RECURSE

        source_files

        src/*
)


add_executable(

    bin/OSXRelease/RetroWars

    ${source_files}
)