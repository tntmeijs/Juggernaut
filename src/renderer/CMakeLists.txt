set(SOURCE_LIST
    include/renderer.hpp
    source/renderer.cpp)

add_library(${RENDERER_NAME} STATIC ${SOURCE_LIST})
target_include_directories(${RENDERER_NAME} PRIVATE include)

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
