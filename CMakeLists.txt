cmake_minimum_required(VERSION 3.8)
project(pong)



if (WIN32)
    set(FREEGLUT_INCLUDE_DIRS "C:/Program\ Files/Common\ Files/freeglut/include")
    set(FREEGLUT_LIBRARY_DIRS "C:/Program\ Files/Common\ Files/freeglut/lib")
endif (WIN32)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-deprecated -Werror=return-type")

find_package (OpenGL REQUIRED)

if (APPLE OR UNIX)
    find_package(GLUT REQUIRED)
endif (APPLE OR UNIX)

if (WIN32)
    include_directories(${OPENGL_INCLUDE_DIR}  ${FREEGLUT_INCLUDE_DIRS})
    link_directories(${FREEGLUT_LIBRARY_DIRS})
elseif (APPLE)
    include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})
elseif (UNIX)
    include_directories(${OPENGL_INCLUDE_DIR} ${FREEGLUT_INCLUDE_DIRS})
endif ()

file(GLOB SOURCE_FILES
  src/*.cpp
  src/*.h
  )

add_executable(pong ${SOURCE_FILES})

if (WIN32)
  target_link_libraries (pong ${OPENGL_LIBRARIES} freeglut)
elseif (APPLE OR UNIX)
  target_link_libraries (pong ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
endif ()
