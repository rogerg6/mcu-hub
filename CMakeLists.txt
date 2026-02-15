cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/gcc-arm-none-eabi.cmake)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME mcuhub)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS_OUTPUT_DIR "${CMAKE_HOME_DIRECTORY}")  

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# ½Ó¿Ú¿â 
add_library(project_includes INTERFACE)
target_include_directories(project_includes INTERFACE 
    ${CMAKE_SOURCE_DIR}/platform 
    ${CMAKE_SOURCE_DIR}/drivers/led 
    ${CMAKE_SOURCE_DIR}/drivers/common 
    ${CMAKE_SOURCE_DIR}/drivers/gpio 
)
 

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(app)
add_subdirectory(drivers)
add_subdirectory(platform)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
    # Add user defined include paths
)


# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    drivers
    app
)
