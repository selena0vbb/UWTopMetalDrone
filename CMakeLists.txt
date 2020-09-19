cmake_minimum_required(VERSION 3.5.1)

# Create project
project(uw_topmetal_drone)
set(CMAKE_BUILD_TYPE Debug)

# Find required modules
# find_package(HDF5 COMPONENTS CXX NO_MODULE REQUIRED shared)


# includes
include_directories(include)


# sources
file(GLOB sources "${PROJECT_SOURCE_DIR}/source/*.cpp")
file(GLOB headers "${PROJECT_SOURCE_DIR}/include/*.h")

# create executable
add_executable(topMetalDrone topMetalDrone.cpp ${sources} ${headers})
target_link_libraries(topMetalDrone CAENDigitizer)
