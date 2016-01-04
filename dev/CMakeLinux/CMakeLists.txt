project(RetroWars)

include_directories(lib/Linux/tinyxml2-master)
include_directories(lib/Linux/tmxparser-master)
include_directories(lib/Linux/SFML_LINUX/include)

link_directories(lib/Linux/tinyxml2-master)
link_directories(lib/Linux/tmxparser-master)
link_directories(lib/Linux/SFML_LINUX/lib)


SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++14 -Wall")
SET(GCC_COVERAGE_LINK_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio -pthread -ltinyxml2 -ltmxparser")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

file(
        GLOB_RECURSE

        source_files

        src/*
)


add_executable(

    bin/LinuxRelease/RetroWars

    ${source_files}
)
