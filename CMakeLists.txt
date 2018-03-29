cmake_minimum_required(VERSION 3.5.0)
project(BalloonFinderFramework)
set(TARGET BalloonFinderFramework)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS} -Wno-format-security -Wno-literal-suffix")

find_package(OpenCV REQUIRED)

include_directories(
    include
	${OpenCV_INCLUDE_DIRS}
)

## Declare a C++ library
# add_library(SRC_FILES
#   src/main.cc
# )

target_link_libraries(snap_cam
  ${OpenCV_LIBS}
)

# add the ROS executables
add_executable(${TARGET} src/main.cc)
target_link_libraries(${TARGET} ${OpenCV_LIBS})

