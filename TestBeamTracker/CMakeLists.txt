cmake_minimum_required(VERSION 3.5)

project(TestBeamTracker LANGUAGES CXX)

set(ROOT_COMPONENTS Core GenVector Hist Tree TreePlayer)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# required packages

# Enable C++11 threading support, with a preference for pthread
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
#find_package(Boost 1.64 REQUIRED COMPONENTS program_options)
find_package(ROOT 6.10 REQUIRED COMPONENTS ${ROOT_COMPONENTS})

# ACTS
add_subdirectory(external/acts-core)


file(GLOB_RECURSE TestBeamTracker_files "src/*.cpp" "include/TestBeamTracker/*.hpp")
add_library(TestBeamTracker SHARED ${TestBeamTracker_files})
target_include_directories (TestBeamTracker PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/> $<INSTALL_INTERFACE:include>)
target_include_directories(TestBeamTracker PUBLIC ${ROOT_INCLUDE_DIRS})
target_link_libraries(TestBeamTracker PUBLIC ${ROOT_LIBRARIES})
target_link_libraries(TestBeamTracker PUBLIC ${TestBeamTrackerClassesDict})
target_link_libraries(TestBeamTracker PUBLIC ActsCore)
install(TARGETS TestBeamTracker LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

add_subdirectory(util)

