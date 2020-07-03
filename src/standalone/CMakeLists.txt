set(SOURCE_LIST source/main.cpp)

add_executable(${STANDALONE_NAME} ${SOURCE_LIST})

target_link_libraries(${STANDALONE_NAME} PRIVATE ${RENDERER_NAME})
target_include_directories(${STANDALONE_NAME} PRIVATE
    include                 # This project
    ../renderer/include)    # Renderer library

# Directory structure in IDEs that support it
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_LIST})

# Use C++17
target_compile_features(${RENDERER_NAME} PRIVATE cxx_std_17)

# High warning level and treat all warnings as errors
if(MSVC)
    target_compile_options(${STANDALONE_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${STANDALONE_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
