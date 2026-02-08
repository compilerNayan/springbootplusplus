cmake_minimum_required(VERSION 3.14)
project(springbootplusplus VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch dependencies
include(FetchContent)

# Fetch springbootplusplus-web
FetchContent_Declare(
    springbootplusplus-web
    GIT_REPOSITORY https://github.com/compilerNayan/arduinolib2.git
    GIT_TAG        main
)

# Fetch springbootplusplus-data
FetchContent_Declare(
    springbootplusplus-data
    GIT_REPOSITORY https://github.com/compilerNayan/arduinolib3.git
    GIT_TAG        main
)

# Fetch cpp-logger (cpp_logger)
FetchContent_Declare(
    cpp-logger
    GIT_REPOSITORY https://github.com/compilerNayan/cpp_logger.git
    GIT_TAG        main
)

FetchContent_MakeAvailable(springbootplusplus-web springbootplusplus-data cpp-logger)

# Create header-only library (INTERFACE library)
add_library(springbootplusplus INTERFACE)

# Set target properties
set_target_properties(springbootplusplus PROPERTIES
    VERSION ${PROJECT_VERSION}
)

# Set include directories for springbootplusplus's own headers (in src directory)
target_include_directories(springbootplusplus INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include>
)

# Link to springbootplusplus-web
# Try the namespaced target first, fallback to non-namespaced
if(TARGET springbootplusplus-web::springbootplusplus-web)
    target_link_libraries(springbootplusplus INTERFACE springbootplusplus-web::springbootplusplus-web)
elseif(TARGET springbootplusplus-web)
    target_link_libraries(springbootplusplus INTERFACE springbootplusplus-web)
else()
    # Fallback: manually add include directory if target doesn't exist
    FetchContent_GetProperties(springbootplusplus-web)
    if(springbootplusplus-web_SOURCE_DIR)
        target_include_directories(springbootplusplus INTERFACE
            $<BUILD_INTERFACE:${springbootplusplus-web_SOURCE_DIR}/src>
        )
    endif()
endif()

# Link to springbootplusplus-data
# Try the namespaced target first, fallback to non-namespaced
if(TARGET springbootplusplus-data::springbootplusplus-data)
    target_link_libraries(springbootplusplus INTERFACE springbootplusplus-data::springbootplusplus-data)
elseif(TARGET springbootplusplus-data)
    target_link_libraries(springbootplusplus INTERFACE springbootplusplus-data)
else()
    # Fallback: manually add include directory if target doesn't exist
    FetchContent_GetProperties(springbootplusplus-data)
    if(springbootplusplus-data_SOURCE_DIR)
        target_include_directories(springbootplusplus INTERFACE
            $<BUILD_INTERFACE:${springbootplusplus-data_SOURCE_DIR}/src>
        )
    endif()
endif()

# Link to cpp-logger (cpp_logger)
# Try the namespaced target first, fallback to non-namespaced
if(TARGET cpp-logger::cpp-logger)
    target_link_libraries(springbootplusplus INTERFACE cpp-logger::cpp-logger)
elseif(TARGET cpp-logger)
    target_link_libraries(springbootplusplus INTERFACE cpp-logger)
else()
    # Fallback: manually add include directory if target doesn't exist
    FetchContent_GetProperties(cpp-logger)
    if(cpp-logger_SOURCE_DIR)
        target_include_directories(springbootplusplus INTERFACE
            $<BUILD_INTERFACE:${cpp-logger_SOURCE_DIR}/src>
        )
    endif()
endif()

# Note: For INTERFACE libraries, we don't need to add header files to target_sources
# The include directories are sufficient for consumers to find the headers

