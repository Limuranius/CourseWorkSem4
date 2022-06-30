add_library(ParsersLib parsers.cpp)
target_link_libraries(ParsersLib HashTableLib RBTreeLib ListLib)

add_library(RefPlanetsLib ReferencePlanets.cpp)
target_link_libraries(RefPlanetsLib ParsersLib HashTableLib RBTreeLib ListLib)

add_library(RefAttrsLib ReferenceAttributes.cpp)
target_link_libraries(RefAttrsLib ParsersLib HashTableLib RBTreeLib ListLib)

add_library(DatabaseLib Database.cpp)
target_link_libraries(DatabaseLib RefAttrsLib RefPlanetsLib)

include_directories(.)


