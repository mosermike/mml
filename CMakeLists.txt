cmake_minimum_required(VERSION 3.10)
project(mml VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Gather the source files
file(GLOB_RECURSE MML_SOURCES src/*.cpp)

# Option to choose between shared or static library, default to shared
option(BUILD_SHARED_LIBS "Build shared libraries by default" ON)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

# Create the library
add_library(mml ${MML_SOURCES})

# Set the include directories for the library
target_include_directories(mml PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Set the output directory for the shared library
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Set the output directory for test executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/tests)

# Install the library
install(TARGETS mml
        EXPORT mmlTargets
        LIBRARY DESTINATION /usr/lib
        INCLUDES DESTINATION /usr/local/include
)

# Install the header files
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/mml
        DESTINATION /usr/local/include)

# Install the mml.hpp header
install(FILES ${PROJECT_SOURCE_DIR}/include/mml.hpp
        DESTINATION /usr/local/include)

# Generate the mml-config.cmake file and install it
install(EXPORT mmlTargets
        FILE mmlTargets.cmake
        DESTINATION /usr/lib/cmake/mml)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/mml-configVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_file(mml-config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/mml-config.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/mml-config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/mml-configVersion.cmake"
    DESTINATION /usr/lib/cmake/mml
)


# Enable testing
enable_testing()

# Collect all test source files
file(GLOB_RECURSE MML_TEST_SOURCES test/*.cpp)

# Add an executable for each test file
foreach(TEST_FILE ${MML_TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_FILE})
    target_link_libraries(${TEST_NAME} mml)

    # Output test executables to the 'tests' directory
    set_target_properties(${TEST_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# Optionally, add a custom test target
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS ${TEST_NAME})

# Add custom target to uninstall
add_custom_target(uninstall
    COMMAND rm -rf /usr/local/include/mml
    COMMAND rm -rf /usr/local/include/mml.hpp
    COMMAND rm -rf /usr/lib/cmake/mml
    COMMAND rm -rf /usr/lib/libmml.so
    COMMAND rm -rf /usr/lib/libmml.so.${PROJECT_VERSION}
    COMMAND rm -rf /usr/lib/cmake/mml
    COMMENT "Uninstalling files..."
)
	 
