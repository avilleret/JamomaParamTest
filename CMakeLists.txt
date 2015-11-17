project(ofApp)
set(APP ofApp)

cmake_minimum_required(VERSION 2.8)

## Doesn't work yet
## TODO fix JamomaCore installation (missing FindJamoma.cmake)
## find_package(Jamoma 0.6 REQUIRED) # Jamoma has to be installed

include(../of/openFrameworks.cmake)

ofxaddon(ofxGui)

set(SOURCES
    src/main.cpp
    src/ofApp.cpp
)

INCLUDE_DIRECTORIES("/usr/local/jamoma/include/jamoma/")

LINK_DIRECTORIES("/usr/local/jamoma/lib/")

add_executable(
    ${APP}
    MACOSX_BUNDLE
    ${SOURCES}
    ${OFXADDONS_SOURCES}
)

target_link_libraries(
    ${APP}
    ${OPENFRAMEWORKS_LIBRARIES}
)

target_link_libraries(
  ${APP}
  JamomaModular
  JamomaFoundation)

cotire(${APP})
