cmake_minimum_required(VERSION 3.22)
enable_language(C)

# STM32CubeMX generated include paths
set(drv_include
    ${CMAKE_CURRENT_SOURCE_DIR}/common
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio
    ${CMAKE_CURRENT_SOURCE_DIR}/led
)

set(drv_src
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio/gpio_stm32f429.c
    ${CMAKE_CURRENT_SOURCE_DIR}/led/led.c
)


set(MX_LINK_LIBS 
    drivers
    ${TOOLCHAIN_LINK_LIBRARIES}
    
)

# Create drivers static library
add_library(drivers OBJECT)
target_sources(drivers PRIVATE ${drv_src})
target_include_directories(drivers PUBLIC ${drv_include})
target_link_libraries(drivers PUBLIC stm32cubemx)
target_link_libraries(drivers PRIVATE project_includes)


# # Add STM32CubeMX generated application sources to the project
# target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MX_Application_Src})

# # Link directories setup
# target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${MX_LINK_DIRS})

# # Add libraries to the project
# target_link_libraries(${CMAKE_PROJECT_NAME} ${MX_LINK_LIBS})

# # Add the map file to the list of files to be removed with 'clean' target
# set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
