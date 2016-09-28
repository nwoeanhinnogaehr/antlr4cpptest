cmake_minimum_required(VERSION 3.6)

# -*- mode:cmake -*-
if(NOT UNIX)
    message(FATAL "Unsupported operating system")
endif()

set(ANTLR4 ~/school/cmput/415/antlr4)

file(GLOB g4_files
    ${PROJECT_SOURCE_DIR}/src/*.g4
    )

file(GLOB generated_src
    ${PROJECT_SOURCE_DIR}/generated/src/*
    )

file(GLOB user_src
    ${PROJECT_SOURCE_DIR}/src/*
    )

add_custom_command(
    OUTPUT ${generated_src}
    DEPENDS ${g4_files}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_SOURCE_DIR}/generated/
    COMMAND ${PROJECT_SOURCE_DIR}/generate.sh
    )

include_directories(
    ${ANTLR4}/runtime/Cpp/runtime/src
    ${ANTLR4}/runtime/Cpp/runtime/src/misc
    ${ANTLR4}/runtime/Cpp/runtime/src/atn
    ${ANTLR4}/runtime/Cpp/runtime/src/dfa
    ${ANTLR4}/runtime/Cpp/runtime/src/tree
    ${ANTLR4}/runtime/Cpp/runtime/src/support
    ${PROJECT_SOURCE_DIR}/generated/src
    )

set(SRC
    ${user_src}
    ${generated_src}
    )

foreach( src_file ${SRC} )
    set_source_files_properties(
        ${src_file}
        PROPERTIES
        COMPILE_FLAGS -Wno-overloaded-virtual
        )
endforeach( src_file ${SRC} )

add_executable(antlr4test
    ${SRC}
    )
#add_precompiled_header(antlr4-demo ${PROJECT_SOURCE_DIR}/runtime/src/antlrcpp-Prefix.h)

target_link_libraries(antlr4test ${PROJECT_SOURCE_DIR}/../antlr4/runtime/Cpp/dist/libantlr4-runtime.so)
