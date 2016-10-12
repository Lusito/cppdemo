cmake_minimum_required(VERSION 2.6)

project(cppdemo)

#warnings
if(MSVC)
  # Force to always compile with W4
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

#eznet library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/eznet)
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/lib/eznet/include)
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/lib/eznet/lib/enet/include)

#ecstasy library
option(ECSTASY_BUILD_TESTS "" OFF)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/ecstasy)
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/lib/ecstasy/include)

#glfw
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_EXAMPLES "" OFF)
add_subdirectory(lib/glfw)
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/include)
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/deps)

#opengl
find_package(OpenGL REQUIRED)
include_directories(SYSTEM ${OPENGL_INCLUDE_DIR})

#libraries to link
set(LINKED_LIBRARIES eznet enet ecstasy glfw ${OPENGL_gl_LIBRARY})
if(WIN32)
    set( LINKED_LIBRARIES
        ${LINKED_LIBRARIES}
        ws2_32
        winmm
    )
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
endif()

#generated files
set(GENERATED_MESSAGE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/generated)
set(GENERATED_SOURCE_FILES
    ${GENERATED_MESSAGE_PATH}/MessageAdapters.cpp
    ${GENERATED_MESSAGE_PATH}/MessageAdapters.hpp
    ${GENERATED_MESSAGE_PATH}/Messages.hpp
    ${GENERATED_MESSAGE_PATH}/MessageConstants.hpp)

#shared files
file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)
list(APPEND SOURCE_FILES
    ${GENERATED_SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw/deps/glad.c
)

add_executable(demo ${SOURCE_FILES})
target_link_libraries(demo ${LINKED_LIBRARIES})

set_property(TARGET demo PROPERTY CXX_STANDARD 14)
set_property(TARGET demo PROPERTY CXX_STANDARD_REQUIRED ON)
target_compile_definitions(demo PUBLIC -DUSING_ECSTASY -DUSING_SIGNAL11)

set_source_files_properties(${GENERATED_SOURCE_FILES} PROPERTIES GENERATED TRUE)

#generate files
add_custom_command(
	OUTPUT ${GENERATED_SOURCE_FILES}
	COMMAND message_generator ${CMAKE_CURRENT_SOURCE_DIR}/src/messages/messages.def ${GENERATED_MESSAGE_PATH}
	MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/src/messages/messages.def
	DEPENDS message_generator
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	COMMENT "Generating message classes."
)
