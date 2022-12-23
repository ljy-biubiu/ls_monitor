cmake_minimum_required(VERSION 3.1)
project(PortMonitor)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_BUILD_TYPE "Release")
# set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/qt5/bin")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QRC_FILES ./UI/resource/images.qrc ./UI/resource/qss.qrc ./UI/resource/webSource.qrc)


# file(GLOB_RECURSE HEADER_FILES "./*.h")
# file(GLOB_RECURSE SRC_FILES FOLLOW_SYMLINKS "./*.cpp")
file(GLOB_RECURSE HK_LIBS "./DRIVER/CAMERA/sdk/lib/HCNetSDKCom/*.so*"  "./DRIVER/CAMERA/sdk/lib/*.so*"
                        "/snap/ffmpeg/1286/usr/lib/libavcodec.so" "/snap/ffmpeg/1286/usr/lib/libavdevice.so.57.10.100" "/snap/ffmpeg/1286/usr/lib/libavfilter.so.6.107.100"
                        "/snap/ffmpeg/1286/usr/lib/libavformat.so" "/snap/ffmpeg/1286/usr/lib/libavutil.so" "/snap/ffmpeg/1286/usr/lib/libpostproc.so.54.7.100"
                        "/snap/ffmpeg/1286/usr/lib/libswresample.so" "/snap/ffmpeg/1286/usr/lib/libswscale.so" )

file(GLOB OTHER_SOURCES "ALGORITHM/ROIFilter/*.cpp" "ALGORITHM/CSF/*.cpp"
                        "ALGORITHM/UtilMethod/*.cpp" "ALGORITHM/src/*.cpp" 
                        "LOG/src/*.cpp" "UI/src/*.cpp" "DRIVER/CAMERA/src/*.cpp"
                        "DRIVER/POINTCLOUD/src/*.cpp" "MSGSERIVE/*.cpp"
                        "COMMUNICATION/src/*.cpp" "COMMUNICATION/IMU/*.cpp"  
                        "COMMUNICATION/POMS/*.cpp" "src/*.cpp" "Utility/*.cpp")
                        
file(GLOB OTHER_INCLUDES "ALGORITHM/ROIFilter/*.hpp" "ALGORITHM/include/*.h*"
                        "ALGORITHM/CSF/*.h*" "ALGORITHM/UtilMethod/*.h*" "DRIVER/CAMERA/include/*.h"
                        "LOG/include/*.h*" "UI/include/*.h*" "DRIVER/POINTCLOUD/include/*.h*"
                        "DRIVER/POINTCLOUD/include/*.h*" "MSGSERIVE/*.h*" "DRIVER/CAMERA/sdk/HCInclude/incEn/*.h*"
                        "PROTOCOL/include/*.h*"  "COMMUNICATION/include/*.h*"  "COMMUNICATION/IMU/*.h" 
                        "COMMUNICATION/POMS/*.h" "include/*.h*" "Utility/*.h" "/snap/ffmpeg/1286/usr/include/libavcodec/*.h")

file(GLOB ALL_INCLUDES "ALGORITHM/ROIFilter" "ALGORITHM/include"
                        "ALGORITHM/CSF" "ALGORITHM/UtilMethod" "DRIVER/CAMERA/include"
                        "LOG/include" "UI/include" "DRIVER/POINTCLOUD/include"
                        "DRIVER/POINTCLOUD/include" "MSGSERIVE" "DRIVER/CAMERA/sdk/HCInclude/incEn"
                        "PROTOCOL/include"  "COMMUNICATION/include"  "include" "Utility" "/snap/ffmpeg/1286/usr/include" )                

set(OTHER_SRCS ${OTHER_SOURCES} ${OTHER_INCLUDES})


find_package(Qt5 REQUIRED COMPONENTS Core WebEngineWidgets Widgets  WebChannel WebEngineCore)

set(QT_LIBRARIES ${Qt5Widgets_LIBRARIES} ${Qt5Core_LIBRARIES}  ${Qt5WebEngineWidgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES})
# find_package(Qt5 COMPONENTS ${REQUIRED_LIBS} REQUIRED)
find_package(PCL 1.9 REQUIRED)
find_package(OpenCV 3.4.1 REQUIRED)
find_package(VTK REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${PCL_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${VTK_INCLUDE_DIRS}
        ${JSONCPP_INCLUDE_DIRS}
        ${ALL_INCLUDES}
)

link_directories(
        ${PCL_LIBRARY_DIRS}
        ${OpenCV_LIB_DIR}
        ${VTK_LIBRARY_DIRS}
)

add_definitions(${PCL_DEFINITIONS})

add_executable(${PROJECT_NAME}
        ${UI_FILES}
        ${RC_FILES}
        ${QRC_FILES}
        ${QT_FORMS_H}
        ${SRC_LIST}
        ${OTHER_SRCS}
        )

target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES}  ${REQUIRED_LIBS_QUALIFIED} ${JSONCPP_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBS} ${HK_LIBS})




