cmake_minimum_required(VERSION 2.6)

project(eznet_examples)

#eznet library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/eznet)
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/lib/eznet/include)
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/lib/eznet/lib/enet/include)

#libraries to link
set(LINKED_LIBRARIES eznet enet )
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
set(SHARED_SOURCE_FILES
    ${GENERATED_SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CustomAdapters.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CustomAdapters.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CustomMessages.hpp
)

add_executable(server ${SHARED_SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/src/Server.cpp)
target_link_libraries(server ${LINKED_LIBRARIES})

add_executable(client ${SHARED_SOURCE_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/src/Client.cpp)
target_link_libraries(client ${LINKED_LIBRARIES})

set_source_files_properties(${GENERATED_SOURCE_FILES} PROPERTIES GENERATED TRUE)

#generate files
add_custom_command(
	OUTPUT ${GENERATED_SOURCE_FILES}
	COMMAND message_generator ${CMAKE_CURRENT_SOURCE_DIR}/src/messages.def ${GENERATED_MESSAGE_PATH}
	MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/src/messages.def
	DEPENDS message_generator
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	COMMENT "Generating message classes."
	)
