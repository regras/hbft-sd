cmake_minimum_required(VERSION 3.5)

#set(CMAKE_VERBOSE_MAKEFILE off)

project(hbft_sdhash)

set(CMAKE_CXX_FLAGS "-w -std=c++14 -O3 -D_BSD_SOURCE -fpermissive")

set(CMAKE_C_FLAGS "-w -std=c99 -O3 -D_BSD_SOURCE")

set(CPP_FILES src/sdhash.cpp)


set(C_FILES
    src/bloomfilter.c
    src/hashing.c
    src/helper.c
    src/bloomfiltertree.c header/filehash.h src/filehash.c src/fingerprint.c
    src/fingerprintList.c
    src/main.c)


set_source_files_properties(${C_FILES} PROPERTIES COMPILE_FLAGS "-x c")


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/.)


set_source_files_properties(${CPP_FILES} ${C_FILES} PROPERTIES LANGUAGE CXX)

add_executable(hbft_sdhash  ${CPP_FILES} ${C_FILES})


target_link_libraries(hbft_sdhash  -lssl -lcrypto )
