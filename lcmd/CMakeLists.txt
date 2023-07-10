cmake_minimum_required(VERSION 3.5)

project(lcmd)

if (NOT DEFINED ENV{COMMON_DIR})
	message(FATAL_ERROR "Please set COMMON_DIR first")
else()
	message(STATUS "COMMON_DIR is $ENV{COMMON_DIR}")
endif()
set(CMAKE_FIND_ROOT_PATH $ENV{COMMON_DIR})
list(APPEND CMAKE_PREFIX_PATH $ENV{COMMON_DIR})
set(CMAKE_INSTALL_PREFIX $ENV{COMMON_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
add_definitions(-DDISABLE_TEST)

# Abseil requires C++11
set(CMAKE_CXX_STANDARD 11)  

find_package(spdlog REQUIRED)
find_package(lcm REQUIRED)

include_directories(src)

add_executable(${PROJECT_NAME} src/lcmd.cpp)

install(TARGETS ${PROJECT_NAME}
RUNTIME DESTINATION bin)

# spdlog
target_link_libraries(${PROJECT_NAME} spdlog::spdlog_header_only)
# lcm
target_link_libraries(${PROJECT_NAME} lcm)