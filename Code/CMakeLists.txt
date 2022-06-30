cmake_minimum_required(VERSION 3.20)
project(proj)

set(DATA_STRUCTURES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Data Structures")
set(HT_DIR "${DATA_STRUCTURES_DIR}/Hash Table")
set(RB_TREE_DIR "${DATA_STRUCTURES_DIR}/RB Tree")
set(LIST_DIR "${DATA_STRUCTURES_DIR}/Single Linked List")

set(DATABASES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Databases")

include_directories(${HT_DIR}
        ${RB_TREE_DIR}
        ${LIST_DIR})
include_directories(${DATABASES_DIR})


add_subdirectory("Data Structures")
add_subdirectory("Databases")