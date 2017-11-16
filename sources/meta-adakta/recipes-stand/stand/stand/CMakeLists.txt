cmake_minimum_required(VERSION 2.6)

project(stand)

# Location where cmake first looks for cmake modules.
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "/usr")
set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin" CACHE PATH "Installation directory for executables")

set(SRCS
  src/stand.cxx
  src/gpio.cxx
  src/minilib.cxx
  src/tty.cxx
  src/memadmin.cxx
)

include_directories(src)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -Wall -fpermissive -Wno-unused-variable -Wno-write-strings -Wextra -std=c99 ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pipe -Wall -fpermissive -Wno-unused-variable -Wno-write-strings -fstack-protector-strong ")

set(CMAKE_C_FLAGS_DEBUG "-Os -g -ggdb -pg")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Os -g -ggdb -pg")
set(CMAKE_C_FLAGS_RELEASE "-Os")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os")

set(CMAKE_CXX_FLAGS_DEBUG "-Os -g -ggdb -pg")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Os -g -ggdb -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(STATUS "GNU v${CMAKE_CXX_COMPILER_VERSION}")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8)
        message(FATAL_ERROR "GCC version must be at least 4.8!")
    endif()
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.9)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 ")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wconditionally-supported ")
    endif()
    if ((CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 5.0) OR (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.0))
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wswitch-bool ")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wswitch-bool ")
    endif()
    if ((CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 6.0) OR (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 6.0))
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
    endif()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-show-caret -ftrack-macro-expansion ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-show-caret -ftrack-macro-expansion -Wnoexcept -Wstrict-null-sentinel ")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(STATUS "Clang v${CMAKE_CXX_COMPILER_VERSION}")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 3.6)
        message(FATAL_ERROR "Clang version must be at least 3.6!")
    endif()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wswitch-bool -Wnull-dereference -Wunused-const-variable ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wswitch-bool -Wnull-dereference -Wunused-const-variable -std=c++14 ")
else()
    message(WARNING "You are using an unsupported compiler! Compilation has only been tested with Clang and GCC.")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fpermissive")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")

add_executable(stand WIN32 ${SRCS})
target_link_libraries(stand "-lpthread" jsoncpp)
install(TARGETS stand RUNTIME DESTINATION "${INSTALL_BIN_DIR}")
