set(SOURCE_LIST
    include/enums.hpp
    include/renderer.hpp
    include/vk/vk_renderer.hpp
    include/vk/vk_instance.hpp
    include/vk/vk_extensions.hpp
    include/vk/vk_validation_layers.hpp
    include/vk/vk_debug_messenger.hpp
    include/vk/vk_device.hpp
    include/vk/vk_queue_families.hpp
    include/vk/vk_queue.hpp
    include/vk/vk_window_surface.hpp
    include/vk/vk_swapchain.hpp
    include/utility/console_output.hpp
    source/renderer.cpp
    source/vk/vk_renderer.cpp
    source/vk/vk_instance.cpp
    source/vk/vk_extensions.cpp
    source/vk/vk_validation_layers.cpp
    source/vk/vk_debug_messenger.cpp
    source/vk/vk_device.cpp
    source/vk/vk_queue_families.cpp
    source/vk/vk_queue.cpp
    source/vk/vk_window_surface.cpp
    source/vk/vk_swapchain.cpp
    source/utility/console_output.cpp)

add_library(${RENDERER_NAME} STATIC ${SOURCE_LIST})
target_include_directories(${RENDERER_NAME} PRIVATE include)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/_deps/glfw ${CMAKE_SOURCE_DIR}/_deps/glfw)
target_link_libraries(${RENDERER_NAME} PRIVATE glfw)

# GLM
add_subdirectory(${CMAKE_SOURCE_DIR}/_deps/glm ${CMAKE_SOURCE_DIR}/_deps/glm)
target_link_libraries(${RENDERER_NAME} PRIVATE glm)
add_definitions(-DGLM_FORCE_RADIANS -DGLM_FORCE_DEPTH_ZERO_TO_ONE)

# Vulkan
find_package(Vulkan)
target_link_libraries(${RENDERER_NAME} PRIVATE ${Vulkan_LIBRARIES})
target_include_directories(${RENDERER_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})

# Directory structure in IDEs that support it
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})

# Use C++17
target_compile_features(${RENDERER_NAME} PRIVATE cxx_std_17)

# High warning level and treat all warnings as errors
if(MSVC)
    target_compile_options(${RENDERER_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${RENDERER_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
