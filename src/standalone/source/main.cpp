#include "renderer.hpp"

int main()
{
    // Construct a new renderer
    jnt::JuggernautRenderer* renderer = jnt::JuggernautRenderer::New(jnt::GraphicsAPI::Vulkan);
    renderer->Initialize(1280, 720);
    
    // Attempt to create a new renderer
    if (!renderer->Create())
    {
        // Failed to create a new renderer, make sure all resources are destroyed
        renderer->Destroy();
        return -1;
    }

    // Wait for the renderer to finish rendering
    while (renderer->IsActive())
    {}
    
    // Deallocate resources
    renderer->Destroy();
    return 0;
}
