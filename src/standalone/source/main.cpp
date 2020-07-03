#include "renderer.hpp"

#include <iostream>

int main()
{
    jnt::Renderer renderer;

    try
    {
		renderer.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
