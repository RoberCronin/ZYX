#pragma once

#include "core/Camera.hpp"
#include "core/renderer/Mesh.hpp"
#include "core/renderer/Shader.hpp"

#include <vector>

class Renderer
{
public:
    Renderer();

    void StartScene(Camera* camera, Shader* shader);
    void Submit(Mesh* mesh);
    void EndScene();

    void Render();

private:
    Camera* m_Camera;
    Shader* m_Shader;
    std::vector<Mesh*> m_Meshs;
    bool m_SceneStarted;
    bool m_SceneRendered;
};
