install_name_tool -change @rpath/../Frameworks/freetype.framework/Versions/A/freetype lib/libfreetype.dylib lib/SFML-2.3.2-osx-clang-universal/lib/libsfml-graphics.2.3.2.dylib
export DYLD_LIBRARY_PATH=lib/tinyxml2-master:lib/tmxparser-master:lib/SFML-2.3.2-osx-clang-universal/lib:lib/
