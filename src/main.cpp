#include "MainLoop.hpp"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <iostream>

int main()
{
    glm::mat4 matrix;

    matrix = glm::mat4(1.0f);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
    MainLoop::run();
    return 0;
}
