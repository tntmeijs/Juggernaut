# Project names
set(RENDERER_NAME Renderer)
set(STANDALONE_NAME Standalone)

# Renderer library
add_subdirectory(renderer)

# Standalone project (depends on renderer)
add_subdirectory(standalone)
