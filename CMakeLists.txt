#----------------------------------------------------------------------------
# Setup the project
#

FIND_PACKAGE( ILCUTIL REQUIRED COMPONENTS ILCSOFT_CMAKE_MODULES )
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
#

project(SDHCALSim)

# project version
SET( ${PROJECT_NAME}_VERSION_MAJOR 0 )
SET( ${PROJECT_NAME}_VERSION_MINOR 1 )
SET( ${PROJECT_NAME}_VERSION_PATCH 0 )

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#find_package( Marlin 1.0 REQUIRED ) # minimum required Marlin version
find_package( ROOT REQUIRED ) # minimum required Marlin version
#find_package( CLHEP REQUIRED )
find_package( LCIO REQUIRED )


FOREACH( pkg LCIO ROOT Geant4 )
	IF( ${pkg}_FOUND )
		INCLUDE_DIRECTORIES( ${${pkg}_INCLUDE_DIRS} )
		LINK_LIBRARIES( ${${pkg}_LIBRARIES} )
		ADD_DEFINITIONS ( ${${pkg}_DEFINITIONS} )
	ENDIF()
ENDFOREACH()

#
# Add specific modules
#

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#

ADD_DEFINITIONS( "-Wall" )

include( ${Geant4_USE_FILE} )
include_directories( ${PROJECT_SOURCE_DIR}/include )

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)

file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

SET (SDHCALSim ${PROJECT_SOURCE_DIR}/src/SDHCALSim.cxx)
SET (SDHCALSimVis ${PROJECT_SOURCE_DIR}/src/SDHCALSimVis.cxx)
SET (SDHCALSimWithScintillator ${PROJECT_SOURCE_DIR}/src/SDHCALSimWithScintillator.cxx)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(SDHCALSim ${SDHCALSim} ${sources} ${headers})
add_executable(SDHCALSimVis ${SDHCALSimVis} ${sources} ${headers})
add_executable(SDHCALSimWithScintillator ${SDHCALSimWithScintillator} ${sources} ${headers})
#
target_link_libraries(SDHCALSim ${Geant4_LIBRARIES} ${EXTRA_LIB})
target_link_libraries(SDHCALSimVis ${Geant4_LIBRARIES} ${EXTRA_LIB})
target_link_libraries(SDHCALSimWithScintillator ${Geant4_LIBRARIES} ${EXTRA_LIB})

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS SDHCALSim DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS SDHCALSimVis DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS SDHCALSimWithScintillator DESTINATION ${PROJECT_SOURCE_DIR}/bin)
