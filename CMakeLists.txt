# CMakeList.txt : CMake project for Final Fantasy 4 DS Save Editor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Final Fantasy 4 DS Save Editor")

# Add source to this project's executable.
add_executable (CMakeTarget "Main.cpp" "Main.h" "SaveFile.h" "Structs.h" "SaveFile.cpp")

# TODO: Add tests and install targets if needed.
