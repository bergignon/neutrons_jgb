cmake_minimum_required(VERSION 3.16...3.21)
project(First_sim)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

add_executable(first_sim main.cc ${sources} ${headers})
target_link_libraries(first_sim ${Geant4_LIBRARIES})

add_custom_target(First_sim DEPENDS first_sim)
