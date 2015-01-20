# Set a list of source files
SET(SRC basics.cpp CFG.cpp CNF.cpp tinyxml2.cpp)

# Add an executable that should be built
add_executable(${EXECUTABLE_NAME} main.cpp ${SRC})

# Set install targets for when we run 'make install'
install(TARGETS ${EXECUTABLE_NAME} #gamelogic
    RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin
    ARCHIVE DESTINATION ${PROJECT_SOURCE_DIR}/lib
    LIBRARY DESTINATION ${PROJECT_SOURCE_DIR}/lib)
