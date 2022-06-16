#pragma once

#include <memory>

#include "core/Texture.hpp"
#include "core/renderer/ElementBufferObject.hpp"
#include "core/renderer/VertexArrayObject.hpp"
#include "core/renderer/VertexBufferObject.hpp"

class SmartMesh
{
public:
    SmartMesh(std::shared_ptr<DynamicVertexBufferObject> vbo, std::shared_ptr<VertexArrayObject> vao, std::shared_ptr<ElementBufferObject> ebo,
              std::shared_ptr<Texture> texture);

    void Bind();
    void Unbind();

    unsigned int GetIndiciesCount();
    unsigned int GetTextureSlot();

private:
    std::shared_ptr<DynamicVertexBufferObject> m_VboPointer;
    std::shared_ptr<VertexArrayObject> m_VaoPointer;
    std::shared_ptr<ElementBufferObject> m_EboPointer;
    std::shared_ptr<Texture> m_Texture;
};

class Mesh
{
public:
    Mesh(DynamicVertexBufferObject* vbo, VertexArrayObject* vao, ElementBufferObject* ebo, Texture* texture);

    void Bind();
    void Unbind();

    unsigned int GetIndiciesCount();
    unsigned int GetTextureSlot();

private:
    DynamicVertexBufferObject* m_VboPointer;
    VertexArrayObject* m_VaoPointer;
    ElementBufferObject* m_EboPointer;
    Texture* m_Texture;
};
