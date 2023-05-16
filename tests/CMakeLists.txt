cmake_minimum_required(VERSION 3.10)

project(uCRC_test LANGUAGES CXX)

set(CMAKE_CXX_FLAGS_DEBUG   "-DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")
set(CMAKE_CXX_FLAGS         "-O2 -g -DSTEST_ONLY_BASENAME")
if(UNIX)
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -DSTEST_UNIX_SLASH")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()



# Enable ASan
# cmake -DUSE_ASAN=ON
if(USE_ASAN AND NOT MINGW) #ASan dont work in MinGW
    message(STATUS "Enabled Address Sanitizer (ASan) USE_ASAN is set to: ${USE_ASAN}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
endif()


message(STATUS "Generator is set to: ${CMAKE_GENERATOR}")



set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/..)


set(SOURCES
    crc_test.cpp
    ${INCLUDE_DIR}/ucrc_t.cpp
)


set(HEADERS
    stest.h
    ${INCLUDE_DIR}/ucrc_t.h
)



# --- General Tests ---
add_executable(tests ${HEADERS} ${SOURCES})

target_include_directories(tests PRIVATE ${INCLUDE_DIR})

# phony target for run tests
add_custom_target(run_tests ALL COMMAND tests DEPENDS tests)

# copy std_file_to_test_crc to build dir
add_custom_command(TARGET tests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/std_file_to_test_crc
    ${CMAKE_CURRENT_BINARY_DIR}/std_file_to_test_crc
)
