#----------------------------------------------------------------------------
# Setup the project

cmake_minimum_required(VERSION 3.16...3.21)
project(NeutronDeposit)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable

find_package(Geant4 REQUIRED)

#find_package(G4mpi REQUIRED)
#find_package(MPI REQUIRED)
#set(CMAKE_CXX_COMPILER mpicxx)

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project

include(${Geant4_USE_FILE})

#include_directories(${PROJECT_SOURCE_DIR}/include ${G4mpi_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)


#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries

add_executable(neutron_sim main.cc ${sources} ${headers})

target_link_libraries(neutron_sim ${Geant4_LIBRARIES})
#target_link_libraries(neutron_sim ${G4mpi_LIBRARIES} ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build B1. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.

file(GLOB MACRO_FILES "*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone

add_custom_target(NeutronDeposit DEPENDS neutron_sim)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX

install(TARGETS neutron_sim DESTINATION bin)


