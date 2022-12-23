cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME imu)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_BUILD_TYPE "Release")

file(GLOB TCP "TCP/*.cpp" "TCP/*.h")
aux_source_directory(. SRC_LIST)

find_package(PCL 1.8 REQUIRED)
find_package(OpenCV 3.4.1 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS} ${OpenCV_LIB_DIR})
add_definitions(${PCL_DEFINITIONS})

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${TCP})
target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} ${OpenCV_LIBS}
        Threads::Threads
        )