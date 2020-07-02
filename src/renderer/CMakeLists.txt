set(RENDERER_FILES
    include/renderer.hpp
    source/renderer.cpp)

add_library(${RENDERER_NAME} STATIC ${RENDERER_FILES})
target_include_directories(${RENDERER_NAME} PRIVATE include)

# Use C++17
target_compile_features(${RENDERER_NAME} PRIVATE cxx_std_17)

# High warning level and treat all warnings as errors
if(MSVC)
    target_compile_options(${RENDERER_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${RENDERER_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
