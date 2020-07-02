set(STANDALONE_FILES source/main.cpp)

add_executable(${STANDALONE_NAME} ${STANDALONE_FILES})

target_link_libraries(${STANDALONE_NAME} PRIVATE ${RENDERER_NAME})
target_include_directories(${STANDALONE_NAME} PRIVATE
    include                 # This project
    ../renderer/include)    # Renderer library

# Use C++17
target_compile_features(${RENDERER_NAME} PRIVATE cxx_std_17)

# High warning level and treat all warnings as errors
if(MSVC)
    target_compile_options(${STANDALONE_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${STANDALONE_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
