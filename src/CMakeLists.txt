cmake_minimum_required(VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
# https://stackoverflow.com/questions/6594796/how-do-i-make-cmake-output-into-a-bin-dir
# We only need 'bin' here.

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
 
# Locate GTest
#find_package(gtest REQUIRED)

include_directories(Headers/*)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(test.o testBoss.c)

#add_executable(word_entry_tests word_entry_tests.cc word_entry.cc)
#target_link_libraries(word_entry_tests ${GTEST_LIBRARIES} pthread)

#add_executable(word_entry_tests2 word_entry_tests2.cc word_entry.cc)
#target_link_libraries(word_entry_tests2 ${GTEST_LIBRARIES} pthread)
