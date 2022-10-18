cmake_minimum_required(VERSION 3.1)
project(Track_detection)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/qt5/bin")
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets Network)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network)

set(UI_FILES ./mainwindow.ui ./setroi.ui ./addlidar.ui )
#set(RC_FILES ./*.rc)
set(QRC_FILES ./image.qrc)

file(GLOB_RECURSE HEADER_FILES "./*.h" "Clustem/*.h" )
file(GLOB_RECURSE SRC_FILES FOLLOW_SYMLINKS "./*.c*" "Clustem/*.c*")
file(GLOB_RECURSE HK_LIBS "./lib/*.so*" "./lib/HCNetSDKCom/*.so*")

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()


find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
find_package(PCL REQUIRED)
# set(OpenCV_DIR /usr/lib/x86_64-linux-gnu/cmake/opencv4/OpenCVConfig.cmake)

find_package(OpenCV 4.2.0 REQUIRED)
#find_package(VTK REQUIRED)

# message(${PCL_INCLUDE_DIRS})
# message(${PCL_LIBRARY_DIRS})

# message(${OPENCV_INCLUDE_DIRS})
# message(${OPENCV_LIBRARY_DIRS})

message(STATUS "OpenCV_DIR = ${OpenCV_DIR}")
message(STATUS "OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS = ${OpenCV_LIBS}")


include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PCL_INCLUDE_DIRS}
        #${OPENCV_INCLUDE_DIRS}
        /usr/local/opencv/include
        ${VTK_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/HCInclude/incCn
)

message("**********OPENCV_INCLUDE_DIRS**********" ${OPENCV_INCLUDE_DIRS})

include_directories(include ${OPENCV_INCLUDE_DIRS})

link_directories(
        ${PCL_LIBRARY_DIRS}
        ${OPENCV_LIBRARY_DIRS}
        ${VTK_LIBRARY_DIRS}
        ${PROJECT_SOURCE_DIR}/HK_sdk/lib
)

add_definitions(${PCL_DEFINITIONS})

add_executable(${PROJECT_NAME}
        ${SRC_FILES}
        ${HEADER_FILES}
        ${UI_FILES}
        ${RC_FILES}
        ${QRC_FILES}
        )

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED} ${PCL_LIBRARIES} ${OPENCV_LIBRARIES} ${HK_LIBS})
