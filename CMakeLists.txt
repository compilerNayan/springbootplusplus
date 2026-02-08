cmake_minimum_required(VERSION 3.14)
project(springbootplusplus VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch dependencies
include(FetchContent)

# Fetch springbootplusplus_web
FetchContent_Declare(
    springbootplusplus_web
    GIT_REPOSITORY https://github.com/compilerNayan/springbootplusplus_web.git
    GIT_TAG        main
)

# Fetch springbootplusplus_data
FetchContent_Declare(
    springbootplusplus_data
    GIT_REPOSITORY https://github.com/compilerNayan/springbootplusplus_data.git
    GIT_TAG        main
)

# Fetch cpp_logger (cpp_logger)
FetchContent_Declare(
    cpp_logger
    GIT_REPOSITORY https://github.com/compilerNayan/cpp_logger.git
    GIT_TAG        main
)

FetchContent_MakeAvailable(springbootplusplus_web springbootplusplus_data cpp_logger)

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

# Link to springbootplusplus_web
# Try the namespaced target first, fallback to non-namespaced
if(TARGET springbootplusplus_web::springbootplusplus_web)
    target_link_libraries(springbootplusplus INTERFACE springbootplusplus_web::springbootplusplus_web)
elseif(TARGET springbootplusplus_web)
    target_link_libraries(springbootplusplus INTERFACE springbootplusplus_web)
else()
    # Fallback: manually add include directory if target doesn't exist
    FetchContent_GetProperties(springbootplusplus_web)
    if(springbootplusplus_web_SOURCE_DIR)
        target_include_directories(springbootplusplus INTERFACE
            $<BUILD_INTERFACE:${springbootplusplus_web_SOURCE_DIR}/src>
        )
    endif()
endif()

# Link to springbootplusplus_data
# Try the namespaced target first, fallback to non-namespaced
if(TARGET springbootplusplus_data::springbootplusplus_data)
    target_link_libraries(springbootplusplus INTERFACE springbootplusplus_data::springbootplusplus_data)
elseif(TARGET springbootplusplus_data)
    target_link_libraries(springbootplusplus INTERFACE springbootplusplus_data)
else()
    # Fallback: manually add include directory if target doesn't exist
    FetchContent_GetProperties(springbootplusplus_data)
    if(springbootplusplus_data_SOURCE_DIR)
        target_include_directories(springbootplusplus INTERFACE
            $<BUILD_INTERFACE:${springbootplusplus_data_SOURCE_DIR}/src>
        )
    endif()
endif()

# Link to cpp_logger (cpp_logger)
# Try the namespaced target first, fallback to non-namespaced
if(TARGET cpp_logger::cpp_logger)
    target_link_libraries(springbootplusplus INTERFACE cpp_logger::cpp_logger)
elseif(TARGET cpp_logger)
    target_link_libraries(springbootplusplus INTERFACE cpp_logger)
else()
    # Fallback: manually add include directory if target doesn't exist
    FetchContent_GetProperties(cpp_logger)
    if(cpp_logger_SOURCE_DIR)
        target_include_directories(springbootplusplus INTERFACE
            $<BUILD_INTERFACE:${cpp_logger_SOURCE_DIR}/src>
        )
    endif()
endif()

# Note: For INTERFACE libraries, we don't need to add header files to target_sources
# The include directories are sufficient for consumers to find the headers

