project(RetroWars)

include_directories(/usr/local/include)

link_directories(/usr/local/lib)


SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++14")
SET(GCC_COVERAGE_LINK_FLAGS "-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -ltmx-loader -lpugixml")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

file(
        GLOB_RECURSE

        source_files

        src/*
)


add_executable(

    bin/RetroWars

    ${source_files}
)
