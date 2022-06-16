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

void Renderer::Submit(Mesh* mesh)
{
    if (m_SceneStarted == false)
    {
        throw std::runtime_error("StartScene needs to be called before adding a mesh.");
    }

    m_Meshs.push_back(mesh);
}

void Renderer::Submit(entity* entity)
{
    if (m_SceneStarted == false)
    {
        throw std::runtime_error("StartScene needs to be called before adding an entity.");
    }

    m_Entities.push_back(entity);
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

    // for (const auto mesh : m_Meshs)
    // {
    //     mesh->Bind();
    //     m_Shader->SetTexture("TEX_SAMPLER", mesh->GetTextureSlot());
    //     GLCall(glDrawElements(GL_TRIANGLES, mesh->GetIndiciesCount(), GL_UNSIGNED_INT, 0));
    //     mesh->Unbind();
    // }

    // for (const auto& entity : m_Entities)
    // {
    //     entity->Bind();
    //     entity->UploadVerts();
    //     m_Shader->SetTexture("TEX_SAMPLER", entity->GetTextureSlot());
    //     GLCall(glDrawElements(GL_TRIANGLES, entity->GetIndiciesCount(), GL_UNSIGNED_INT, 0));
    //     entity->Unbind();
    // }

    for (int i = 0; i < m_Entities.size(); i++)
    {
        m_Entities[i]->Bind();
        m_Entities[i]->UploadVerts();
        m_Shader->SetTexture("TEX_SAMPLER", m_Entities[i]->GetTextureSlot());
        GLCall(glDrawElements(GL_TRIANGLES, m_Entities[i]->GetIndiciesCount(), GL_UNSIGNED_INT, 0));
        m_Entities[i]->Unbind();
    }
}
