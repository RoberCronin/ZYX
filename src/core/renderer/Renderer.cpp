#include "Renderer.hpp"
#include "core/Debug.hpp"
#include "core/renderer/Shader.hpp"

#include <GL/gl.h>
#include <stdexcept>

Renderer::Renderer()
    : m_SceneStarted(false)
    , m_SceneRendered(false)
    , m_Camera(nullptr)
{
}

void Renderer::StartScene(Camera* camera, Shader* shader)
{
    m_Meshs.clear();
    m_Camera = camera;
    m_Shader = shader;
    m_SceneStarted = true;
}

void Renderer::AddMesh(Mesh* mesh)
{
    if (m_SceneStarted == false)
    {
        throw std::runtime_error("StartScene needs to be called before adding a mesh.");
    }

    m_Meshs.push_back(mesh);
}

void Renderer::EndScene()
{
    if (m_SceneStarted == false)
    {
        throw std::runtime_error("StartScene needs to be called before ending the scene.");
    }

    m_SceneStarted = false;
}

void Renderer::Render()
{
    if (m_SceneStarted)
    {
        throw std::runtime_error("EndScene needs to be called before rendering.");
    }

    m_Shader->Bind();

    m_Shader->SetUniformMat4fv("uProjection", m_Camera->getProjectionMatrix());
    m_Shader->SetUniformMat4fv("uView", m_Camera->getViewMatrix());

    for (const auto mesh : m_Meshs)
    {
        mesh->Bind();
        m_Shader->SetTexture("TEX_SAMPLER", mesh->GetTextureSlot());
        GLCall(glDrawElements(GL_TRIANGLES, mesh->GetIndiciesCount(), GL_UNSIGNED_INT, 0));
        mesh->Unbind();
    }
}
