# Set minimum CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Set project name
PROJECT(MusicMeetsMachines)

# Add std=c++11 to the CXX flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Set the name of our executable
set(EXECUTABLE_NAME mmm)
 
# Add the src subdirectory
add_subdirectory(src)
